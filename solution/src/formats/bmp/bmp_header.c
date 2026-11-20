#include "formats/bmp/bmp_header.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
bool bmp_header_is_valid(const struct bmp_header* header) {
    if (header == NULL) {
        return false;
    }

    if (header->bfType != 0x4D42) {
        return false;
    }

    if (header->biSize != 40) {
        return false;
    }

    if (header->biWidth <= 0 || header->biHeight == 0) {
        return false;
    }

    if (header->biHeight == INT32_MIN) {
        return false;
    }

    if (header->biPlanes != 1) {
        return false;
    }

    if (header->biBitCount != 24) {
        return false;
    }

    if (header->biCompression != 0) {
        return false;
    }

    return true;
}
