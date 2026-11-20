#include "formats/bmp/bmp_padding.h"

uint8_t bmp_padding(uint64_t width) {
    // P = (4 - (3w % 4)) % 4

    const uint8_t bytes_per_pixel = 3;
    const uint8_t row_alignment = 4;

    // R = (3 * (w % 4)) % 4
    const uint8_t remainder =
        (bytes_per_pixel * (width % row_alignment)) % row_alignment;

    // P = (4 - R) % 4
    const uint8_t padding =
        (row_alignment - remainder) % row_alignment;

    return padding;
}
