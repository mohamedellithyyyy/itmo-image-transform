#include "transforms/transform.h"

#include "transforms/copy.h"
#include "transforms/flip.h"
#include "transforms/rotate.h"

struct image transform_apply(
    const struct image* source,
    enum transformation transformation
) {
    switch (transformation) {
        case TRANSFORM_NONE:
            return image_copy(source);

        case TRANSFORM_CW90:
            return rotate_cw90(source);

        case TRANSFORM_CCW90:
            return rotate_ccw90(source);

        case TRANSFORM_FLIPH:
            return flip_horizontal(source);

        case TRANSFORM_FLIPV:
            return flip_vertical(source);

        default:
            return (struct image){0};
    }
}
