cmake_minimum_required(VERSION 3.16.3)
project(jlibheif)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/main.cpp
        libheif/libheif/exif.cc
        src/PngEncoder.cpp
)

find_package(PNG REQUIRED)
link_directories(${PNG_LIBRARY})

include_directories(libheif)
link_directories(libheif)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC libheif include)
target_link_libraries(${PROJECT_NAME} heif PNG::PNG ${JNI_LIBRARIES})

add_library(HelloJNI SHARED
        src/ru_likhogub_HelloJNI.cc
        libheif/libheif/exif.cc
        src/PngEncoder.cpp)
target_include_directories(HelloJNI PRIVATE ${JNI_INCLUDE_DIRS} libheif include)
target_link_libraries(HelloJNI heif PNG::PNG ${JNI_LIBRARIES})