#ifndef TEMPLATE_PARSER
#define TEMPLATE_PARSER
#include "structs.h"

struct meesageTemplate_struct;

enum envVarNames
{
	tNight = 128,
	tDay = 64,
	feelsLike = 32,
	precipitationAmount = 16,
	windDir = 8,
	windSpeed = 4,
	windGustSpeed = 2,
	pressure = 1
};

typedef struct messageTemplate_struct
{
	enum messageTemplateTypeEnum messageType;
	char* message;
	int requiredFlags;
	char requiredEnvVars;
	char requiredEnvVarsPrevDay;

	//Required variables
	RANGE requiredNightTempRange;
	RANGE requiredDayTempTange;
	RANGE requiredFeelsLikeRange;
	RANGE requiredPrecipitationAmoundRange;
	enum windDirEnum requiredWindDir;
	RANGE requiredWindSpeedRange;
	RANGE requiredWindGustSpeed;
	RANGE requiredPressure;
	RANGE requiredDay;
	RANGE requiredMonth;

	//Required variables of previous day
	RANGE requiredNightTempRangePrevDay;
	RANGE requiredDayTempTangePrevDay;
	RANGE requiredFeelsLikeRangePrevDay;
	RANGE requiredPrecipitationAmoundRangePrevDay;
	RANGE requiredWindSpeedRangePrevDay;
	RANGE requiredWindGustSpeedPrevDay;
	RANGE requiredPressurePrevDay;

} MSG_TEMPLATE;

MSG_TEMPLATE* initTemplate();
MSG_TEMPLATE* initTemplateFromFields(char** rowFields);
MSG_TEMPLATE* makeTemplateCopy(MSG_TEMPLATE* original);
enum messageType getMsgTypeFromString(char* inputString);

#endif
