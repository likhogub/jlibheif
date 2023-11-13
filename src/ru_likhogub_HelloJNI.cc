#include <jni.h>
#include <memory>
#include "ru_likhogub_HelloJNI.h"
#include "libheif/heif.h"
#include "PngEncoder.h"


JNIEXPORT jobject JNICALL Java_ru_likhogub_HelloJNI_sayHello(JNIEnv *env, jobject, jbyteArray input) {
    jsize length = env->GetArrayLength(input);
    jbyte *bytes = env->GetByteArrayElements(input, nullptr);

    heif_context* ctx = heif_context_alloc();
    heif_context_read_from_memory_without_copy(ctx, bytes, length, nullptr);
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
    return env->NewDirectByteBuffer(buffer, (jsize) size);
}
