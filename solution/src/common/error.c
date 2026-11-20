#include "common/error.h"

#include <errno.h>
#include <stdio.h>

void error_print(enum status status) {
    switch (status) {
        case STATUS_OK:
            break;

        case STATUS_FILE_NOT_FOUND:
            fprintf(stderr, "Error: Input file not found.\n");
            break;

        case STATUS_INVALID_ARGUMENT:
            fprintf(stderr, "Error: Invalid argument.\n");
            break;

        case STATUS_INVALID_FORMAT:
            fprintf(stderr, "Error: Invalid file format.\n");
            break;

        case STATUS_IO_ERROR:
            fprintf(stderr, "Error: File input/output operation failed.\n");
            break;

        case STATUS_MEMORY_ERROR:
            fprintf(stderr, "Error: Memory allocation failed.\n");
            break;

        default:
            fprintf(stderr, "Error: Unknown error.\n");
            break;
    }
}

int error_exit_code(enum status status) {
    switch (status) {
        case STATUS_OK:
            return 0;

        case STATUS_FILE_NOT_FOUND:
            return ENOENT;

        case STATUS_IO_ERROR:
            return EIO;

        case STATUS_MEMORY_ERROR:
            return ENOMEM;

        case STATUS_INVALID_ARGUMENT:
        case STATUS_INVALID_FORMAT:
        default:
            return EINVAL;
    }
}
