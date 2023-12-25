#include <stdio.h>

int identify_file_format(FILE * file, char file_format[]);

int read_integer(FILE *file);

int convert_string_to_integer(char string[]);

int clamp(int value, int minimum, int maximum);

void eliminate_junk(FILE *file);

void eliminate_comments(FILE *file);
