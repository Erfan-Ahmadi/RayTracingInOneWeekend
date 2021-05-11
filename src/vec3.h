#pragma once

#include <cmath>
#include <math.h>
#include <iostream>

template <typename T>
class basic_vec3 {
public:
    basic_vec3() : e{0, 0, 0} {}
    basic_vec3(T e0, T e1, T e2) : e{e0, e1, e2} {}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    basic_vec3<T> operator-() const { return basic_vec3(-1*e[0], -1*e[1], -1*e[2]); }
    T operator[](int i) const { return e[i]; }
    T& operator[](int i) { return e[i]; }

    template <typename U>
    basic_vec3<T>& operator+=(const basic_vec3<U>& v) {
        e[0] += static_cast<T>(v.e[0]);
        e[1] += static_cast<T>(v.e[1]);
        e[2] += static_cast<T>(v.e[2]);
        return *this;
    }
    
    template <typename U>
    basic_vec3<T>& operator*=(const basic_vec3<U>& v) {
        e[0] *= static_cast<T>(v.e[0]);
        e[1] *= static_cast<T>(v.e[1]);
        e[2] *= static_cast<T>(v.e[2]);
        return *this;
    }
    
    basic_vec3<T>& operator*=(double const t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    basic_vec3<T>& operator/=(double const t) {
        return *this *= 1/t;
    }

    T length() const {
        return std::sqrt(length_squared());
    }

    T length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    inline static basic_vec3<T> random() {
        return basic_vec3<T>(random_double(), random_double(), random_double()); // fix later
    }

    inline static basic_vec3<T> random(double min, double max) {
        return basic_vec3<T>(random_double(min,max), random_double(min,max), random_double(min,max)); // fix later
    }

public:
    T e[3];
};

// vec3 Utility Functions

template <typename T>
inline std::ostream& operator<<(std::ostream &out, const basic_vec3<T> &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template <typename T>
inline basic_vec3<T> operator+(const basic_vec3<T> &u, const basic_vec3<T> &v) {
    return basic_vec3<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template <typename T>
inline basic_vec3<T> operator-(const basic_vec3<T> &u, const basic_vec3<T> &v) {
    return basic_vec3<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template <typename T>
inline basic_vec3<T> operator*(const basic_vec3<T> &u, const basic_vec3<T> &v) {
    return basic_vec3<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template <typename T>
inline basic_vec3<T> operator*(double t, const basic_vec3<T> &v) {
    return basic_vec3<T>(t*v.e[0], t*v.e[1], t*v.e[2]);
}

template <typename T>
inline basic_vec3<T> operator*(const basic_vec3<T> &v, double t) {
    return t * v;
}

template <typename T>
inline basic_vec3<T> operator/(basic_vec3<T> v, double t) {
    return (1/t) * v;
}

template <typename T>
inline double dot(const basic_vec3<T> &u, const basic_vec3<T> &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

template <typename T>
inline basic_vec3<T> cross(const basic_vec3<T> &u, const basic_vec3<T> &v) {
    return basic_vec3<T>(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

template <typename T>
inline basic_vec3<T> unit_vector(basic_vec3<T> v) {
    return v / v.length();
}

typedef basic_vec3<double> vec3;

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vec3 reflect(const vec3 & v, const vec3 & n) {
    return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3 & uv, const vec3 & n, const double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-1.0 * uv, n), 1.0);
    vec3 perpendicular = etai_over_etat * (uv + cos_theta * n);
    vec3 parallel = -1.0 * std::sqrt(std::fabs(1.0 - perpendicular.length_squared())) * n;
    return parallel + perpendicular;
}

typedef vec3 point3;   // 3D point
typedef vec3 color;    // RGB color