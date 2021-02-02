#ifndef FUNCTIONS
#define FUNCTIONS

#include "structs.h"

int populateEnvDataFromCsv(ENV_DATA* environment, char* dataFilePath);
char* getFittingMessageOfType(enum messageType requestedMessageType, ENV_DATA* environment, ENV_DATA* prevDayEnvironment, char* templatesFilePath);
int checkMessageForFitness(char** fields, ENV_DATA* environment, ENV_DATA* prevDayEnvironment);

#endif