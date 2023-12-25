// Copyright Cazacu Alexandru-Dan 312CA 2023-2024
#include "application.h"
#include <stdio.h>

void select_from_image(image *image)
{
	char command[100], *token, line[100];
	int first_x = 0, first_y = 0, second_x = 0, second_y = 0;

	scanf("%s", command);

	if (strcmp(command, "ALL") == 0) {
		select_whole_image(image);
	} else {
		fgets(line, 100, stdin);
		first_x = convert_string_to_integer(command);

		token = strtok(line, "\n ");
		if (!token) {
			printf("Invalid command\n");
			return;
		}
		first_y = convert_string_to_integer(token);

		token = strtok(NULL, "\n ");
		if (!token) {
			printf("Invalid command\n");
			return;
		}
		second_x = convert_string_to_integer(token);

		token = strtok(NULL, "\n ");
		if (!token) {
			printf("Invalid command\n");
			return;
		}
		second_y = convert_string_to_integer(token);

		if (first_x == 1e9 ||
			second_x == 1e9 ||
			first_y == 1e9 ||
			second_y == 1e9) {
			printf("Invalid command\n");
			return;
		}

		select_image_region(image, first_x, first_y, second_x, second_y);
	}
}

void print_histogram(image *image)
{
	int maximum_stars, number_bins;
	char line[100], *token;

	fgets(line, 100, stdin);

	token = strtok(line, "\n ");
	if (!token) {
		if (!image->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
		return;
	}
	maximum_stars = convert_string_to_integer(token);

	token = strtok(NULL, "\n ");
	if (!token) {
		if (!image->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
		return;
	}
	number_bins = convert_string_to_integer(token);

	token = strtok(NULL, "\n");
	if (token) {
		if (!image->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
		return;
	}

	calculate_histogram(image, maximum_stars, number_bins);
}

void rotate_image(image *image)
{
	int angle;
	scanf("%d", &angle);
	rotate_image_selection(image, angle);
}

void apply_effect(image *image)
{
	char effect[1000], effect_name[1000];
	int valid;
	fgets(effect, 1000, stdin);

	valid = sscanf(effect, "%s", effect_name);

	if ((int)effect[0] == 10) {
		if (!image->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
		return;
	}

	if (!valid)
		return;

	if (strcmp(effect_name, "EDGE") == 0)
		apply_edge_detection(image);
	else if (strcmp(effect_name, "SHARPEN") == 0)
		apply_sharpen(image);
	else if (strcmp(effect_name, "BLUR") == 0)
		apply_blur(image);
	else if (strcmp(effect_name, "GAUSSIAN_BLUR") == 0)
		apply_gaussian_blur(image);
	else
		printf("APPLY parameter invalid\n");
}

void save_image(image *image)
{
	char file_details[1000], file_name[1000], format_type[1000];
	int is_binary = 1, valid;

	format_type[0] = 0;
	fgets(file_details, 1000 * sizeof(char), stdin);

	valid = sscanf(file_details, "%s%s", file_name, format_type);

	if (!valid)
		return;

	if (strcmp(format_type, "ascii") == 0)
		is_binary = 0;

	save_image_file(image, is_binary, file_name);
}
