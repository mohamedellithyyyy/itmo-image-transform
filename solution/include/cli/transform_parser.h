#ifndef TRANSFORM_PARSER_H
#define TRANSFORM_PARSER_H

enum transformation {
    TRANSFORM_NONE,
    TRANSFORM_CW90,
    TRANSFORM_CCW90,
    TRANSFORM_FLIPH,
    TRANSFORM_FLIPV
};

int transform_parse(const char* text, enum transformation* result);

#endif
