cmake_minimum_required(VERSION 3.16.3)
project(jlibheif)

set(CMAKE_CXX_STANDARD 17)


include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

# check for libpng
pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
    include_directories (${LIBPNG_INCLUDE_DIRS})
    link_directories (${LIBPNG_LIBRARY_DIRS})
    link_libraries (${LIBPNG_LIBRARIES})
endif ()
add_executable(${PROJECT_NAME} src/main.cpp ${LIBPNG_LINK_FLAGS})

add_subdirectory(external/libheif)
target_include_directories(${PROJECT_NAME} PUBLIC ${libheif_BINARY_DIR} ${libheif_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} heif)

target_sources(${PROJECT_NAME} PUBLIC
        src/encoder_png.cc
        src/encoder_png.h
        src/encoder.h
        src/encoder.cc)

#include_directories(external/libpng)

#FetchContent_Declare(
#        zlib
#        GIT_REPOSITORY https://github.com/madler/zlib
#        FIND_PACKAGE_ARGS NAMES ZLIB
#)
#FetchContent_MakeAvailable(zlib)
#
#add_subdirectory(external/zlib)
#target_include_directories(jlibheif PUBLIC ${zlib_BINARY_DIR} ${zlib_SOURCE_DIR})
#target_link_libraries(jlibheif zlib)

#
#
#
#FetchContent_Declare(
#        libpng
#        GIT_REPOSITORY https://github.com/glennrp/libpng
#        GIT_TAG v1.6.37
#)
#FetchContent_MakeAvailable(libpng)
#include_directories(
#        ${libpng_SOURCE_DIR}
#        ${libpng_BINARY_DIR}
#)
#add_subdirectory(external/libpng)
#target_include_directories(jlibheif PUBLIC external/libpng)
#target_link_libraries(jlibheif png)

#find_package(PNG REQUIRED)
#include_directories(${PNG_INCLUDE_DIR})
#target_link_libraries(jlibheif ${PNG_LIBRARY})
#
#find_package(ZLIB REQUIRED)
#include_directories(${ZLIB_INCLUDE_DIR})
#target_link_libraries(jlibheif ${ZLIB_LIBRARY})


#find_package(PNG)
#if (TARGET PNG::PNG)
#    add_definitions(-DHAVE_LIBPNG=1)
#
#    target_link_libraries(jlibheif PNG::PNG)
#
#    target_sources(jlibheif PRIVATE
#            src/encoder_png.cc
#            src/encoder_png.h
#            src/encoder.h
#            src/encoder.cc)
#
##    install(TARGETS heif-thumbnailer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
##    install(FILES heif-thumbnailer.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
#endif ()