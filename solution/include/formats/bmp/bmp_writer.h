#ifndef BMP_WRITER_H
#define BMP_WRITER_H

#include <stdio.h>

#include "common/status.h"
#include "image/image.h"

/* Write an internal image into a BMP file */
enum status to_bmp(FILE* out, const struct image* img);

#endif
