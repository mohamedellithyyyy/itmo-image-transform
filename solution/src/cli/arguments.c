#include "cli/arguments.h"
#include <stddef.h>
int arguments_parse(int argc, char** argv, struct arguments* args) {
    if (argc != 4 || argv == NULL || args == NULL) {
        return 0;
    }

    args->input_path = argv[1];
    args->output_path = argv[2];

    return transform_parse(argv[3], &args->transformation);
}
