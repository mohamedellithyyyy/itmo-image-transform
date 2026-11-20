#include "image/image.h"

#include <stdint.h>
#include <stdlib.h>

struct image image_create(uint64_t width, uint64_t height) {
    struct image img = {0};

    if (width == 0 || height == 0) {
        return img;
    }

    if (width > SIZE_MAX / height / sizeof(*img.data)) {
        return img;
    }

    img.data = malloc(width * height * sizeof(*img.data));

    if (img.data == NULL) {
        return img;
    }

    img.width = width;
    img.height = height;

    return img;
}

void image_destroy(struct image* img) {
    if (img == NULL) {
        return;
    }

    free(img->data);

    img->data = NULL;
    img->width = 0;
    img->height = 0;
}
