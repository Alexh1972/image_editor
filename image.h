#include "utils.h"

typedef struct image image;

struct image {
	int **matrix;
	int width, height, maximum_value;
	int x_minimum, x_maximum, y_minimum, y_maximum;
	FILE *file;
	char file_format[3];
};

void load_image(image *image, char file_name[]);

void read_matrix(image *image, int width, int height);

void read_matrix_binary(image *image, int width, int height);

void select_image_region(image *image, int first_x, int first_y, int second_x, int second_y);

void select_whole_image(image *image);

void set_selection(image *image, int first_x, int first_y, int second_x, int second_y);

void calculate_histogram(image *image, int maximum_stars, int number_bins);

void calculate_equalization(image *image);

void rotate_image_selection(image *image, int angle);

int whole_image_selected(image *image);

void rotate_ppm_image(image *image, int angle);

void rotate_pgm_image(image *image, int angle);

void save_pgm_image(image *image, int is_binary, char file_name[]);

void save_ppm_image(image *image, int is_binary, char file_name[]);

void crop_image(image *image);

void apply_edge_detection(image *image);

void apply_sharpen(image *image);

void apply_blur(image *image);

void apply_gaussian_blur(image *image);

void apply_kernel(image *image, double kernel[3][3]);

void save_image_file(image *image, int is_binary, char file_name[]);


