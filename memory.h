/// @brief Allocates memory for a matrix
/// with certain height and width.
/// @param height The width.
/// @param width The height.
/// @return The pointer indicating to the matrix.
int **allocate_matrix(int height, int width);

/// @brief Frees a matrix.
/// @param matrix The matrix.
/// @param height Its height.
void free_matrix(int **matrix, int height);

/// @brief Frees the resources of the image.
/// @param image The image.
void free_image_resources(image *image);
