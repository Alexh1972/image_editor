#include "application.h"

void run(void)
{
	int is_running = 1;
	image image;
	image.file = NULL;
	image.matrix = NULL;
	while (is_running) {
		execute_command(&is_running, &image);
	}
}

void execute_command(int *is_running, image *image)
{
	char command[1000];
	scanf("%s", command);
	if (strcmp(command, "LOAD") == 0) {
		char file_name[1000];
		scanf("%s", file_name);
		load_image(image, file_name);
	} else if (strcmp(command, "EXIT") == 0) {
		stop(image, is_running);
	} else if (strcmp(command, "SELECT") == 0) {
		select_from_image(image);
	} else if (strcmp(command, "HISTOGRAM") == 0) {
		print_histogram(image);
	} else if (strcmp(command, "EQUALIZE") == 0) {
		calculate_equalization(image);
	} else if (strcmp(command, "ROTATE") == 0) {
		rotate_image(image);
	} else if (strcmp(command, "CROP") == 0) {
		crop_image(image);
	} else if (strcmp(command, "APPLY") == 0) {
		apply_effect(image);
	} else if (strcmp(command, "SAVE") == 0) {
		save_image(image);
	} else {
		fgets(command, 1000, stdin);
		printf("Invalid command\n");
	}
} 

void stop(image *image, int *is_running)
{
	if (image->matrix == NULL)
		printf("No image loaded\n");
	else
		free_image_resources(image);
	*is_running = 0;
}