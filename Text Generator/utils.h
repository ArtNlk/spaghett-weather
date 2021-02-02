#ifndef UTILS
#define UTILS

#define EXIT_CODE_WRONG_ARGC -1
#define EXIT_CODE_MALLOC_ERROR -2
#define EXIT_CODE_FILE_OPEN_ERROR -3
#define EXIT_CODE_BAD_ARG_ERROR -4
#define EXIT_CODE_INVALID_DATE_ERROR -5
#define EXIT_CODE_NULL_POINTER -6
#define EXIT_CODE_GENERAL_PURPOSE_ERROR -7
#define EXIT_CODE_RECORD_NOT_FOUND -8

#define MAX_ARG_COUNT 5
#define MIN_ARG_COUNT 4
#define DATA_RECORD_NUM_FIELDS 11
#define TEMPLATE_RECORD_NUM_FIELDS 20

#define ERR_ARGCOUNT_TEXT "Неверное число аргументов, инфо:\n"
#define ERR_INPUT_FILE_NOT_FOUND_TEXT "Ошибка! Ошибка открытия файла входных данных: %s\n"
#define ERR_TEMPLATE_FILE_NOT_FOUND_TEXT "Ошибка! Ошибка открытия файла входных данных: %s\n"
#define ERR_OUTPUT_FILE_OPEN_ERROR_TEXT "Ошибка! Ошибка открытия файла вывода %s\n"
#define ERR_BAD_ARG_TEXT "Неверно заданы параметры программы: %s\n"
#define ERR_INVALID_DATE_TEXT "Неверная дата: %s"
#define ERR_UNKNOWN_ERROR_TEXT "Возникла ошибка! Программер уже курит мануалы."

#define INFO_TEXT "Эта программа создана для составления текстов прогнозов погоды на основании данных в формате файлов в формате CSV\n"
#define ARG_USAGE_TEXT "Допустимые параметры:\n\
/d <date> \t Дата прогноза вида DD.MM.YY или DD.MM.YYYY \n\
/i <filename> \t \Путь к файлу с данными \n\
/t <filename> \t Путь к файлу с заготовками \n\
/o <outputfile> \t Путь к файлу вывода\n\
/a \t Добавлять текст к концу выходного файла вместо перезаписи\n"

#define TEMPLATE_MSG_MAX_LENGTH 256
#define ERROR_STRING_MAX_LENGTH 50

//void usage(char* option);
void programInfo();

#endif
