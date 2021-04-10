#pragma once

#include "vec3.h"
#include "common.h"

void write_color(uint8_t * pixels, int i, int j, int width, int height, int samples_per_pixel, color pixel_value) {
    uint8_t * p = pixels;
    if(nullptr != p) {
        int linearized_coord = i + (height - j - 1) * width;
        int r_index = linearized_coord * 3;

        double scale = 1.0 / samples_per_pixel;
        auto r = std::sqrt(pixel_value.x() * scale);
        auto g = std::sqrt(pixel_value.y() * scale);
        auto b = std::sqrt(pixel_value.z() * scale);

        auto ir = static_cast<int>(256 * clamp(r, 0.0, 0.999));
        auto ig = static_cast<int>(256 * clamp(g, 0.0, 0.999));
        auto ib = static_cast<int>(256 * clamp(b, 0.0, 0.999));

        p[r_index] = ir;
        p[r_index + 1] = ig;
        p[r_index + 2] = ib;
    }
    int const channels = 3; // color is vec3
}