#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r, std::shared_ptr<material> mat) :
        center(cen), radius(r), mat_ptr(mat)
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
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
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        get_sphere_uv(outward_normal, rec.u, rec.v);
        rec.mat_ptr = mat_ptr;

        return true;
    }

    virtual bool bounding_box(double time0, double time1, aabb & output_box) const override {
        output_box = aabb(center - point3(radius, radius, radius), center + point3(radius, radius, radius));
        return true;
    }

private:
    static void get_sphere_uv(point3 const & p, double & u, double & v) {
        auto theta = acos(-p.y());
        auto phi = atan2(-p.z(), p.x()) + pi;

        u = phi / (2 * pi);
        v = theta / (pi);
    }

public:
    point3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;
};