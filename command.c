#include "application.h"
#include <stdio.h>

void select_from_image(image *image)
{
	char command[100];
	scanf("%s", command);
	int first_x = 0, first_y = 0, second_x = 0, second_y = 0;
	if (strcmp(command, "ALL") == 0) {
		select_whole_image(image);
	} else {
		first_x = convert_string_to_integer(command);
		scanf("%d%d%d", &first_y, &second_x, &second_y);
		select_image_region(image, first_x, first_y, second_x, second_y);
	}
}

void print_histogram(image *image)
{
	int maximum_stars, number_bins;
	scanf("%d%d", &maximum_stars, &number_bins);
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
	char effect_name[1000];
	scanf("%s", effect_name);
	if (strcmp(effect_name, "EDGE") == 0) {
		apply_edge_detection(image);
	} else if (strcmp(effect_name, "SHARPEN") == 0) {
		apply_sharpen(image);
	} else if (strcmp(effect_name, "BLUR") == 0) {
		apply_blur(image);
	} else if (strcmp(effect_name, "GAUSSIAN_BLUR") == 0) {
		apply_gaussian_blur(image);
	} else {
		printf("APPLY parameter invalid\n");
	}
}

void save_image(image *image)
{
	char file_details[1000], file_name[1000], format_type[1000];
	int is_binary = 1;
	format_type[0] = 0;
	fgets(file_details, 1000 * sizeof(char), stdin);
	sscanf(file_details, "%s%s", file_name, format_type);
	if (strcmp(format_type, "ascii") == 0)
		is_binary = 0;

	save_image_file(image, is_binary, file_name);
}