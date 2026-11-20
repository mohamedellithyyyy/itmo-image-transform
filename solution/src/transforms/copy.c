#include "transforms/copy.h"

#include <stddef.h>

struct image image_copy(const struct image* source) {
    if (source == NULL || source->data == NULL) {
        return (struct image){0};
    }

    struct image copy = image_create(source->width, source->height);

    if (copy.data == NULL) {
        return (struct image){0};
    }

    for (uint64_t i = 0; i < source->width * source->height; i++) {
        copy.data[i] = source->data[i];
    }

    return copy;
}
