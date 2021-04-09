#pragma once

#include "vec3.h"


void write_color(uint8_t * pixels, int i, int j, int width, int height, color pixel_value) {
    uint8_t * p = pixels;
    if(nullptr != p) {
        int linearized_coord = i + (height - j - 1) * width;
        int r_index = linearized_coord * 3;
        p[r_index] = static_cast<uint8_t>(255.999 * pixel_value.x());
        p[r_index + 1] = static_cast<uint8_t>(255.999 * pixel_value.y());
        p[r_index + 2] = static_cast<uint8_t>(255.999 * pixel_value.z());
    }
    int const channels = 3; // color is vec3
}