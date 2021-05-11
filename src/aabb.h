#pragma once

#include "common.h"

class aabb {
public:

    aabb() {}
    aabb(point3 const & min, point3 const & max)
        : minimum(min)
        , maximum(max)
    {

    }

    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    inline bool hit(const ray& r, double t_min, double t_max) const {
        for (int a = 0; a < 3; ++a) {
            auto invD = 1.0f / r.direction()[a];
            auto t0 = (minimum[a] - r.origin()[a]) * invD;
            auto t1 = (maximum[a] - r.origin()[a]) * invD;
            if(invD < 0.0f) {
                std::swap(t0, t1);
            }
            t_min = (t0 > t_min) ? t0 : t_min;
            t_max = (t1 > t_max) ? t_max : t1;
            
            if(t_max <= t_min) {
                return false;
            }
        }
        return true;
    }

public:

    point3 minimum;
    point3 maximum;
};

aabb surrounding_box(aabb box0, aabb box1) {
    point3 new_min = point3(
        fmin(box0.min().x(), box1.min().x()),
        fmin(box0.min().y(), box1.min().y()),
        fmin(box0.min().z(), box1.min().z()));
    point3 new_max = point3(
        fmax(box0.max().x(), box1.max().x()),
        fmax(box0.max().y(), box1.max().y()),
        fmax(box0.max().z(), box1.max().z()));

    return aabb(new_min, new_max);
}