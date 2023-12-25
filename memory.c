#include "application.h"

int **allocate_matrix(int height, int width)
{
	int **matrix = malloc(height * sizeof(int *));

	for (int i = 0; i < height; i++)
		matrix[i] = calloc(width, sizeof(int));
	return matrix;
}

void free_matrix(int **matrix, int height)
{
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

void free_image_resources(image *image)
{
	free_matrix(image->matrix, image->height);
	image->file = NULL;
	image->matrix = NULL;
}
