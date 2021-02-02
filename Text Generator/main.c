#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

#include "csv/csvparser.h"

#include "structs.h"
#include "debug.h"
#include "functions.h"
#include "utils.h"

#define CSV_PARSER_OPTIONS CSV_STRICT|CSV_STRICT_FINI|CSV_APPEND_NULL|CSV_EMPTY_IS_NULL

typedef struct csv_parser CSV_PARSER;

int main(int argc, char* argv[]) 
{
	int originalArgc = argc;
	char* dataFilePath = NULL;
	char* templatesFilePath = NULL;
	char* outputFilePath = NULL;
	DATE* inputDate = NULL;
	int append = 0;

	int errorCode = 0;

	setlocale(LC_ALL, "Rus");
#pragma region Argument parsing

	if (strstr(argv[1], "/help"))
	{
		programInfo();
		exit(EXIT_SUCCESS);
	}

	if (argc-1 > MAX_ARG_COUNT*2 || argc-1 < MIN_ARG_COUNT*2)
	{
		printf(ERR_ARGCOUNT_TEXT);
		programInfo();
		exit(EXIT_CODE_WRONG_ARGC);
	}

	for (int i = 0; i < originalArgc; i++)//Search for flag arguments. Terrible, unefficient, and it works
	{
		if (strstr(argv[i], "/a"))
		{
			append = 1;
		}
	}

	while(argc-- > 1)
	{
		if (strstr(argv[argc], "/d"))
		{
			if (argc == originalArgc)//if this happens to be the last argument, attempt to read at argv[argc+1] would fail terribly. Check for that here.
			{
				printf_s(ERR_BAD_ARG_TEXT, argv[argc]);
				programInfo();
				exit(EXIT_CODE_BAD_ARG_ERROR);
			}

			int day = 0;
			int month = 0;
			int year = 0;

			errorCode = sscanf_s(argv[argc + 1],"%d.%d.%d",&day,&month,&year);

			if (errorCode != 3)
			{
				printf_s(ERR_BAD_ARG_TEXT, argv[argc]);
				programInfo();
				exit(EXIT_CODE_BAD_ARG_ERROR);
			}

			inputDate = initDateFromValues(day,month,year);

			if (!dateIsValid(inputDate))
			{
				printf_s(ERR_INVALID_DATE_TEXT, argv[argc+1]);
				exit(EXIT_CODE_INVALID_DATE_ERROR);
			}
		}

		if (strstr(argv[argc], "/i"))
		{
			//int errorCode = fopen_s(&dataFile,argv[argc + 1],"r");

			if (argc == originalArgc)//if this happens to be the last argument, attempt to read at argv[argc+1] would fail terribly. Check for that here.
			{
				printf_s(ERR_BAD_ARG_TEXT, argv[argc]);
				programInfo();
				exit(EXIT_CODE_BAD_ARG_ERROR);
			}

			dataFilePath = calloc(strlen(argv[argc + 1]), sizeof(char));
			errorCode = strcpy_s(dataFilePath, strlen(argv[argc + 1]),argv[argc + 1]);

			if(errorCode != 0)
			{
				printf_s(ERR_UNKNOWN_ERROR_TEXT);
				exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
			}

			//if (errorCode != 0)
			//{
			//	printf_s(ERR_INPUT_FILE_NOT_FOUND_TEXT, argv[argc + 1]);
			//	exit(EXIT_CODE_FILE_OPEN_ERROR);
			//}
			//else
			//{
			//	printf_s("Успешно открыт фаил данных: %s", argv[argc + 1]);
			//}
		}

		if (strstr(argv[argc], "/t"))
		{
			if (argc == originalArgc)//if this happens to be the last argument, attempt to read at argv[argc+1] would fail terribly. Check for that here.
			{
				printf_s(ERR_BAD_ARG_TEXT, argv[argc]);
				programInfo();
				exit(EXIT_CODE_BAD_ARG_ERROR);
			}

			//errorCode = fopen_s(&templatesFile, argv[argc + 1], "r");
			templatesFilePath = calloc(strlen(argv[argc + 1]), sizeof(char));
			errorCode = strcpy_s(outputFilePath, strlen(argv[argc + 1]), argv[argc + 1]);
			if (errorCode != 0)
			{
				printf_s(ERR_UNKNOWN_ERROR_TEXT);
				exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
			}

			//if (errorCode != 0)
			//{
			//	printf_s(ERR_TEMPLATE_FILE_NOT_FOUND_TEXT, argv[argc + 1]);
			//	exit(EXIT_CODE_FILE_OPEN_ERROR);
			//}
			//else
			//{
			//	printf_s("Успешно открыт фаил заготовок: %s", argv[argc + 1]);
			//}
		}

		if (strstr(argv[argc], "/o"))
		{
			if (argc+1 == originalArgc)//if this happens to be the last argument, attempt to read at argv[argc+1] would fail terribly. Check for that here.
			{
				printf_s(ERR_BAD_ARG_TEXT, argv[argc]);
				programInfo();
				exit(EXIT_CODE_BAD_ARG_ERROR);
			}

			outputFilePath = calloc(strlen(argv[argc + 1]), sizeof(char));
			errorCode = strcpy_s(outputFilePath, strlen(argv[argc + 1]), argv[argc + 1]);
			if (errorCode != 0)
			{
				printf_s(ERR_UNKNOWN_ERROR_TEXT);
				exit(EXIT_CODE_GENERAL_PURPOSE_ERROR);
			}

			//if (append)
			//{
			//	errorCode = fopen_s(&outputFile, argv[argc + 1], "a");
			//}
			//else
			//{
			//	errorCode = fopen_s(&outputFile, argv[argc + 1], "w");
			//}

			//if (errorCode != 0)
			//{
			//	printf_s(ERR_OUTPUT_FILE_OPEN_ERROR_TEXT, argv[argc + 1]);
			//	exit(EXIT_CODE_FILE_OPEN_ERROR);
			//}
			//else
			//{
			//	printf_s("Успешно открыт фаил вывода: %s", argv[argc + 1]);
			//}
		}
	}
#pragma endregion Argument parsing

	ENV_DATA* currentDateData = initEnvData();
	if (inputDate != NULL)
	{
		currentDateData->date = *inputDate;
	}
	else
	{
		error("inputDate was NULL");
		exit(EXIT_CODE_NULL_POINTER);
	}

	errorCode = populateEnvDataFromCsv(currentDateData,dataFilePath);
	if (errorCode == -1)
	{
		printf_s("Cannot find data record for date %d.%d.%d",currentDateData->date.day, currentDateData->date.month, currentDateData->date.year);
		exit(EXIT_CODE_RECORD_NOT_FOUND);
	}
}