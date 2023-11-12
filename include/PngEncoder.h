#ifndef JLIBHEIF_PNGENCODER_H
#define JLIBHEIF_PNGENCODER_H


#include <cstdint>
#include <vector>

class PngEncoder {
public:
    static bool encode(const struct heif_image_handle *handle,
                       const struct heif_image *image,
                       char **destination,
                       size_t *destination_size,
                       int compression_level);

private:
    static uint8_t *get_exif_metadata(const struct heif_image_handle *handle, size_t *size);

    static std::vector<uint8_t> get_xmp_metadata(const struct heif_image_handle *handle);
};


#endif //JLIBHEIF_PNGENCODER_H
