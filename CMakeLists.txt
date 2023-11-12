cmake_minimum_required(VERSION 3.16.3)
project(jlibheif)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/encoder.cc
        src/encoder_png.cc
        libheif/libheif/exif.cc)

find_package(PNG REQUIRED)
link_directories(${PNG_LIBRARY})

include_directories(libheif)
link_directories(libheif)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC libheif include ${JNI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} heif PNG::PNG ${JNI_LIBRARIES})
