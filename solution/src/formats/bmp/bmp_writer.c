#include "formats/bmp/bmp_writer.h"

#include "formats/bmp/bmp_header.h"
#include "formats/bmp/bmp_padding.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


enum status to_bmp(FILE* out, const struct image* img) {

    /* 1. Validate arguments */
    if (out == NULL || img == NULL || img->data == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }
    if (img->width == 0 || img->height == 0) {
        return STATUS_INVALID_ARGUMENT;
    }
    /* 2. Check dimensions */
    if (img->width > INT32_MAX || img->height > INT32_MAX) {
        return STATUS_INVALID_FORMAT;
    }
    /* 3. Calculate row size and padding */
    const uint64_t padding = bmp_padding(img->width);
    if (img->width > (UINT64_MAX - padding) / 3) {
        return STATUS_INVALID_FORMAT;
    }
    const uint64_t row_size = img->width * 3 + padding;
    /* 4. Calculate image data size */
    if (row_size > UINT64_MAX / img->height) {
        return STATUS_INVALID_FORMAT;
    }
    const uint64_t image_size = row_size * img->height;
    /* 5. Calculate total BMP file size */
    const uint64_t header_size = 54;
    const uint64_t file_size = header_size + image_size;
    if (file_size > UINT32_MAX) {
        return STATUS_INVALID_FORMAT;
    }
    /* 6. Create BMP header */
    struct bmp_header header = {0};
    header.bfType = 0x4D42;
    header.bfSize = (uint32_t) file_size;
    header.bfOffBits = (uint32_t) header_size;

    header.biSize = 40;
    header.biWidth = (int32_t) img->width;
    header.biHeight = (int32_t) img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = (uint32_t) image_size;

    /* 7. Write BMP header */
    if (fwrite(&header, sizeof(header), 1, out) != 1) {
        return STATUS_IO_ERROR;
    }
    /* 8. Write pixel data */
    const uint8_t zero_padding[3] = {0, 0, 0};
    for (uint64_t y = img->height; y > 0; y--) {

        const uint64_t row = y - 1;

        for (uint64_t x = 0; x < img->width; x++) {

            const uint64_t index = row * img->width + x;

            const struct pixel* pixel = &img->data[index];

            const uint8_t bgr[3] = {
                pixel->b,
                pixel->g,
                pixel->r
            };
            if (fwrite(bgr, sizeof(bgr), 1, out) != 1) {
                return STATUS_IO_ERROR;
            }
        }
        /* 9. Write row padding */
        if (padding > 0) {
            if (fwrite(zero_padding, 1, padding, out) != padding) {
                return STATUS_IO_ERROR;
            }
        }
    }
    return STATUS_OK;
}
