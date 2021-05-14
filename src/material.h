#pragma once

#include "common.h"
#include "texture.h"

struct hit_record;

class material {
public:
    virtual color emitted(double u, double v, const point3& p) const {
        return color(0,0,0);
    }
    virtual bool scatter(const ray & r_in, const hit_record & rec, color & attenuation, ray & scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(std::make_shared<solid_color>(a)) {}
    lambertian(std::shared_ptr<texture> a) : albedo(a) {}

    virtual bool scatter(const ray & r_in, const hit_record & rec, color & attenuation, ray & scattered) const override {
        vec3 scatter_direction = rec.normal + random_unit_vector();

        if(scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

public:
    std::shared_ptr<texture> albedo;
};

class metal : public material {
public:
    metal(const color& a, double f) : albedo(a), fuzz((f < 1) ? f : 1) {}

    virtual bool scatter(const ray & r_in, const hit_record & rec, color & attenuation, ray & scattered) const override {
        vec3 reflected_direction = reflect(unit_vector(r_in.dir), rec.normal);
        scattered = ray(rec.p, reflected_direction + fuzz * random_in_unit_sphere(), r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(const ray & r_in, const hit_record & rec, color & attenuation, ray & scattered) const override {
        attenuation = color(1, 1, 1);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        double cos_theta = std::fmin(dot(rec.normal, -1.0 * r_in.direction()), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
        vec3 unit_direction = unit_vector(r_in.direction());

        bool cant_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;

        if(cant_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
            // reflect
            direction = reflect(unit_direction, rec.normal);
        } else {
            // refract
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = ray(rec.p, direction, r_in.time());
        return true;
    }

public:
    double ir; // index of refraction

private:
    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

class diffuse_light : public material {
public:
    diffuse_light(std::shared_ptr<texture> a) : emit(a) {}
    diffuse_light(color c) : emit(std::make_shared<solid_color>(c)) {}

    virtual bool scatter(ray const & r_in, hit_record const & rec, color & attenuation, ray & scattered) const override {
        return false;
    }
    
    virtual color emitted(double u, double v, const point3& p) const override {
        return emit->value(u, v, p);
    }

public:
    std::shared_ptr<texture> emit;

};

class isotropic : public material {
    public:
        isotropic(color c) : albedo(std::make_shared<solid_color>(c)) {}
        isotropic(std::shared_ptr<texture> a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

    public:
        std::shared_ptr<texture> albedo;
};