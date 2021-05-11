#pragma once

#include "common.h"
#include "perlin.h"

class texture {
public:
    virtual color value(double u, double v, point3 const & p) const = 0;
};

class solid_color : public texture {
public:
    solid_color() {};
    solid_color(color const & c) : color_value(c) {}

    solid_color(double r, double g, double b)
        : solid_color(color(r, g, b))
    {}

    virtual color value(double u, double v, point3 const & p) const override {
        return color_value;
    }

public:
    color color_value;
};

class checker_texture : public texture {
public:
    checker_texture() {};

    checker_texture(std::shared_ptr<texture> t1, std::shared_ptr<texture> t2) 
        : odd_texture(t1) 
        , even_texture(t2)
    {}

    checker_texture(color const & c1, color const & c2) 
        : checker_texture(std::make_shared<solid_color>(c1), std::make_shared<solid_color>(c2)) 
    {}

    virtual color value(double u, double v, point3 const & p) const override {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if(sines < 0) {
            return odd_texture->value(u, v, p);
        } else {
            return even_texture->value(u, v, p);
        }
    }

public:
    std::shared_ptr<texture> odd_texture;
    std::shared_ptr<texture> even_texture;
};

class noise_texture : public texture {
public:
    noise_texture() {}
    noise_texture(double sc) : scale(sc) {}
    
    virtual color value(double u, double v, point3 const & p) const override {
        return color(1, 1, 1) * 0.5 * (1.0 + sin(scale * p.z() + 10*noise.turb(p)));
    }

public:
    perlin noise;
    double scale;
};