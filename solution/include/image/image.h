#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"

#include <stdint.h>

struct image {
    uint64_t width;
    uint64_t height;
    struct pixel* data;
};

/* Image memory management */
struct image image_create(uint64_t width, uint64_t height);
void image_destroy(struct image* img);

#endif
