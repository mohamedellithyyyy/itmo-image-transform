#include "transforms/rotate.h"

#include <stddef.h>
struct image rotate_cw90(const struct image* source) {
    if (source == NULL || source->data == NULL) {
        return (struct image){0};
    }

    struct image result = image_create(source->height, source->width);

    if (result.data == NULL) {
        return (struct image){0};
    }

    for (uint64_t y = 0; y < source->height; y++) {
        for (uint64_t x = 0; x < source->width; x++) {
            uint64_t new_x = source->height - 1 - y;
            uint64_t new_y = x;

            result.data[new_y * result.width + new_x] =
                source->data[y * source->width + x];
        }
    }

    return result;
}

struct image rotate_ccw90(const struct image* source) {
    if (source == NULL || source->data == NULL) {
        return (struct image){0};
    }

    struct image result = image_create(source->height, source->width);

    if (result.data == NULL) {
        return (struct image){0};
    }

    for (uint64_t y = 0; y < source->height; y++) {
        for (uint64_t x = 0; x < source->width; x++) {
            uint64_t new_x = y;
            uint64_t new_y = source->width - 1 - x;

            result.data[new_y * result.width + new_x] =
                source->data[y * source->width + x];
        }
    }

    return result;
}
