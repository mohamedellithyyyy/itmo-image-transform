#ifndef FLIP_H
#define FLIP_H

#include "image/image.h"
#include "transforms/flip.h"

#include <stddef.h>

struct image flip_horizontal(const struct image* source);
struct image flip_vertical(const struct image* source);

#endif
