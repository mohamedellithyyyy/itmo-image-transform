
#include "formats/bmp/bmp_reader.h"

#include "common/status.h"
#include "formats/bmp/bmp_header.h"
#include "formats/bmp/bmp_padding.h"
#include "image/image.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

enum status from_bmp(FILE* in, struct image* img) {
    /* 1. Validate function arguments */
    if (in == NULL || img == NULL) {
        return STATUS_INVALID_ARGUMENT;
    }

    *img = (struct image){0};

    /* 2. Read BMP header */
    struct bmp_header header;

    if (fread(&header, sizeof(header), 1, in) != 1) {
        return STATUS_IO_ERROR;
    }

    /* 3. Validate BMP header */
    if (!bmp_header_is_valid(&header)) {
        return STATUS_INVALID_FORMAT;
    }

    /* 4. Validate pixel data offset */
    if (header.bfOffBits < sizeof(header)) {
        return STATUS_INVALID_FORMAT;
    }

    if ((uint64_t) header.bfOffBits > (uint64_t) LONG_MAX) {
        return STATUS_INVALID_FORMAT;
    }

    /* 5. Extract image dimensions */
    const uint64_t width = (uint64_t) header.biWidth;

    const int64_t signed_height = header.biHeight;

    const uint64_t height = signed_height < 0
        ? (uint64_t) (-signed_height)
        : (uint64_t) signed_height;

    const int is_top_down = signed_height < 0;

    /* 6. Calculate required pixel data size */
    const uint64_t padding = bmp_padding(width);

    if (width > (UINT64_MAX - padding) / 3) {
        return STATUS_INVALID_FORMAT;
    }

    const uint64_t row_size = width * 3 + padding;

    if (height > (UINT64_MAX - header.bfOffBits) / row_size) {
        return STATUS_INVALID_FORMAT;
    }

    const uint64_t required_size =
        (uint64_t) header.bfOffBits + row_size * height;

    /* 7. Allocate image memory */
    struct image result = image_create(width, height);

    if (result.data == NULL) {
        return STATUS_MEMORY_ERROR;
    }

    /* 8. Check actual file size */
    if (fseek(in, 0, SEEK_END) != 0) {
        image_destroy(&result);
        return STATUS_IO_ERROR;
    }

    const long file_size = ftell(in);

    if (file_size < 0) {
        image_destroy(&result);
        return STATUS_IO_ERROR;
    }

    if ((uint64_t) file_size < required_size) {
        image_destroy(&result);
        return STATUS_INVALID_FORMAT;
    }

    /* 9. Move to pixel data */
    if (fseek(in, (long) header.bfOffBits, SEEK_SET) != 0) {
        image_destroy(&result);
        return STATUS_IO_ERROR;
    }
    /* 10. Read pixel data */
    for (uint64_t file_y = 0; file_y < height; file_y++) {
        const uint64_t y = is_top_down
            ? file_y
            : height - 1 - file_y;

        for (uint64_t x = 0; x < width; x++) {
            uint8_t bgr[3];

            if (fread(bgr, sizeof(uint8_t), 3, in) != 3) {
                image_destroy(&result);
                return STATUS_IO_ERROR;
            }

            result.data[y * width + x] = (struct pixel) {
                .b = bgr[0],
                .g = bgr[1],
                .r = bgr[2]
            };
        }

        /* 11. Skip row padding */
        if (padding > 0) {
            uint8_t padding_bytes[3];

            if (fread(padding_bytes, 1, padding, in) != padding) {
                image_destroy(&result);
                return STATUS_IO_ERROR;
            }
        }
    }

    /* 12. Return the completed image */
    *img = result;

    return STATUS_OK;
}
