#pragma once

#include <cmath>

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

    basic_vec3<T>& operator/=(const double t) {
        return *this *= 1/t;
    }

    T length() const {
        return std::sqrt(length_squared());
    }

    T length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

public:
    T e[3];
};

typedef basic_vec3<double> vec3;
typedef basic_vec3<float> vec3f;