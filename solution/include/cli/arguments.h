#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "cli/transform_parser.h"

struct arguments {
    const char* input_path;
    const char* output_path;
    enum transformation transformation;
};

int arguments_parse(int argc, char** argv, struct arguments* args);

#endif
