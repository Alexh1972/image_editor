// Copyright Cazacu Alexandru-Dan 312CA 2023-2024
#include <stdio.h>

/// @brief Identifies the format of a certain image.
/// @param file The file.
/// @param file_format The format of the image.
/// @return 1 if the file is binary, 0 if it's ascii
int identify_file_format(FILE * file, char file_format[]);

/// @brief Read the next integer for a file.
/// @param file The file.
/// @return The integer which was read.
int read_integer(FILE *file);

/// @brief Converts a string into a number.
/// @param string The string to be converted.
/// @return 1e9 if the string is not valid,
/// otherwise the integer.
int convert_string_to_integer(char string[]);

/// @brief Clamp function.
/// @param value The value.
/// @param minimum The lower range.
/// @param maximum The upper range.
/// @return A number for the range.
int clamp(int value, int minimum, int maximum);

/// @brief Eliminates the whitespaces for the
/// end of the line from a file.
/// @param file The file.
void eliminate_junk(FILE *file);

/// @brief Eliminates the comments (lines beginning)
/// with "#" from a file.
/// @param file The file.
void eliminate_comments(FILE *file);
