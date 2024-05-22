//
// Created by zerth on 09/05/24.
//
#include "Versor.h"



static const std::vector<float> e1 = {1.0f,0.0f};
static const std::vector<float> e2 = {0.0f,1.0f};
Versor Versor::negate() const { return {a * -1.0f, x * -1.0f, y * -1.0f, b * -1.0f}; }
Versor Versor::reverse() const { return {a, x, y, b * -1.0f}; }
//Versor Versor::normalize() const;
Versor Versor::add(const Versor &v) const { return {a + v.a, x + v.x, y + v.y, b + v.b}; }
Versor Versor::add(const float scalar) const { return {a + scalar, x, y, b}; }
Versor Versor::sub(const Versor &v) const { return {a - v.a, x - v.x, y - v.y, b - v.b}; }
Versor Versor::sub(const float scalar) const { return {a - scalar, x, y, b}; }
Versor Versor::mul(const Versor &v) const {
    float tempa = (a * v.a) + (x * v.x) + (y * v.y) + (-b * v.b);
    float tempx = (x * v.a) + (b * v.y) + (a * v.x) + (-y * v.b);
    float tempy = (a * v.y) + (x * v.b) + (y * v.a) + (-b * v.x);
    float tempb = (b * v.a) + (a * v.b) + (x * v.y) + (-y * v.x);
    return { tempa, tempx, tempy, tempb };
}
Versor Versor::mul(const std::vector<float> &v) const {         //0 = x, 1 = y
    float tempa = (x * v[0]) + (y * v[1]);
    float tempx = (b * v[1]) + (a * v[0]);
    float tempy = (a * v[1]) + (-b * v[0]);
    float tempb = (x * v[1]) + (-y * v[0]);
    return { tempa, tempx, tempy, tempb };
}
Versor Versor::mul(const float scalar) const { return {a * scalar, x * scalar, y * scalar, b * scalar}; }
Versor Versor::div(const Versor &v) const {
    if (v.a != 0.0f) { return {a / v.a,x / v.a,y / v.a,b / v.a};    //If the input versor is a scalar
    } else if (v.b == 0.0f) { return {0.0f,x / v.x,y / v.y,0.0f};   //If the input versor is a vector
    } else { return {0.0f,0.0f,0.0f,b / v.b}; } }                   //If the input versor is a bivector
Versor Versor::div(const float scalar) const { return {a / scalar, x / scalar, y / scalar, b / scalar}; }
Versor Versor::inr(const Versor &v) const { return {a * v.a + x * v.x + y * v.y - b * v.b, 0.0f, 0.0f, 0.0f}; }
Versor Versor::inr(const float scalar) const { return { a * scalar, 0.0f, 0.0f, 0.0f}; }
Versor Versor::ext(const Versor &v) const {
    float tempa = (a * v.a);
    float tempx = (x * v.a) + (a * v.x);
    float tempy = (a * v.y) + (y * v.a);
    float tempb = (b * v.a) + (a * v.b) + (x * v.y) + (-y * v.x);
    return { tempa, tempx, tempy, tempb };
}
Versor Versor::ext(const float scalar) const { return {a * scalar, x * scalar, y * scalar, b * scalar}; }
Versor Versor::lco(const Versor &v) const {
    float tempa = (a * v.a) + (x * v.x) + (y * v.y) + (-b * v.b);
    float tempx = (a * v.x) + (-y * v.b);
    float tempy = (a * v.y) + (x * v.b);
    float tempb = (a * v.b);
    return { tempa, tempx, tempy, tempb };
}
Versor Versor::lco(const float scalar) const {
    return { a * scalar, 0.0f, 0.0f, 0.0f };
}
Versor Versor::rco(const Versor &v) const {
    float tempa = (a * v.a) + (x * v.x) + (y * v.y) + (-b * v.b);
    float tempx = (x * v.a) + (b * v.y);
    float tempy = (y * v.a) + (-b * v.x);
    float tempb = (b * v.a);
    return { tempa, tempx, tempy, tempb };
}
Versor Versor::rco(const float scalar) const {
    return { a * scalar, 0.0f, 0.0f, 0.0f };
}
Versor Versor::sqNorm() const { return (*this | (~*this)); }

Versor Versor::reflect(const Versor &v) const {
    return (*this * v) * (*this);
}


std::string Versor::toString() const {
    std::ostringstream os;
    if (a != 0.0f) {
        os << a;
    }
    if (x != 0.0f) {
        if (!os.str().empty()) {
            os << " + ";
        }
        os << x << "e1";
    }
    if (y != 0.0f) {
        if (!os.str().empty()) {
            os << " + ";
        }
        os << y << "e2";
    }
    if (b != 0.0f) {
        if (!os.str().empty()) {
            os << " + ";
        }
        os << b << "e1^e2";
    }
    if (os.str().empty()) {
        os << "0";
    }
    return os.str();
}


