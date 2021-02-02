#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "templateParser.h"
#include "utils.h"

MSG_TEMPLATE* initTemplate()
{
	MSG_TEMPLATE* msgTemplate = calloc(1, sizeof(MSG_TEMPLATE));
	if (msgTemplate == NULL)
	{
		error("EnvData malloc error!");
		exit(EXIT_CODE_MALLOC_ERROR);
		//return NULL;
	}

	msgTemplate->message = NULL;

	return msgTemplate;
}

MSG_TEMPLATE* initTemplateFromFields(char** rowFields)
{
	MSG_TEMPLATE* msgTemplate = initTemplate();

}

MSG_TEMPLATE* makeTemplateCopy(MSG_TEMPLATE* original)
{
	MSG_TEMPLATE* copy = calloc(1, sizeof(MSG_TEMPLATE));

	int errorCode = memcpy_s(copy, sizeof(MSG_TEMPLATE), original, sizeof(MSG_TEMPLATE));
	if (errorCode);
	{
		char* errorString = calloc(ERROR_STRING_MAX_LENGTH, sizeof(char));
		if (errorString == NULL)
		{
			error("Error allocating error string in message template copying");
			exit(EXIT_CODE_MALLOC_ERROR);
			return NULL;
		}
		else
		{
			sprintf_s(errorString, ERROR_STRING_MAX_LENGTH, "Message template copying error with code %d", errorCode);
			return NULL;
		}
		error(errorString);
		free(errorString);
		exit(EXIT_CODE_MALLOC_ERROR);
		return NULL;
	}

	errorCode = memcpy_s(copy->message, sizeof(char) * TEMPLATE_MSG_MAX_LENGTH, original->message, sizeof(char) * TEMPLATE_MSG_MAX_LENGTH);

	if (errorCode);
	{
		char* errorString = calloc(ERROR_STRING_MAX_LENGTH, sizeof(char));
		if (errorString == NULL)
		{
			error("Error allocating error string in message template message string copying");
			exit(EXIT_CODE_MALLOC_ERROR);
			return NULL;
		}
		else
		{
			sprintf_s(errorString, ERROR_STRING_MAX_LENGTH, "Message template message string copying error with code %d", errorCode);
			return NULL;
		}
		error(errorString);
		free(errorString);
		exit(EXIT_CODE_MALLOC_ERROR);
		return NULL;
	}

	return copy;
}

enum messageType getMsgTypeFromString(char* inputString)
{
	if (strstr(inputString,"начало"))
	{
		return Intro;
	}

	if (strstr(inputString, "данные"))
	{
		return Data;
	}

	if (strstr(inputString, "Сообщение"))
	{
		return Message;
	}

	if (strstr(inputString, "конец"))
	{
		return Outro;
	}

	return InvalidTemplateType;
}

int checkTemplateFitness(MSG_TEMPLATE template, ENV_DATA environment)
{

}
