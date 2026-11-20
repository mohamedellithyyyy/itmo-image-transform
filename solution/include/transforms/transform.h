#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "cli/transform_parser.h"
#include "image/image.h"

struct image transform_apply(
    const struct image* source,
    enum transformation transformation
);

#endif
