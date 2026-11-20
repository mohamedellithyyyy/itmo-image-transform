#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

#include "common/status.h"
#include "image/image.h"

enum status from_file(FILE* in, struct image* img);

#endif
