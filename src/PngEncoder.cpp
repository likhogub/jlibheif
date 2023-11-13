#include <png.h>
#include "PngEncoder.h"
#include <libheif/heif.h>
#include <cstdlib>
#include <cstring>

struct mem_encode {
    char *buffer;
    size_t size;
};

void my_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length) {
    auto *p = (struct mem_encode *) png_get_io_ptr(png_ptr);
    size_t nsize = p->size + length;
    if (p->buffer) {
        p->buffer = (char *) realloc(p->buffer, nsize);
    } else {
        p->buffer = (char *) malloc(nsize);
    }
    if (!p->buffer) {
        png_error(png_ptr, "Write Error");
    }
    memcpy(p->buffer + p->size, data, length);
    p->size += length;
}

bool PngEncoder::encode(const struct heif_image *image,
                        char **destination,
                        size_t *destination_size,
                        int compression_level) {
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr,
                                                  nullptr, nullptr);
    if (!png_ptr) {
        fprintf(stderr, "libpng initialization failed (1)\n");
        return false;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        fprintf(stderr, "libpng initialization failed (2)\n");
        return false;
    }

    if (compression_level != -1) {
        png_set_compression_level(png_ptr, compression_level);
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fprintf(stderr, "Error while encoding image\n");
        return false;
    }

    bool withAlpha = (heif_image_get_chroma_format(image) == heif_chroma_interleaved_RGBA ||
                      heif_image_get_chroma_format(image) == heif_chroma_interleaved_RRGGBBAA_BE);

    int width = heif_image_get_width(image, heif_channel_interleaved);
    int height = heif_image_get_height(image, heif_channel_interleaved);

    int bitDepth;
    int input_bpp = heif_image_get_bits_per_pixel_range(image, heif_channel_interleaved);
    if (input_bpp > 8) {
        bitDepth = 16;
    } else {
        bitDepth = 8;
    }

    const int colorType = withAlpha ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB;

    png_set_IHDR(png_ptr, info_ptr, width, height, bitDepth, colorType,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    uint8_t **row_pointers = new uint8_t *[height];

    int stride_rgb;
    const uint8_t *row_rgb = heif_image_get_plane_readonly(image,
                                                           heif_channel_interleaved, &stride_rgb);

    for (int y = 0; y < height; ++y) {
        row_pointers[y] = const_cast<uint8_t *>(&row_rgb[y * stride_rgb]);
    }

    if (bitDepth == 16) {
        // shift image data to full 16bit range

        int shift = 16 - input_bpp;
        if (shift > 0) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < stride_rgb; x += 2) {
                    uint8_t *p = (&row_pointers[y][x]);
                    int v = (p[0] << 8) | p[1];
                    v = (v << shift) | (v >> (16 - shift));
                    p[0] = (uint8_t) (v >> 8);
                    p[1] = (uint8_t) (v & 0xFF);
                }
            }
        }
    }

    png_set_rows(png_ptr, info_ptr, row_pointers);
    mem_encode state{};
    png_set_write_fn(png_ptr, &state, my_png_write_data, nullptr);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

    *destination = state.buffer;
    *destination_size = state.size;

    delete[] row_pointers;
    return true;
}