#include <iostream>
#include <libheif/heif.h>
#include "encoder_png.h"

using namespace std;

int main() {
    cout << "Hello world! " << endl;
    heif_context* ctx = heif_context_alloc();
    heif_context_read_from_file(ctx, "/home/olikhogub/Downloads/sample1.heic", nullptr);
    heif_image_handle* handle;
    heif_context_get_primary_image_handle(ctx, &handle);

    heif_image* img;
    heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
    std::unique_ptr<Encoder> encoder;

    auto pngEncoder = new PngEncoder();
    pngEncoder->set_compression_level(5);
    encoder.reset(pngEncoder);
    encoder->Encode(handle, img, "/home/olikhogub/Downloads/sample1.png");
    heif_image_release(img);
    heif_image_handle_release(handle);
    return 0;
}