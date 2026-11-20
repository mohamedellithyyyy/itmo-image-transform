#include "io/file_writer.h"

#include "formats/bmp/bmp_writer.h"

enum status to_file(FILE* out, const struct image* img) {

    //Validate arguments
    if (out == NULL || img == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    // Write image using BMP format
    return to_bmp(out, img);
}
