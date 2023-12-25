#include "image.h"

/// @brief Reads selection coordinates.
/// @param image The image where the selection
/// will be done.
void select_from_image(image * image);

/// @brief Reads the number of bins
/// and their maximum length and prints
/// the histogram.
/// @param image The image based on the
/// histogram will be calculates.
void print_histogram(image *image);

/// @brief Reads the angle of rotation
/// and rotates the image.
/// @param image The image where the rotation
/// will be done.
void rotate_image(image *image);

/// @brief Reads the name of the effect
/// which will be applied and applies it.
/// @param image The image.
void apply_effect(image *image);

/// @brief Reads the name of the file
/// where the image will be saved and
/// the format.
/// @param image The image which will be
/// saved. 
void save_image(image *image);
