#pragma once

#include "common.h"
#include "hittable.h"
#include "material.h"
#include "texture.h"

class constant_medium : public hittable {
public:
    constant_medium(std::shared_ptr<hittable> b, double density, std::shared_ptr<texture> t) 
        : boundary(b)
        , neg_inv_density(-1 / density)
        , phase_function(std::make_shared<isotropic>(t))
    {}
    
    constant_medium(std::shared_ptr<hittable> b, double density, color c) 
        : boundary(b)
        , neg_inv_density(-1 / density)
        , phase_function(std::make_shared<isotropic>(c))
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        hit_record rec1, rec2;
        bool ret = false;
        if(boundary->hit(r, -infinity, +infinity, rec1)) {
            if(boundary->hit(r, rec1.t + 0.0001, +infinity, rec2)) {
                if(rec1.t < t_min) rec1.t = t_min;
                if(rec2.t > t_max) rec2.t = t_max;

                if(rec1.t < rec2.t) {
                    if(rec1.t < 0) {
                        rec1.t = 0;
                    }

                    const auto ray_length = r.direction().length();
                    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
                    const auto hit_distance = neg_inv_density * log(random_double());

                    if(hit_distance <= distance_inside_boundary) {
                        rec.t = rec1.t + hit_distance / ray_length;
                        rec.p = r.at(rec.t);
                        rec.normal = vec3(1, 0, 0); // arbitrary
                        rec.front_face = true; // arbitrary
                        rec.mat_ptr = phase_function;
                        ret = true;
                    }
                }
            }
        }
        return ret;
    }

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override {
        return boundary->bounding_box(time0, time1, output_box);
    }

public:
    std::shared_ptr<hittable> boundary;
    std::shared_ptr<material> phase_function;
    double neg_inv_density;
};