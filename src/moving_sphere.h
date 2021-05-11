#pragma once

#include "hittable.h"

class moving_sphere : public hittable {
public:
    moving_sphere() {}
    moving_sphere(point3 cen0, point3 cen1, double t0, double t1, double r, std::shared_ptr<material> mat) : 
        center0(cen0),
        center1(cen1),
        time0(t0),
        time1(t1),
        radius(r),
        mat_ptr(mat)
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center(r.time());
        double a = r.direction().length_squared();
        double half_b = dot(oc, r.direction());
        double c = oc.length_squared() - radius * radius;
        
        double discriminant = half_b * half_b - a * c;

        if(discriminant < 0) return false;
        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if(root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if(root < t_min || t_max < root) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center(r.time())) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;

        return true;
    }
    
    virtual bool bounding_box(double time0, double time1, aabb & output_box) const override {
        aabb box_t0 = aabb(center(time0) - point3(radius, radius, radius), center(time0) + point3(radius, radius, radius));
        aabb box_t1 = aabb(center(time1) - point3(radius, radius, radius), center(time1) + point3(radius, radius, radius));
        output_box = surrounding_box(box_t0, box_t1);
        return true;
    }

    point3 center(double time) const {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }

public:
    point3 center0, center1;
    double time0, time1;
    double radius;
    std::shared_ptr<material> mat_ptr;
};