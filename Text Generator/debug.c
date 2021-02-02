#include "debug.h"
#include <stdlib.h>
#include <stdio.h>

void error(const char* message)
{
	printf_s("Error! %s",message);
}

void warning(const char* message)
{
	printf_s("Warning! %s",message);
}

void info(const char* message)
{
	printf_s("Info: %s",message);
}