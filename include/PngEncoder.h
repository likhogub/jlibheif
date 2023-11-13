#ifndef JLIBHEIF_PNGENCODER_H
#define JLIBHEIF_PNGENCODER_H


#include <cstdint>
#include <vector>

class PngEncoder {
public:
    static bool encode(const struct heif_image *image,
                       char **destination,
                       size_t *destination_size,
                       int compression_level);
};


#endif //JLIBHEIF_PNGENCODER_H
