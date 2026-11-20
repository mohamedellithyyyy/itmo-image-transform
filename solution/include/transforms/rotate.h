#ifndef ROTATE_H
#define ROTATE_H

#include "image/image.h"


struct image rotate_cw90(const struct image* source);
struct image rotate_ccw90(const struct image* source);

#endif
