// Copyright Cazacu Alexandru-Dan 312CA 2023-2024
#include "application.h"

void load_image(image *image, char file_name[])
{
	char file_format[3];
	int width, height, maximum_value;
	// frees all the resources of the anterior image
	if (image->matrix)
		free_image_resources(image);

	image->file = fopen(file_name, "rb");

	// reads the image based on the file format
	if (image->file) {
		int is_binary = identify_file_format(image->file, file_format);
		strcpy(image->file_format, file_format);
		eliminate_comments(image->file);
		fscanf(image->file, "%d%d", &width, &height);
		eliminate_comments(image->file);

		image->width = width;
		image->height = height;
		if (strcmp(file_format, "pgm") == 0) {
			fscanf(image->file, "%d", &maximum_value);
			image->maximum_value = maximum_value;

			if (!is_binary)
				read_matrix(image, width, height);
			else
				read_matrix_binary(image, width, height);
		} else if (strcmp(file_format, "ppm") == 0) {
			fscanf(image->file, "%d", &maximum_value);
			image->maximum_value = maximum_value;

			if (!is_binary)
				read_matrix(image, 3 * width, height);
			else
				read_matrix_binary(image, 3 * width, height);
		} else if (strcmp(file_format, "pbm") == 0) {
			if (!is_binary)
				read_matrix(image, width, height);
			else
				read_matrix_binary(image, width, height);
		}
		image->x_minimum = 0;
		image->y_minimum = 0;
		image->x_maximum = image->width;
		image->y_maximum = image->height;

		fclose(image->file);
		printf("Loaded %s\n", file_name);
	} else {
		printf("Failed to load %s\n", file_name);
	}
}

void read_matrix(image *image, int width, int height)
{
	image->matrix = allocate_matrix(height, width);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			fscanf(image->file, "%d", &image->matrix[i][j]);
}

void read_matrix_binary(image *image, int width, int height)
{
	unsigned char data;
	eliminate_junk(image->file);
	image->matrix = allocate_matrix(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fread(&data, sizeof(unsigned char), 1, image->file);
			image->matrix[i][j] = data;
		}
	}
}

void select_image_region(image *image,
						 int first_x,
						 int first_y,
						 int second_x,
						 int second_y)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	int auxiliar;

	// checks if coordinated are valid
	if (first_x >= 0 && first_x < image->width &&
		second_x >= 0 && second_x <= image->width &&
	    first_y >= 0 && first_y < image->height &&
		second_y >= 0 && second_y <= image->height &&
		first_x != second_x && first_y != second_y) {
		if (first_x > second_x) {
			auxiliar = first_x;
			first_x = second_x;
			second_x = auxiliar;
		}
		if (first_y > second_y) {
			auxiliar = first_y;
			first_y = second_y;
			second_y = auxiliar;
		}
		set_selection(image, first_x, first_y, second_x, second_y);
		printf("Selected %d %d %d %d\n", first_x, first_y, second_x, second_y);
	} else {
		printf("Invalid set of coordinates\n");
	}
}

void select_whole_image(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	set_selection(image, 0, 0, image->width, image->height);
	printf("Selected ALL\n");
}

void set_selection(image *image,
				   int first_x,
				   int first_y,
				   int second_x,
				   int second_y)
{
	image->x_minimum = first_x;
	image->y_minimum = first_y;
	image->x_maximum = second_x;
	image->y_maximum = second_y;
}

void calculate_histogram(image *image, int maximum_stars, int number_bins)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") != 0) {
		printf("Black and white image needed\n");
		return;
	}

	int pixel_value_count[image->maximum_value + 1], maximum_bin_sum = -1;

	for (int i = 0; i <= image->maximum_value; i++)
		pixel_value_count[i] = 0;

	// counts the number of each pixel value appearance
	for (int i = image->y_minimum; i < image->y_maximum; i++)
		for (int j = image->x_minimum; j < image->x_maximum; j++)
			pixel_value_count[image->matrix[i][j]]++;

	int bin_length = image->maximum_value / number_bins;
	int bin_sum = 0, number_stars;

	if (image->maximum_value % number_bins != 0)
		bin_length++;

	for (int i = 0; i <= image->maximum_value; i++) {
		if (i % bin_length == 0) {
			if (bin_sum > maximum_bin_sum)
				maximum_bin_sum = bin_sum;
			bin_sum = 0;
		}

		bin_sum += pixel_value_count[i];
	}

	if (bin_sum > maximum_bin_sum)
		maximum_bin_sum = bin_sum;

	bin_sum = 0;

	// calculates how many * will each line have
	for (int i = 0; i <= image->maximum_value; i++) {
		if (i % bin_length == 0 && i != 0) {
			number_stars = 1.0 * (bin_sum * maximum_stars) / maximum_bin_sum;

			printf("%d\t|\t", number_stars);

			for (int j = 0; j < number_stars; j++)
				printf("*");
			printf("\n");
			bin_sum = 0;
		}

		bin_sum += pixel_value_count[i];
	}

	number_stars = 1.0 * (bin_sum * maximum_stars) / maximum_bin_sum;

	printf("%d\t|\t", number_stars);

	for (int j = 0; j < number_stars; j++)
		printf("*");
	printf("\n");
}

void calculate_equalization(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") != 0) {
		printf("Black and white image needed\n");
		return;
	}

	int partial_sum_pixel_value_count[image->maximum_value + 1];
	// calculates how many pixels have its value less than a
	// certain pixel
	for (int i = 0; i <= image->maximum_value; i++)
		partial_sum_pixel_value_count[i] = 0;

	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++)
			partial_sum_pixel_value_count[image->matrix[i][j]]++;

	for (int i = 1; i <= image->maximum_value; i++)
		partial_sum_pixel_value_count[i] +=
		partial_sum_pixel_value_count[i - 1];

	double result;
	// calculates new pixel value
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			result = (1.0 * image->maximum_value /
			(image->width * image->height)) *
			partial_sum_pixel_value_count[image->matrix[i][j]];

			image->matrix[i][j] =
			clamp((int)round(result), 0, image->maximum_value);
		}
	}
	printf("Equalize done\n");
}

void rotate_pgm_image(image *image, int angle)
{
	int **rotated_image, auxiliar;
	if (whole_image_selected(image)) {
		while (angle) {
			rotated_image = allocate_matrix(image->width, image->height);
			for (int i = 0; i < image->width; i++)
				for (int j = 0; j < image->height; j++)
					rotated_image[i][image->height - j - 1] =
					image->matrix[j][i];

			free_matrix(image->matrix, image->height);

			auxiliar = image->width;
			image->width = image->height;
			image->height = auxiliar;
			image->x_maximum = image->width;
			image->y_maximum = image->height;
			image->matrix = rotated_image;

			angle -= 90;
		}
	} else {
		rotated_image = allocate_matrix(image->height, image->width);
		for (int i = 0; i < image->height; i++)
			for (int j = 0; j < image->width; j++)
				rotated_image[i][j] = image->matrix[i][j];
		while (angle) {
			for (int i = image->y_minimum; i < image->y_maximum; i++)
				for (int j = image->x_minimum; j < image->x_maximum; j++)
					rotated_image[i][j] =
					image->matrix[image->y_maximum - j +
					image->x_minimum - 1][image->x_minimum -
					image->y_minimum + i];

			for (int i = image->y_minimum; i < image->y_maximum; i++)
				for (int j = image->x_minimum; j < image->x_maximum; j++)
					image->matrix[i][j] = rotated_image[i][j];

			angle -= 90;
		}

		free_matrix(rotated_image, image->height);
	}
}

void rotate_ppm_image(image *image, int angle)
{
	int **rotated_image, auxiliar;
	if (whole_image_selected(image)) {
		while (angle) {
			rotated_image = allocate_matrix(image->width, image->height * 3);
			for (int i = 0; i < image->width; i++) {
				for (int j = 0; j < image->height; j++) {
					rotated_image[i][3 * (image->height - j - 1)] =
					image->matrix[j][3 * i];
					rotated_image[i][3 * (image->height - j - 1) + 1] =
					image->matrix[j][3 * i + 1];
					rotated_image[i][3 * (image->height - j - 1) + 2] =
					image->matrix[j][3 * i + 2];
				}
			}

			free_matrix(image->matrix, image->height);

			auxiliar = image->width;
			image->width = image->height;
			image->height = auxiliar;
			image->x_maximum = image->width;
			image->y_maximum = image->height;
			image->matrix = rotated_image;

			angle -= 90;
		}
	} else {
		rotated_image = allocate_matrix(image->height, 3 * image->width);
		for (int i = 0; i < image->height; i++)
			for (int j = 0; j < 3 * image->width; j++)
				rotated_image[i][j] = image->matrix[i][j];
		while (angle) {
			for (int i = image->y_minimum; i < image->y_maximum; i++) {
				for (int j = image->x_minimum; j < image->x_maximum; j++) {
					rotated_image[i][3 * j] = image->matrix
					[image->y_maximum - j + image->x_minimum - 1]
					[3 * (image->x_minimum - image->y_minimum + i)];

					rotated_image[i][3 * j + 1] = image->matrix
					[image->y_maximum - j + image->x_minimum - 1]
					[3 * (image->x_minimum - image->y_minimum + i) + 1];

					rotated_image[i][3 * j + 2] = image->matrix
					[image->y_maximum - j + image->x_minimum - 1]
					[3 * (image->x_minimum - image->y_minimum + i) + 2];
				}
			}
			for (int i = image->y_minimum; i < image->y_maximum; i++)
				for (int j = image->x_minimum; j < 3 * image->x_maximum; j++)
					image->matrix[i][j] = rotated_image[i][j];

			angle -= 90;
		}

		free_matrix(rotated_image, image->height);
	}
}

void rotate_image_selection(image *image, int angle)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (image->x_maximum - image->x_minimum !=
		image->y_maximum - image->y_minimum) {
		if (!whole_image_selected(image)) {
			printf("The selection must be square\n");
			return;
		}
	}
	int rotation_angle = angle;
	if (rotation_angle < 0)
		rotation_angle = 360 + rotation_angle;

	if (rotation_angle != 0 &&
		rotation_angle != 90 &&
		rotation_angle != 180 &&
		rotation_angle != 270 &&
		rotation_angle != 360) {
		printf("Unsupported rotation angle\n");
		return;
	}

	if (strcmp(image->file_format, "ppm") == 0)
		rotate_ppm_image(image, rotation_angle);
	else if (strcmp(image->file_format, "pgm") == 0)
		rotate_pgm_image(image, rotation_angle);
	printf("Rotated %d\n", angle);
}

void save_pgm_image(image *image, int is_binary, char file_name[])
{
	FILE *file = fopen(file_name, "wb");
	if (is_binary)
		fprintf(file, "P5\n");
	else
		fprintf(file, "P2\n");
	fprintf(file,
			"%d %d\n%d\n",
			image->width,
			image->height,
			image->maximum_value);
	if (is_binary) {
		unsigned char *data;
		data = malloc(image->width * sizeof(unsigned char));
		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++)
				data[j] = (unsigned char)image->matrix[i][j];
			fwrite(data, sizeof(unsigned char), image->width, file);
		}
		free(data);
	} else {
		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++)
				fprintf(file, "%d ", image->matrix[i][j]);
			fprintf(file, "\n");
		}
	}
	fclose(file);
}

void save_ppm_image(image *image, int is_binary, char file_name[])
{
	FILE *file = fopen(file_name, "wb");
	if (is_binary)
		fprintf(file, "P6\n");
	else
		fprintf(file, "P3\n");
	fprintf(file,
			"%d %d\n%d\n",
			image->width,
			image->height,
			image->maximum_value);
	if (is_binary) {
		unsigned char *data;
		data = malloc(3 * image->width * sizeof(unsigned char));
		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < 3 * image->width; j++)
				data[j] = (unsigned char)image->matrix[i][j];
			fwrite(data, sizeof(unsigned char), 3 * image->width, file);
		}
		free(data);
	} else {
		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < 3 * image->width; j++)
				fprintf(file, "%d ", image->matrix[i][j]);
			fprintf(file, "\n");
		}
	}
	fclose(file);
}

int whole_image_selected(image *image)
{
	return image->x_minimum == 0 &&
		   image->y_minimum == 0 &&
		   image->x_maximum == image->width &&
		   image->y_maximum == image->height;
}

void crop_image(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	int **cropped_image;

	if (strcmp(image->file_format, "pgm") == 0) {
		cropped_image =
		allocate_matrix(image->y_maximum - image->y_minimum,
						image->x_maximum - image->x_minimum);

		for (int i = 0; i < image->y_maximum - image->y_minimum; i++)
			for (int j = 0; j < image->x_maximum - image->x_minimum; j++)
				cropped_image[i][j] =
				image->matrix[image->y_minimum + i][image->x_minimum + j];

		free_matrix(image->matrix, image->height);
		image->height = image->y_maximum - image->y_minimum;
		image->width = image->x_maximum - image->x_minimum;
		image->x_minimum = 0;
		image->y_minimum = 0;
		image->x_maximum = image->width;
		image->y_maximum = image->height;
		image->matrix = cropped_image;
	} else if (strcmp(image->file_format, "ppm") == 0) {
		cropped_image =
		allocate_matrix(image->y_maximum - image->y_minimum,
						3 * (image->x_maximum - image->x_minimum));

		for (int i = 0; i < image->y_maximum - image->y_minimum; i++)
			for (int j = 0; j < 3 * (image->x_maximum - image->x_minimum); j++)
				cropped_image[i][j] =
				image->matrix[image->y_minimum + i][3 * image->x_minimum + j];

		free_matrix(image->matrix, image->height);
		image->height = image->y_maximum - image->y_minimum;
		image->width = image->x_maximum - image->x_minimum;
		image->x_minimum = 0;
		image->y_minimum = 0;
		image->x_maximum = image->width;
		image->y_maximum = image->height;
		image->matrix = cropped_image;
	}
	printf("Image cropped\n");
}

void apply_edge_detection(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	double edge_detection_kernel[3][3] = {
		{-1, -1, -1},
		{-1, 8, -1},
		{-1, -1, -1}
	};

	apply_kernel(image, edge_detection_kernel);

	printf("APPLY EDGE done\n");
}

void apply_sharpen(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	double sharpen_kernel[3][3] = {
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};

	apply_kernel(image, sharpen_kernel);

	printf("APPLY SHARPEN done\n");
}

void apply_blur(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	double blur_kernel[3][3] = {
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9}
	};

	apply_kernel(image, blur_kernel);

	printf("APPLY BLUR done\n");
}

void apply_gaussian_blur(image *image)
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "pgm") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	double gaussian_blur_kernel[3][3] = {
		{1.0 / 16, 2.0 / 16, 1.0 / 16},
		{2.0 / 16, 4.0 / 16, 2.0 / 16},
		{1.0 / 16, 2.0 / 16, 1.0 / 16}
	};

	apply_kernel(image, gaussian_blur_kernel);

	printf("APPLY GAUSSIAN_BLUR done\n");
}

void apply_kernel(image *image, double kernel[3][3])
{
	int start_x = image->x_minimum, start_y = image->y_minimum;
	int final_x = image->x_maximum, final_y = image->y_maximum;
	int **new_matrix = allocate_matrix(image->height, 3 * image->width);

	if (start_x < 1)
		start_x = 1;

	if (start_y < 1)
		start_y = 1;

	if (final_x > image->width - 1)
		final_x = image->width - 1;

	if (final_y > image->height - 1)
		final_y = image->height - 1;

	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < 3 * image->width; j++)
			new_matrix[i][j] = image->matrix[i][j];

	// applying the kernel for all pixels in a certain selection
	for (int i = start_y; i < final_y; i++) {
		for (int j = start_x; j < final_x; j++) {
			double new_red_pixel = 0, new_green_pixel = 0, new_blue_pixel = 0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					new_red_pixel +=
					image->matrix[i + k - 1][3 * (j + l - 1)] *
					kernel[k][l];

					new_green_pixel +=
					image->matrix[i + k - 1][3 * (j + l - 1) + 1] *
					kernel[k][l];

					new_blue_pixel +=
					image->matrix[i + k - 1][3 * (j + l - 1) + 2] *
					kernel[k][l];
				}
			}
			new_red_pixel =
			clamp(round(new_red_pixel), 0, image->maximum_value);

			new_green_pixel =
			clamp(round(new_green_pixel), 0, image->maximum_value);

			new_blue_pixel =
			clamp(round(new_blue_pixel), 0, image->maximum_value);

			new_matrix[i][3 * j] = new_red_pixel;
			new_matrix[i][3 * j + 1] = new_green_pixel;
			new_matrix[i][3 * j + 2] = new_blue_pixel;
		}
	}

	free_matrix(image->matrix, image->height);
	image->matrix = new_matrix;
}

void save_image_file(image *image, int is_binary, char file_name[])
{
	if (!image->matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(image->file_format, "ppm") == 0)
		save_ppm_image(image, is_binary, file_name);
	else if (strcmp(image->file_format, "pgm") == 0)
		save_pgm_image(image, is_binary, file_name);

	printf("Saved %s\n", file_name);
}
