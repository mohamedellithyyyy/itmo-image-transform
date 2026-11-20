#include "cli/transform_parser.h"

#include <string.h>

int transform_parse(const char* text, enum transformation* result) {
    if (text == NULL || result == NULL) {
        return 0;
    }

    if (strcmp(text, "none") == 0) {
        *result = TRANSFORM_NONE;
    } else if (strcmp(text, "cw90") == 0) {
        *result = TRANSFORM_CW90;
    } else if (strcmp(text, "ccw90") == 0) {
        *result = TRANSFORM_CCW90;
    } else if (strcmp(text, "fliph") == 0) {
        *result = TRANSFORM_FLIPH;
    } else if (strcmp(text, "flipv") == 0) {
        *result = TRANSFORM_FLIPV;
    } else {
        return 0;
    }

    return 1;
}
