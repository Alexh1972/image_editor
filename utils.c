#include "utils.h"
#include <string.h>

int identify_file_format(FILE *file, char file_format[])
{
	char header[2];
	fread(header, sizeof(unsigned char), 2, file);
	if (strcmp(header, "P2") == 0 || strcmp(header, "P5") == 0)
		strcpy(file_format, "pgm");
	else if (strcmp(header, "P3") == 0 || strcmp(header, "P6") == 0)
		strcpy(file_format, "ppm");
	else if (strcmp(header, "P1") == 0 || strcmp(header, "P4") == 0)
		strcpy(file_format, "pbm");
	
	if (strcmp(header, "P2") == 0 || strcmp(header, "P3") == 0 || strcmp(header, "P1") == 0)
		return 0;
	
	if (strcmp(header, "P5") == 0 || strcmp(header, "P6") == 0 || strcmp(header, "P4") == 0)
		return 1;
	return 0;
}

int read_integer(FILE *file)
{
	char character;
	int answer = 0;
	character = fgetc(file);
	while (!feof(file) && !(character >= '0' && character <= '9')) {
		character = fgetc(file);
	}
	while (!feof(file) && character >= '0' && character <= '9') {
		answer = answer * 10 + ((int)character - '0');
		character = fgetc(file);
	}
	return answer;
}

void eliminate_junk(FILE *file)
{
	char junk[1000];
	fgets(junk, 1000, file);
}

void eliminate_comments(FILE *file)
{
	char first_line_character, comment[1000];
	first_line_character = fgetc(file);
	while (first_line_character == '#') {
		fgets(comment, 1000, file);
		first_line_character = fgetc(file);
	}
	fseek(file, -1, SEEK_CUR);
}

int convert_string_to_integer(char string[])
{
	int i = 0;
	int answer = 0;
	while (string[i]) {
		answer = answer * 10 + (string[i] - '0');
		i++;
	}
	return answer;
}

int clamp(int value, int minimum, int maximum)
{
	if (value < minimum)
		return minimum;
	if (value > maximum)
		return maximum;
	return value;
}