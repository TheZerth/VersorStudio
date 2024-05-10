//
// Created by zerth on 07/05/24.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// The vector class used in VersorStudio, a 3D vector class with Gibbs notation.
// Named after Josiah Willard Gibbs, considered one of the fathers of "vector algebra".
// A brilliant physicist and mathematician. Oversimplified vectors to make them easier.
// But at the cost of losing some of the geometric properties of vectors.
class Gibbs {
public:
    float x, y, z;

    Gibbs(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

//---------OPERATORS---------
public:
    // Addition
    Gibbs operator+(const Gibbs& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    // Subtraction
    Gibbs operator-(const Gibbs& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    // Scalar Multiplication
    Gibbs operator*(const float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    // Scalar Division
    Gibbs operator/(const float scalar) const {
        if (scalar != 0.0f) {
            return {x / scalar, y / scalar, z / scalar};
        } else {
            std::cout << "Error: Division by zero is not allowed." << std::endl;
            return *this;
        }
    }

    // Console Output
    friend std::ostream& operator<<(std::ostream& os, const Gibbs& v) {
        os << "[Gibbs]: " << v.x << " e1, " << v.y << " e2, " << v.z << " e3" << std::endl;
        return os;
    }
    // Console Input, create a Gibbs using X Y Z input.
    friend std::istream& operator>>(std::istream& is, Gibbs& v) {
        is >> v.x >> v.y >> v.z;
        return is;
    }
//FUNCTIONS
public:
    // Dot Product
    float dot(const Gibbs& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Cross Product
    Gibbs cross(const Gibbs& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    // Cartesian Magnitude, only works in cartesian space.
    float magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Normalize
    Gibbs normalize() const {
        float mag = magnitude();
        if (mag != 0.0f) {
            return {x / mag, y / mag, z / mag};
        } else {
            std::cout << "Error: Cannot normalize a zero vector." << std::endl;
            return *this;
        }
    }

    // Angle between two Versors
    float angle(const Gibbs& v) const {
        return acosf(dot(v) / (magnitude() * v.magnitude()));
    }

    // Projection of this Gibbs onto another Gibbs
    Gibbs projection(const Gibbs& v) const {
        return v * (dot(v) / v.dot(v));
    }

    // Rejection of this Gibbs from another Gibbs
    Gibbs rejection(const Gibbs& v) const {
        return *this - projection(v);
    }

    // Rotate this Gibbs by an angle around another Gibbs
    Gibbs rotate(const Gibbs& axis, float angle) const {
        return *this * cosf(angle) + axis.cross(*this) * sinf(angle) + axis * axis.dot(*this) * (1 - cosf(angle));
    }

    // Rotate this Gibbs by an angle around the X axis
    Gibbs rotateX(float angle) const {
        return rotate({1.0f, 0.0f, 0.0f}, angle);
    }

    // Rotate this Gibbs by an angle around the Y axis
    Gibbs rotateY(float angle) const {
        return rotate({0.0f, 1.0f, 0.0f}, angle);
    }

    // Rotate this Gibbs by an angle around the Z axis
    Gibbs rotateZ(float angle) const {
        return rotate({0.0f, 0.0f, 0.1f}, angle);
    }
};

