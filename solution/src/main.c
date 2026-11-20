#include <stdio.h>

#include "cli/arguments.h"
#include "common/error.h"
#include "io/file_reader.h"
#include "io/file_writer.h"
#include "transforms/transform.h"

int main(int argc, char** argv) {
    struct arguments args;

    if (!arguments_parse(argc, argv, &args)) {
        fprintf(stderr,
                "Usage: %s <input.bmp> <output.bmp> "
                "<none|cw90|ccw90|fliph|flipv>\n",
                argv[0]);
        return error_exit_code(STATUS_INVALID_ARGUMENT);
    }

    FILE* input = fopen(args.input_path, "rb");

    if (input == NULL) {
        error_print(STATUS_FILE_NOT_FOUND);
        return error_exit_code(STATUS_FILE_NOT_FOUND);
    }

    struct image original = {0};

    enum status status = from_file(input, &original);

    fclose(input);

    if (status != STATUS_OK) {
        error_print(status);
        return error_exit_code(status);
    }

    struct image transformed =
        transform_apply(&original, args.transformation);

    image_destroy(&original);

    if (transformed.data == NULL) {
        error_print(STATUS_MEMORY_ERROR);
        return error_exit_code(STATUS_MEMORY_ERROR);
    }

    FILE* output = fopen(args.output_path, "wb");

    if (output == NULL) {
        error_print(STATUS_IO_ERROR);
        image_destroy(&transformed);
        return error_exit_code(STATUS_IO_ERROR);
    }

    status = to_file(output, &transformed);

    if (fclose(output) != 0 && status == STATUS_OK) {
        status = STATUS_IO_ERROR;
    }

    image_destroy(&transformed);

    if (status != STATUS_OK) {
        error_print(status);
        return error_exit_code(status);
    }

    return 0;
}
