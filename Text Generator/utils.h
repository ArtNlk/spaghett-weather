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

#define ERR_ARGCOUNT_TEXT "�������� ����� ����������, ����:\n"
#define ERR_INPUT_FILE_NOT_FOUND_TEXT "������! ������ �������� ����� ������� ������: %s\n"
#define ERR_TEMPLATE_FILE_NOT_FOUND_TEXT "������! ������ �������� ����� ������� ������: %s\n"
#define ERR_OUTPUT_FILE_OPEN_ERROR_TEXT "������! ������ �������� ����� ������ %s\n"
#define ERR_BAD_ARG_TEXT "������� ������ ��������� ���������: %s\n"
#define ERR_INVALID_DATE_TEXT "�������� ����: %s"
#define ERR_UNKNOWN_ERROR_TEXT "�������� ������! ���������� ��� ����� �������."

#define INFO_TEXT "��� ��������� ������� ��� ����������� ������� ��������� ������ �� ��������� ������ � ������� ������ � ������� CSV\n"
#define ARG_USAGE_TEXT "���������� ���������:\n\
/d <date> \t ���� �������� ���� DD.MM.YY ��� DD.MM.YYYY \n\
/i <filename> \t \���� � ����� � ������� \n\
/t <filename> \t ���� � ����� � ����������� \n\
/o <outputfile> \t ���� � ����� ������\n\
/a \t ��������� ����� � ����� ��������� ����� ������ ����������\n"

#define TEMPLATE_MSG_MAX_LENGTH 256
#define ERROR_STRING_MAX_LENGTH 50

//void usage(char* option);
void programInfo();

#endif
