#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include  "../dep//stb/stb_image_write.h"

#include "vec3.h"
#include "color.h"

int main() {

    // image info

    int image_width = 1920;
    int image_height = 1080;
    int image_channels = 3;

    // image data

    uint8_t * pixels = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * (image_width * image_height * image_channels)));

    // render

    uint32_t current_index = 0;
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color col(double(i) / (image_width-1), double(j) / (image_height-1), 0.75);
            write_color(pixels, i, j, image_width, image_height, col);
        }
    }

    // write to file
    stbi_write_jpg("render.jpg", image_width, image_height, image_channels, pixels, 100);

    free(pixels);
    
    std::cerr << "\nDone.\n";

    return 0;
}