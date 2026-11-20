#include "io/file_reader.h"

#include "formats/bmp/bmp_reader.h"

enum status from_file(FILE* in, struct image* img) {
    if (in == NULL || img == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }
    return from_bmp(in, img);
}
