#include "transforms/flip.h"

struct image flip_horizontal(const struct image* source) {
    if (source == NULL || source->data == NULL) {
        return (struct image){0};
    }

    struct image result = image_create(source->width, source->height);

    if (result.data == NULL) {
        return (struct image){0};
    }

    for (uint64_t y = 0; y < source->height; y++) {
        for (uint64_t x = 0; x < source->width; x++) {
            uint64_t new_x = source->width - 1 - x;

            result.data[y * result.width + new_x] =
                source->data[y * source->width + x];
        }
    }

    return result;
}

struct image flip_vertical(const struct image* source) {
    if (source == NULL || source->data == NULL) {
        return (struct image){0};
    }

    struct image result = image_create(source->width, source->height);

    if (result.data == NULL) {
        return (struct image){0};
    }

    for (uint64_t y = 0; y < source->height; y++) {
        uint64_t new_y = source->height - 1 - y;

        for (uint64_t x = 0; x < source->width; x++) {
            result.data[new_y * result.width + x] =
                source->data[y * source->width + x];
        }
    }

    return result;
}
