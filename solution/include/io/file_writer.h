#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "common/status.h"
#include "image/image.h"

#include <stdio.h>


enum status to_file(FILE* out, const struct image* img);

#endif
