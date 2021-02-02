#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "csv/csvparser.h"
#include "utils.h"
#include "debug.h"
#include "templateParser.h"



int populateEnvDataFromCsv(ENV_DATA* environment, char* dataFilePath) 
{
	CsvParser* csvParser = CsvParser_new(dataFilePath,',',0);

	CsvRow* csvRecord = NULL;
	int rowCounter = 0;

	char** rowFields = NULL;

	while (csvRecord = CsvParser_getRow(csvParser) != NULL)
	{
		rowCounter++;
		int numFields = CsvParser_getNumFields(csvRecord);
		if (numFields != DATA_RECORD_NUM_FIELDS)
		{
			printf_s("Malformed record on line %d. Please investigate. Skipping...", rowCounter);
			CsvParser_destroy_row(csvRecord);
			continue;
		}

		rowFields = CsvParser_getFields(csvRecord);

		//Check date:
		DATE* newDate = initDateFromString(rowFields[0]);

		if (!datesMatch(&environment->date, newDate))
		{
			CsvParser_destroy_row(csvRecord);
			continue;
		}
		else
		{
			printf_s("Found record for date %d.%d.%d on row %d, processing...", newDate->day, newDate->month, newDate->year, rowCounter);
			free(newDate);
		}
	}

	if (csvRecord == NULL)
	{
		CsvParser_destroy(csvParser);
		return -1;
	}
		//Process T night:
		RANGE* tNight = initRangeFromString(rowFields[1]);
		if (tNight != NULL)
		{
			environment->tempNight = *tNight;
			free(tNight);
		}
		else
		{
			error("NULL detected in populating environment value tNight");
			exit(EXIT_CODE_NULL_POINTER);
		}

		//Process T day:
		RANGE* tDay = initRangeFromString(rowFields[2]);
		if (tDay != NULL)
		{
			environment->tempDay = *tDay;
			free(tDay);
		}
		else
		{
			error("NULL detected in populating environment value tDay");
			exit(EXIT_CODE_NULL_POINTER);
		}

		//Process Feels like:
		RANGE* feelsLike = initRangeFromString(rowFields[3]);
		if (feelsLike != NULL)
		{
			environment->feelsLike = *feelsLike;
			free(feelsLike);
		}
		else
		{
			error("NULL detected in populating environment value feelsLike");
			exit(EXIT_CODE_NULL_POINTER);
		}

		//Process precipitation:
		int precipitationFlags = getFlagsFromString(rowFields[4]);
		environment->flags = environment->flags | precipitationFlags;

		//Process precipitation amount:
		int precipitationAmout = 0;
		int errorCode = sscanf_s(rowFields[5],"%d",&precipitationAmout);
		if (errorCode != 1)
		{
			error("Error processing precipitation amount. Number of read fields != 1");
			exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
		}

		//Process wind direction:
		environment->windDir = getWindDirFromString(rowFields[6]);

		//Wind speed processing:
		RANGE* windSpeed = initRangeFromString(rowFields[7]);
		if (windSpeed != NULL)
		{
			environment->windSpeed = *windSpeed;
			free(windSpeed);
		}
		else
		{
			error("NULL detected in populating environment value windSpeed");
			exit(EXIT_CODE_NULL_POINTER);
		}

		//Wind gust speed processing:
		int windGustSpeed = 0;
		errorCode = sscanf_s(rowFields[8], "%d",&windGustSpeed);
		environment->windGustSpeed = windGustSpeed;
		if (errorCode != 1)
		{
			error("Error processing windGustSpeed: number of read fields != 1");
			exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
		}

		//Wind gust speed processing:
		int pressure = 0;
		errorCode = sscanf_s(rowFields[9], "%d", &pressure);
		environment->pressure = pressure;
		if (errorCode != 1)
		{
			error("Error processing pressure: number of read fields != 1");
			exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
		}

		int envFlags = getFlagsFromString(rowFields[10]);
		environment->flags = environment->flags | envFlags;
		CsvParser_destroy_row(csvRecord);
		CsvParser_destroy(csvParser);
		return 0;
}

int checkMessageForFitness(char** fields, ENV_DATA* environment, ENV_DATA* prevDayEnvironment)
{
	RANGE* testRange = initRange();
	int numReadFields = 0;
	int templateFlags = getFlagsFromString(fields[19]);

	if (!flagsMatch(environment, templateFlags))
	{
		return -1;
	}

	//Day test:
	numReadFields = sscanf_s(fields[2], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!valueInRange(testRange, environment->date.day))
	{
		return -1;
	}

	//Month test:
	numReadFields = sscanf_s(fields[3], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!valueInRange(testRange, environment->date.month))
	{
		return -1;
	}

	//Tnight test:
	numReadFields = sscanf_s(fields[4], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->tempNight))
	{
		return -1;
	}

	//Tday test:
	numReadFields = sscanf_s(fields[5], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->tempDay))
	{
		return -1;
	}

	//Feels like test:
	numReadFields = sscanf_s(fields[6], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->feelsLike))
	{
		return -1;
	}

	//Precipitation amount test
	numReadFields = sscanf_s(fields[7], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->precipitationAmount))
	{
		return -1;
	}

	//Wind speed test
	numReadFields = sscanf_s(fields[8], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->windSpeed))
	{
		return -1;
	}

	//Wind gust speed test
	numReadFields = sscanf_s(fields[9], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->windGustSpeed))
	{
		return -1;
	}

	//Pressure test
	numReadFields = sscanf_s(fields[10], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &environment->pressure))
	{
		return -1;
	}

	/*
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////PREV DAY CHECKS GO FROM NOW///////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	*/
	if (strcmp(fields[11], "нет"))
	{
		return 1;
	}
	//Tnight test:
	numReadFields = sscanf_s(fields[12], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->tempNight))
	{
		return -1;
	}

	//Tday test:
	numReadFields = sscanf_s(fields[13], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->tempDay))
	{
		return -1;
	}

	//Feels like test:
	numReadFields = sscanf_s(fields[14], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->feelsLike))
	{
		return -1;
	}

	//Precipitation amount test
	numReadFields = sscanf_s(fields[15], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->precipitationAmount))
	{
		return -1;
	}

	//Wind speed test
	numReadFields = sscanf_s(fields[16], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->windSpeed))
	{
		return -1;
	}

	//Wind gust speed test
	numReadFields = sscanf_s(fields[17], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->windGustSpeed))
	{
		return -1;
	}

	//Pressure test
	numReadFields = sscanf_s(fields[18], "%d %d", &testRange->min, &testRange->max);
	if (numReadFields != 2)
	{
		return -2;
	}
	if (!rangesOverlap(testRange, &prevDayEnvironment->pressure))
	{
		return -1;
	}

	return 1;
}

char* getFittingMessageOfType(enum messageType requestedMessageType, ENV_DATA environment, ENV_DATA prevDayEnvironment, char* templatesFilePath)
{
	CsvParser* csvParser = CsvParser_new(templatesFilePath, ',', 0);

	CsvRow* csvRecord = NULL;
	int numRecords= 0;
	int rowCounter = 0;
	int fitness = 0;

	char** rowFields = NULL;

	while (csvRecord = CsvParser_getRow(csvParser) != NULL)
	{
		rowCounter++;
		int numFields = CsvParser_getNumFields(csvRecord);
		if (numFields != TEMPLATE_RECORD_NUM_FIELDS)
		{
			printf_s("Malformed template record on line %d. Please investigate. Skipping...", rowCounter);
			CsvParser_destroy_row(csvRecord);
			continue;
		}

		rowFields = CsvParser_getFields(csvRecord);

		//Check type:
		enum messageType msgType = getMsgTypeFromString(rowFields[0]);

		if (msgType != requestedMessageType)
		{
			CsvParser_destroy_row(csvRecord);
			continue;
		}
		else
		{

			printf_s("Found template record number %d",numRecords);
		}
	}
}


