#include <iostream>
#include <libheif/heif.h>
#include <memory>
#include "PngEncoder.h"

using namespace std;

int main() {
    cout << "Hello world! " << endl;
    heif_context* ctx = heif_context_alloc();
    heif_context_read_from_file(ctx, "/home/olikhogub/Downloads/sample1.heic", nullptr);
    heif_image_handle* handle;
    heif_context_get_primary_image_handle(ctx, &handle);

    heif_image* img;
    heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
    std::unique_ptr<PngEncoder> pngEncoder;

    char* buffer = nullptr;
    size_t size = 0;
    pngEncoder->encode(img, &buffer, &size, 9);
    heif_image_release(img);
    heif_image_handle_release(handle);
    return 0;
}