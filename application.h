// Copyright Cazacu Alexandru-Dan 312CA 2023-2024
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "command.h"
#include "utils.h"
#include "memory.h"

/// @brief Runs the image editor.
void run(void);

/// @brief Reads a command and executes it.
/// @param is_running When it becomes 0, the program stops.
/// @param image The image where operations will be done.
void execute_command(int *is_running, image *image);

/// @brief Stops the program and frees all the resources.
/// @param image The image which needs to be freed.
/// @param is_running It becomes 0.
void stop(image *image, int *is_running);
