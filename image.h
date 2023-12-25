#include "utils.h"

typedef struct image image;

struct image {
	int **matrix;
	int width, height, maximum_value;
	int x_minimum, x_maximum, y_minimum, y_maximum;
	FILE *file;
	char file_format[3];
};

/// @brief Loads image from a certain file into image.
/// @param image Image will be stored here.
/// @param file_name Name of the file.
void load_image(image *image, char file_name[]);

/// @brief Reads the image matrix in the ascii way.
/// @param image Image will be stored here.
/// @param width The width of the image.
/// @param height The height of the image.
void read_matrix(image *image, int width, int height);

/// @brief Reads the image matrix in the binary way.
/// @param image Image will be stored here.
/// @param width The width of the image.
/// @param height The height of the image.
void read_matrix_binary(image *image, int width, int height);

/// @brief Selects a region of the image so
///	that next operations will be done on it.
/// @param image The image where selection
/// needs to be done.
/// @param first_x First pixel coordinate
/// corresponding to X axis.
/// @param first_y First pixel coordinate
/// corresponding to Y axis.
/// @param second_x Last pixel coordinate
/// corresponding to X axis.
/// @param second_y Last pixel coordinate
/// corresponding to Y axis.
void select_image_region(image *image,
						 int first_x,
						 int first_y,
						 int second_x,
						 int second_y);

/// @brief Selects the whole image so
///	that next operations will be done on it.
/// @param image The image where selection
/// needs to be done.
void select_whole_image(image *image);

/// @brief Stores selection coordinates.
/// @param image The image where selection
/// needs to be done.
/// @param first_x First pixel coordinate
/// corresponding to X axis.
/// @param first_y First pixel coordinate
/// corresponding to Y axis.
/// @param second_x Last pixel coordinate
/// corresponding to X axis.
/// @param second_y Last pixel coordinate
/// corresponding to Y axis.
void set_selection(image *image,
				   int first_x,
				   int first_y,
				   int second_x,
				   int second_y);

/// @brief Prints the histogram of a
/// certain image.
/// @param image The image.
/// @param maximum_stars The maximum
/// number of stars that need to be
///  printed on every line.
/// @param number_bins The number of
/// lines.
void calculate_histogram(image *image, int maximum_stars, int number_bins);

/// @brief Stores the image after
/// equalizing operation is done.
/// @param image The image where
/// equalizing operation is done.
void calculate_equalization(image *image);

/// @brief Rotates the selection of an image.
/// @param image The image where the rotation is done.
/// @param angle The angle of the rotation.
void rotate_image_selection(image *image, int angle);

/// @brief Checks if the whole image is selected.
/// @param image The image which is verified.
/// @return 1 if the whole image is selected,
/// otherwise 0.
int whole_image_selected(image *image);

/// @brief Roatates a PPM image.
/// @param image The image.
/// @param angle The angle of rotation.
void rotate_ppm_image(image *image, int angle);

/// @brief Roatates a PGM image.
/// @param image The image.
/// @param angle The angle of rotation.
void rotate_pgm_image(image *image, int angle);

/// @brief Saves a PGM image into a file.
/// @param image The image that needs to be saved.
/// @param is_binary 1 if the image needs to be saved in binary
/// format, 0 for ascii.
/// @param file_name The file where the image will be saved.
void save_pgm_image(image *image, int is_binary, char file_name[]);

/// @brief Saves a PPM image into a file.
/// @param image The image that needs to be saved.
/// @param is_binary 1 if the image needs to be saved in binary
/// format, 0 for ascii.
/// @param file_name The file where the image will be saved.
void save_ppm_image(image *image, int is_binary, char file_name[]);

/// @brief Crops the selection of a certain image.
/// @param image The image where the cropping operation will be
/// done.
void crop_image(image *image);

/// @brief Applies the EDGE kernel onto an image.
/// @param image The image where the kernel will be applied.
void apply_edge_detection(image *image);

/// @brief Applies the SHARPEN kernel onto an image.
/// @param image The image where the kernel will be applied.
void apply_sharpen(image *image);

/// @brief Applies the BLUR kernel onto an image.
/// @param image The image where the kernel will be applied.
void apply_blur(image *image);

/// @brief Applies the GAUSSIAN BLUR kernel onto an image.
/// @param image The image where the kernel will be applied.
void apply_gaussian_blur(image *image);

/// @brief Applies a specific kernel onto an image.
/// @param image The image where the kernel will be applied.
/// @param kernel The kernel which will be applied.
void apply_kernel(image *image, double kernel[3][3]);

/// @brief Saves an image into a file.
/// @param image The image which needs to be saved.
/// @param is_binary 1 if the image needs to be saved in binary
/// format, 0 for ascii.
/// @param file_name The file where the image will be saved.
void save_image_file(image *image, int is_binary, char file_name[]);
