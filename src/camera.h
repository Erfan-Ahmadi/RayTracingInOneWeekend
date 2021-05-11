#pragma once

#include "common.h"

class camera {
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vup,
            double vfov_degrees,
            double aspect_ratio,
            double aperture,
            double focus_distance,
            double _t0 = 0.0,
            double _t1 = 0.0)
        {
            auto theta = degrees_to_radians(vfov_degrees);
            auto h = std::tan(theta / 2.0);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_distance * u * viewport_width;
            vertical = focus_distance * v * viewport_height;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_distance * w;

            lens_radius = aperture / 2.0;

            t0 = _t0;
            t1 = _t1;
        }

        ray get_ray(double s, double t) const {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();
            return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - (origin + offset), random_double(t0, t1));
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
        double t0, t1; // shutter open/close time
};