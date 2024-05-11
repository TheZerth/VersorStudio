//
// Created by zerth on 09/05/24.
//
#pragma once
#ifndef VERSORSTUDIO_VERSOR_H
#define VERSORSTUDIO_VERSOR_H
#include <vector>
#include <iostream>
#include <iomanip>
// This class represents a versor, or what is most commonly known as a multivector.
// This can be seen as a replacement for vectors and can be used to perform geometric operations.
// These geometric operations can greatly simplify things that would be difficult to do with classical vectors.
// This object can be used as a scalar, vector and oriented area depending on the quantities of the coefficients.
//
// If the object is a scalar it can be used to represent things such as mass and charge.
// If the object is a vector it can be used to represent things such as velocity and force.
// If the object is a bivector it can be used to represent things such as angular momentum and torque.

class Versor {
//--------------------Variables--------------------
public:
    std::vector<float> e1, e2;    //These are the basis vectors.
    float a; //This represents the coefficient to the unit scalar, 1.
    float x; //This represents the coefficient to the basis vector, e1.
    float y; //This represents the coefficient to the basis vector, e2.
    float b; //This represents the oriented area or volume of the bivector. Will be zero for vectors and scalars.
public:
    Versor(float a, float x, float y, float b) : a(a), x(x), y(y), b(b) {}

    ~Versor() = default;

    Versor negate(Versor v) const;
//--------------------OPERATORS--------------------
public:
    //--------------------Addition--------------------
    // ADDITION of multivectors is simply the individual sums of the compononents.
    Versor operator+(const Versor &v) const {
        return {a + v.a, x + v.x, y + v.y, b + v.b};
    }
    //--------------------Subtraction--------------------
    // SUBTRACTION is defined as the sum of the inverse of the input versor.
    // A - B = A + (-B), here is the litteral implementation of this.
    // I will not use this due to the fact that it is not as efficient as it could be.
    /*Versor operator-(const Versor& v) const {
        Versor temp{-v.a, -v.x, -v.y, -v.b};
        return *this + temp;
    }*/
    Versor operator-(const Versor &v) const {
        return {a - v.a, x - v.x, y - v.y, b - v.b};
    }

    //--------------------Multiplication--------------------
    // Scalar Multiplication
    Versor operator*(const float scalar) const {
        return {a * scalar, x * scalar, y * scalar, b * scalar};
    }

    // Versor Multiplication
    Versor operator*(const Versor &v) const {
        if (v.a != 0.0f) {              //If the input versor is a scalar
            return {v.a * a,
                    v.a * x,
                    v.a * y,
                    v.a * b};
        } else if (v.b == 0.0f) {         //If the input versor is a vector
            return {0,
                    x * v.x,
                    y * v.y,
                    0};
        } else {                          //If the input versor is a bivector
            //return UNDEFINED;
        }
    }

    //--------------------Division--------------------
    // Scalar Division
    Versor operator/(const float scalar) const {
        if (scalar != 0.0f) {           //
            return {a / scalar, x / scalar, y / scalar, b / scalar};
        } else {
            std::cout << "Error: Division by zero is not allowed." << std::endl;
            return *this;
        }
    }

    // Versor Division
    // This is currently a bit of a hack to make the geometric object work
    // Further work will be done on this to make it function properly.
    // Currently, it does not represent a true geometric division.
    Versor operator/(const Versor &v) const {
        float temp = 0;                 //If the input versor is a scalar
        if (v.a != 0.0f) {
            return {a / v.a,
                    x / v.a,
                    y / v.a,
                    b / v.a};
        }                               //If the input versor is a vector
        else if (v.b == 0.0f) {
            return {0,
                    x / v.x,
                    y / v.y,
                    0};
        } else {                          //Input is a bivector
            return {b / v.b, 0, 0, 0};
        }
    }

    //--------------------Exterior Product--------------------
    // Wedge Product, used to create bivectors and trivectors out of vectors. Also known as the exterior product.
    // This quantity represents the oriented area or volume constructed by the components.
    // A is a versor containing a scalar and vector components; a+xe1+ye2
    // A ^ B = (a_x * e1)(a_y * e2) ^ (b_x * e1)(b_y * e2), expanding with FOIL
    // (a_x * e1) ^ (b_x * e1) + (a_x * e1) ^ (b_y * e2) + (a_y * e2) ^ (b_x * e1) + (a_y * e2) ^ (b_y * e2) =
    // since e1_a = e1_b and a ^ a = 0, we can simplify this to:
    // 0 + (a_x * e1) ^ (b_y * e2) + (a_y * e2) ^ (b_x * e1) + 0 =
    // Using a ^ b = -b ^ a, we can simplify this to:
    // (a_x * e1) ^ (b_y * e2) - (a_y * e1) ^ (b_x * e2) =
    // Through factoring a_x, a_y, b_x and b_y, we can simplify this to:
    // (a_x * b_y - a_y * b_x) * e1 ^ e2
    // e1 ^ e2 is the unit bivector that represents the oriented volume of our basis vectors.
    // The rest is a scalar quantity.
    // If the wedge product is zero, then the two vectors are parallel.
    Versor operator^(const Versor &v) const {
        return {0, 0, 0, x * v.y - y * v.x};
    };

    //--------------------Interior Product--------------------
    // Dot Product, used to create scalars out of vectors. Also known as the inner product or scalar product.
    // Represents the projection of one vector onto another multiplied by the product of their magnitudes.
    // A . B = (a_x * e1 + a_y * e2) . (b_x * e1 + b_y * e2), expanding with FOIL
    // (a_x * e1) . (b_x * e1) + (a_x * e1) . (b_y * e2) + (a_y * e2) . (b_x * e1) + (a_y * e2) . (b_y * e2) =
    // Since e1 and e2 are orthogonal, e1 . e2 = 0 we can simplify this to:
    // (a_x * e1) . (b_x * e1) + 0 + 0 + (a_y * e2) . (b_y * e2) =
    // Through factoring a_x, a_y, b_x and b_y, we can simplify this to:
    // (a_x * b_x)(e1 . e1) + (a_y * b_y)(e2 . e2) =
    // Since e1 . e1 = 1 and e2 . e2 = 1, we can simplify this to:
    // (a_x * b_x) + (a_y * b_y), just a scalar quantity.
    Versor operator|(const Versor &v) const {
        return {x * v.x + y * v.y, 0.0f, 0.0f, 0.0f};
    };


    //--------------------IO-STREAM-FUNCTIONS--------------------
    // Console Outputd
    friend std::ostream &operator<<(std::ostream &os, const Versor &v) {
        os << "[Versor]: " << std::fixed << std::setprecision(3) << std::setfill('0')
           << v.a << " + " << v.x << " e1 + " << v.y << " e2 + " << v.b << "(e1^e2)" << std::endl;
        return os;
    };

    // Console Input, create a Versor using A X Y Z input.
    friend std::istream &operator>>(std::istream &is, Versor &v) {
        is >> v.a >> v.x >> v.y >> v.b;
        return is;
    };
//--------------------FUNCTIONS--------------------
};

#endif //VERSORSTUDIO_VERSOR_H
