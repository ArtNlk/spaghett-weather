#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "debug.h"
#include "utils.h"

#pragma region Functions
#pragma region Date functions
DATE* initDate()
{
	DATE* date = calloc(1,sizeof(DATE));
	if (date == NULL)
	{
		error("Date malloc error!");
		return date;
	}

	return date;
}

DATE* initDateFromValues(int day, int month, int year)
{
	DATE* date = calloc(1, sizeof(DATE));
	if (date == NULL)
	{
		error("Date from values malloc error!");
		return date;
	}

	date->day = day;
	date->month = month;
	//if we got something like xx.xx.xx as input, it will turn into 19xx if year is >= 50, and if year is less than 50, it will turn into 20xx

	if (year < 100)//Assume noone is gonna ask for weather of 01.01.99, if you do, too bad!
	{
		if (year < 50)
		{
			date->year = year + 2000;
		}
		else
		{
			date->year = year + 1900;
		}
	}
	else
	{
		date->year = year;
	}

	return date;
}

DATE* initDateFromString(char* inputString)//Expects input formatted as xx.xx.xx or xx.xx.xxxx
{
	if (inputString == NULL)
	{
		error("Init date from string: NULL string provided!");
		return NULL;
	}

	int day = 0;
	int month = 0;
	int year = 0;

	int numFields = sscanf_s(inputString,"%d.%d.%d",&day,&month,&year);
	if (numFields != 3)
	{
		error("Error reading date in initDateFromValues!");
		return NULL;
	}

	DATE* newDate = initDateFromValues(day,month,year);

	return newDate;
}

int dateIsValid(DATE* date) 
{
	if (date->month > 12 || date->month < 1)
	{
		return 0;
	}

	if (date->day > 31 || date->day < 1)
	{
		return 0; //months dont have more than 31 days or days less than 1
	}
	else if ((date->month <= 7 && date->month % 2 == 0) || (date->month > 7 && date->month % 2 == 1))
	{
		if (date->day > 30 || date->day < 1)
		{
			return 0; //Months in expression above have 30 or 29 days
		}

		if (date->month == 2) //february check
		{
			if (isLeapYear(date->year) && date->day > 29) //it is leap year, but date is bigger than 29
			{
				return 0;
			}
			else if (isLeapYear(date->year) != 1 && date->day > 28) //it is not leap year and date is bigger than 28
			{
				return 0;
			}
		}
	}

	if (date->year < 0)
	{
		return 0;
	}

	return 1;//if no checks above tripped, date is valid
}

DATE* getPrevDayDate(DATE* currentDate)
{
	if (!dateIsValid(currentDate))
	{
		error("Invalid date in getPrevDayDate!");
		return NULL;
	}

	int newYear = 0;
	int newMonth = 0;
	int newDay = 0;

	if (currentDate->day == 1)//Is it first day or any other?
	{
		if (currentDate->month == 1)//If yes, is it january today?
		{
			//If yes, prev. day is dec. 31 of previous year
			newYear = currentDate->year - 1;
			newMonth = 12;
			newDay = 31;
		}
		else
		{
			if (currentDate->month == 3)//If its not january, is it march? Since we are gonna roll back to february!
			{
				if (isLeapYear(currentDate->year))//If its march, is it leap year?
				{
					newYear = currentDate->year;
					newMonth = 2;
					newDay = 29;//If yes, set day to 29, since it leap year and its february
				}
				else
				{
					newYear = currentDate->year;
					newMonth = 2;
					newDay = 28;//else set to 28
				}
			}
			else
			{
				//Its nor january and not march, so keep the year and roll back the month, since we are still in a "its a first day of month" branch
				newYear = currentDate->year;
				newMonth = currentDate->month - 1;
				if ((newMonth <= 7 && newMonth % 2 == 0) || (newMonth > 7 && newMonth % 2 == 1))//Check for 30/31 days
				{
					newDay = 30;//
				}
				else
				{
					newDay = 31;
				}
			}
		}
	}
	else
	{
		//If it is not the first of some month, its simple: roll back the day by one:
		newYear = currentDate->year;
		newMonth = currentDate->month;
		newDay = currentDate->day - 1;
	}

	DATE* newDate = initDateFromValues(newDay,newMonth,newYear);

	return newDate;
}

int isLeapYear(short year)
{
	if (year % 400 == 0)
		return 1;
	if (year % 100 == 0)
		return 0;
	if (year % 4 == 0)
		return 1;
	return 0;
}

enum daysEnum dateToWeekday(DATE* date)
{
	if (dateIsValid(date))
	{
		int day = date->day;
		int month = date->month;
		int year = date->year;
		int weekday  = (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4 - year/100 + year/400)%7; //Have no idea on how this works, but this is amazing, found here: https://stackoverflow.com/a/21235587/11591076
		return weekday;
	}
	else
	{
		return InvalidDay;
	}
}

int datesMatch(DATE* date1, DATE* date2)
{
	return date1->day == date2->day && date1->month == date2->month && date1->year == date2->year;
}
#pragma endregion

#pragma region Range functions

RANGE* initRange() 
{
	RANGE* range = calloc(1,sizeof(RANGE));
	if (range == NULL);
	{
		error("Range malloc error!");
		return range;
	}

	return range;
}

RANGE* initRangeFromValues(int min, int max) 
{
	RANGE* range = calloc(1,sizeof(RANGE));
	if (range == NULL);
	{
		error("Range malloc error!");
		return range;
	}

	range->min = min;
	range->max = max;

	return range;
}

RANGE* initRangeFromString(char* inputString)
{
	if (inputString == NULL)
	{
		error("Init range from string: NULL string provided!");
		return NULL;
	}

	int min = 0;
	int max = 0;

	int numFields = sscanf_s(inputString, "%d %d", &min, &max);
	if (numFields != 2)
	{
		error("Error reading range in initRangeFromValues!");
		return NULL;
	}

	RANGE* newRange = initRangeFromValues(min,max);

	return newRange;
}

int valueInRange(RANGE* range, int value)
{
	return (value < range->max && value > range->min);
}

int rangesOverlap(RANGE* rangeOne, RANGE* rangeTwo)
{
	return (valueInRange(rangeOne,rangeTwo->max) || valueInRange(rangeOne, rangeTwo->min) ||
		valueInRange(rangeTwo, rangeOne->max) || valueInRange(rangeTwo, rangeOne->min));
}

#pragma endregion

#pragma region Environment functions

ENV_DATA* initEnvData()
{
	ENV_DATA* envData = calloc(1,sizeof(ENV_DATA));
	if (envData == NULL)
	{
		error("EnvData malloc error!");
		return envData;
	}

	return envData;
}

ENV_DATA* initEnvDataFromValues(int flags, DATE date, RANGE tempNight, RANGE tempDay, RANGE feelsLike, int precipitationAmount, enum windDirEnum windDir, RANGE windSpeed, int windGustSpeed, int pressure, int prevDayAvailable)
{
	ENV_DATA* envData = calloc(1,sizeof(ENV_DATA));
	if (envData == NULL)
	{
		error("EnvData from values malloc error!");
		return envData;
	}

	envData->date = date;
	envData->feelsLike = feelsLike;
	envData->flags = flags;
	envData->precipitationAmount = precipitationAmount;
	envData->pressure = pressure;
	envData->tempDay = tempDay;
	envData->tempNight = tempNight;
	envData->windDir = windDir;
	envData->windGustSpeed = windGustSpeed;
	envData->windSpeed = windSpeed;
	envData->prevDayAvailable = prevDayAvailable;

	return envData;
}

ENV_DATA* makeEnvDataCopy(ENV_DATA* original)
{
	ENV_DATA* envData = malloc(sizeof(ENV_DATA));
	if (envData == NULL)
	{
		error("EnvData copying malloc error!");
		return envData;
	}

	envData->date = original->date;
	envData->feelsLike = original->feelsLike;
	envData->flags = original->flags;
	envData->precipitationAmount = original->precipitationAmount;
	envData->pressure = original->pressure;
	envData->tempDay = original->tempDay;
	envData->tempNight = original->tempNight;
	envData->windDir = original->windDir;
	envData->windGustSpeed = original->windGustSpeed;
	envData->windSpeed = original->windSpeed;
	envData->prevDayAvailable = original->prevDayAvailable;

	return envData;
}

int flagsMatch(ENV_DATA* envData, int flags)//Check if all flags match
{
	return envData->flags == flags;
}

int flagMatches(ENV_DATA* envData, int flag)//Check if at least one flag matches
{
	return envData->flags && flag != 0;
}

int getFlagsFromString(char* inputString)
{
	int flags = 0;

	if (strstr(inputString,RAIN_FLAG_STRING))
	{
		flags = flags | rainFlag;
	}

	if (strstr(inputString, SNOW_FLAG_STRING))
	{
		flags = flags | snowFlag;
	}

	if (strstr(inputString, HAILSHOWER_FLAG_STRING))
	{
		flags = flags | hailShowerFlag;
	}

	if (strstr(inputString, FROST_FLAG_STRING))
	{
		flags = flags | frostFlag;
	}

	if (strstr(inputString, ICEROADS_FLAG_STRING))
	{
		flags = flags | icyRoadsFlag;
	}

	if (strstr(inputString, FOG_FLAG_STRING))
	{
		flags = flags | fogFlag;
	}

	if (strstr(inputString, STORM_FLAG_STRING))
	{
		flags = flags | stormFlag;
	}

	if (strstr(inputString, LIGHTNING_FLAG_STRING))
	{
		flags = flags | lightningFlag;
	}

	if (strstr(inputString, SNOWSTORM_FLAG_STRING))
	{
		flags = flags | snowStormFlag;
	}

	if (strstr(inputString, FREEZING_FLAG_STRING))
	{
		flags = flags | freezingFlag;
	}

	if (strstr(inputString, DUST_FLAG_STRING))
	{
		flags = flags | dustFlag;
	}

	if (strstr(inputString, SMOG_FLAG_STRING))
	{
		flags = flags | smogFlag;
	}

	if (strstr(inputString, ICING_FLAG_STRING))
	{
		flags = flags | icingFlag;
	}

	if (strstr(inputString, EMERGENCY_FLAG_STRING))
	{
		flags = flags | emergencyFlag;
	}

	return flags;
}

int getWindDirFromString(char* inputString)
{
	if (strstr(inputString, NORTH_WIND_STRING))
	{
		return North;
	}

	if (strstr(inputString, NORTHEAST_WIND_STRING))
	{
		return NorthEast;
	}

	if (strstr(inputString, NORTHWEST_WIND_STRING))
	{
		return NorthWest;
	}

	if (strstr(inputString, SOUTH_WIND_STRING))
	{
		return South;
	}

	if (strstr(inputString, SOUTHEAST_WIND_STRING))
	{
		return SouthEast;
	}

	if (strstr(inputString, SOUTHWEST_WIND_STRING))
	{
		return SouthWest;
	}

	if (strstr(inputString, EAST_WIND_STRING))
	{
		return East;
	}
	
	if (strstr(inputString, WEST_WIND_STRING))
	{
		return West;
	}

	return None;
}

#pragma endregion


#pragma endregion
