#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "command.h"
#include "utils.h"
#include "memory.h"

void run(void);

void execute_command(int *is_running, image *image);