#ifndef STRUCTS
#define STRUCTS

struct date_struct;
struct range_struct;
struct environment_struct;

enum daysEnum {InvalidDay,Mon,Tue,Wed,Thur,Fri,Sat,Sun};
enum windDirEnum { North, NorthEast, NorthWest, South, SouthEast, SouthWest, East, West, None };
enum messageTemplateTypeEnum { InvalidTemplateType,Intro, Data, Message, Outro };

#define RAIN_FLAG_STRING "дождь"
#define SNOW_FLAG_STRING "снег"
#define HAILSHOWER_FLAG_STRING "град"
#define FROST_FLAG_STRING "иней"
#define ICEROADS_FLAG_STRING "гололед"
#define FOG_FLAG_STRING "туман"
#define STORM_FLAG_STRING "шторм"
#define LIGHTNING_FLAG_STRING "гроза"
#define SNOWSTORM_FLAG_STRING "метель"
#define FREEZING_FLAG_STRING "мороз"
#define DUST_FLAG_STRING "пыль"
#define SMOG_FLAG_STRING "смог"
#define ICING_FLAG_STRING "обледенение"
#define EMERGENCY_FLAG_STRING "чс"

#define NORTH_WIND_STRING "с"
#define NORTHEAST_WIND_STRING "св"
#define NORTHWEST_WIND_STRING "сз"
#define SOUTH_WIND_STRING "ю"
#define SOUTHEAST_WIND_STRING "юв"
#define SOUTHWEST_WIND_STRING "юз"
#define EAST_WIND_STRING "в"
#define WEST_WIND_STRING "з"

enum envFlags 
{
	rainFlag = 8192,
	snowFlag = 4096,
	hailShowerFlag = 2048,
	frostFlag = 1024,
	icyRoadsFlag = 512,
	fogFlag = 256,
	stormFlag = 128,
	lightningFlag = 64,
	snowStormFlag = 32,
	freezingFlag = 16,
	dustFlag = 8,
	smogFlag = 4,
	icingFlag = 2,
	emergencyFlag = 1
};

enum variables
{
	pressureVariableFlag = 128,
	windGustSpeedVariableFlag = 64,
	windSpeedVariableFlag = 32,
	windDirVariableFlag = 16,
	precipitationAmountVariableFlag = 8,
	feelsLikeVariableFlag = 4,
	tDayVariableFlag = 2,
	tNightVariableFlag = 1
};

#pragma region Structs

typedef struct date_struct
{
	short day;
	short month;
	short year;
} DATE;

typedef struct range_struct
{
	int min;
	int max;
} RANGE;

typedef struct environment_struct
{
	int flags;
	DATE date;
	RANGE tempNight;
	RANGE tempDay;
	RANGE feelsLike;
	int precipitationAmount;
	enum windDirEnum windDir;
	RANGE windSpeed;
	int windGustSpeed;
	int pressure;
	int prevDayAvailable;
} ENV_DATA;

#pragma endregion Structs

//Date functions
DATE* initDate();
DATE* initDateFromValues(int day, int month, int year);
DATE* initDateFromString(char* inputString);
int dateIsValid(DATE* date);
int isLeapYear(short year);
enum daysEnum dateToWeekday(DATE* date);
DATE* getPrevDayDate(DATE* currentDate);
int datesMatch(DATE* date1, DATE* date2);

//Range functions
RANGE* initRange();
RANGE* initRangeFromValues(int min, int max);
RANGE* initRangeFromString(char* inputString);
int valueInRange(RANGE* range, int value);
int rangesOverlap(RANGE* rangeOne, RANGE* rangeTwo);

//Environment functions
ENV_DATA* initEnvData();
ENV_DATA* initEnvDataFromValues(int flags, DATE date, RANGE tempNight, RANGE tempDay, RANGE feelsLike, int precipitationAmount, enum windDirEnum windDir, RANGE windSpeed, int windGustSpeed, int pressure, int prevDayAvailable);
ENV_DATA* makeEnvDataCopy(ENV_DATA* original);
int flagsMatch(ENV_DATA* envData, int flags);
int flagMatches(ENV_DATA* envData, int flag);
int getFlagsFromString(char* inputString);
int getWindDirFromString(char* inputString);

#endif