#pragma once

#include <cmath>
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
typedef basic_vec3<float> vec3f;

typedef vec3 point3;   // 3D point
typedef vec3 color;    // RGB color