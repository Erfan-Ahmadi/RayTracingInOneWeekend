#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include  "../dep//stb/stb_image_write.h"

#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(ray const & r) {
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int image_channels = 3;

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // image data

    uint8_t * pixels = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * (image_width * image_height * image_channels)));

    // render

    uint32_t current_index = 0;
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {

            double u = double(i) / (image_width-1);
            double v = double(j) / (image_height-1);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);

            write_color(pixels, i, j, image_width, image_height, pixel_color);
        }
    }

    // write to file
    stbi_write_jpg("render.jpg", image_width, image_height, image_channels, pixels, 100);

    free(pixels);
    
    std::cerr << "\nDone.\n";

    return 0;
}