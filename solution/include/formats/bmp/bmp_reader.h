
#ifndef BMP_READER_H
#define BMP_READER_H

#include <stdio.h>

#include "common/status.h"
#include "image/image.h"

/* Read a BMP file into an internal image */
enum status from_bmp(FILE* in, struct image* img);

#endif
