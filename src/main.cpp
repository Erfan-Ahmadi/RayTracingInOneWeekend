#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include  "../dep//stb/stb_image_write.h"

int main() {

    // image info

    uint32_t image_width = 100;
    uint32_t image_height = 100;
    uint32_t image_channels = 4;

    // image data

    uint8_t * pixels = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * (image_width * image_height * image_channels)));

    // render

    uint32_t current_index = 0;
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            uint8_t ir = static_cast<uint8_t>(255.999 * r);
            uint8_t ig = static_cast<uint8_t>(255.999 * g);
            uint8_t ib = static_cast<uint8_t>(255.999 * b);
            uint8_t ia = 255;

            pixels[current_index++] = ir;
            pixels[current_index++] = ig;
            pixels[current_index++] = ib;
            pixels[current_index++] = ia;
        }
    }

    // write to file
    stbi_write_png("render.png", image_width, image_height, image_channels, pixels, image_channels * image_width);

    free(pixels);

    return 0;
}