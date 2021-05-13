#pragma once

#include "common.h"
#include "hittable.h"

class xy_rect : public hittable {
public:
    xy_rect() {}
    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<material> mat) :
        x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_ptr(mat)
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        
        double t = (k - r.origin().z()) / r.direction().z();
        
        if(t < t_min || t > t_max) {
            return false;
        }

        auto r_at_t = r.at(t);
        auto x = r_at_t.x();
        auto y = r_at_t.y();

        if(x < x0 || x > x1 || y < y0 || y > y1) {
            return false;
        }

        rec.u = (x-x0)/(x1-x0);
        rec.v = (y-y0)/(y1-y0);
        rec.t = t;

        auto outward_normal = vec3(0, 0, 1);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;
        rec.p = r_at_t;

        return true;
    }

    virtual bool bounding_box(double time0, double time1, aabb & output_box) const override {
        output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
        return true;
    }

public:
    double x0, x1, y0, y1, k;
    std::shared_ptr<material> mat_ptr;
};

class xz_rect : public hittable {
public:
    xz_rect() {}
    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<material> mat) :
        x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat_ptr(mat)
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        
        double t = (k - r.origin().y()) / r.direction().y();
        
        if(t < t_min || t > t_max) {
            return false;
        }

        auto r_at_t = r.at(t);
        auto x = r_at_t.x();
        auto z = r_at_t.z();

        if(x < x0 || x > x1 || z < z0 || z > z1) {
            return false;
        }

        rec.u = (x-x0)/(x1-x0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;

        auto outward_normal = vec3(0, 1, 0);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;
        rec.p = r_at_t;

        return true;
    }

    virtual bool bounding_box(double time0, double time1, aabb & output_box) const override {
        output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
        return true;
    }

public:
    double x0, x1, z0, z1, k;
    std::shared_ptr<material> mat_ptr;
};

class yz_rect : public hittable {
public:
    yz_rect() {}
    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<material> mat) :
        y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat_ptr(mat)
    {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        
        double t = (k - r.origin().x()) / r.direction().x();
        
        if(t < t_min || t > t_max) {
            return false;
        }

        auto r_at_t = r.at(t);
        auto y = r_at_t.y();
        auto z = r_at_t.z();

        if(y < y0 || y > y1 || z < z0 || z > z1) {
            return false;
        }

        rec.u = (y-y0)/(y1-y0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;

        auto outward_normal = vec3(1, 0, 0);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;
        rec.p = r_at_t;

        return true;
    }

    virtual bool bounding_box(double time0, double time1, aabb & output_box) const override {
        output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
        return true;
    }

public:
    double y0, y1, z0, z1, k;
    std::shared_ptr<material> mat_ptr;
};