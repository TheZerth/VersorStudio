//
// Created by zerth on 09/05/24.
//
#pragma once
#ifndef VERSORSTUDIO_VERSOR_H
#define VERSORSTUDIO_VERSOR_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
// This class represents a versor, or what is most commonly known as a multivector.
// This can be seen as a replacement for vectors and can be used to perform geometric operations.
// These geometric operations can greatly simplify things that would be difficult to do with classical vectors.
// This object can be used as a scalar, vector and oriented area depending on the quantities of the coefficients.
// See the cpp for full details on how the operations are performed.
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
//--------------------OPERATORS--------------------
public:
    //--------------------Addition--------------------
    // ADDITION of multivectors is simply the individual sums of the compononents.
    Versor operator+(const Versor &v) const {
        return add(v);
    }
    Versor operator+(const float scalar) const {
        return add(scalar);
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
        return sub(v);
    }
    Versor operator-(const float scalar) const {
        return sub(scalar);
    }

    // Versor multiplication is not standard multiplication, it is what is known as a geometric product.
    // If we start by assuming one can multiply two multivectors together, we can define the geometric product through the following:
    // ab = (ab + ab) / 2 = (ab + ba + ab - ba) / 2
    // (ab+ba)/2 + (ab-ba)/2
    // (ab+ba)/2 is the dot product, and (ab-ba)/2 is the wedge product.
    // The dot product is the projection of one vector onto another multiplied by the product of their magnitudes.
    // The wedge product is the oriented area or volume constructed by the components.
    // The geometric product is the sum of the dot and wedge products.
    // The geometric product is associative, distributive and the wedge component anti commutative.
    // e1e2 = e1 ^ e2, the geometric product of two orthogonal basis vectors is the wedge product.
    // e1e1 = 1
    // e1(e1e2) = (e1e1)e2 = e2s
    //--------------------Multiplication--------------------
    // Scalar Multiplication
    Versor operator*(const float scalar) const {
        return mul(scalar);
    }
    // Vector Multiplication
    Versor operator*(const std::vector<float> &v) const {
        return mul(v);
    }
    // Versor Multiplication
    Versor operator*(const Versor &v) const {
        return mul(v);
    }

    //--------------------Division--------------------
    // Scalar Division
    Versor operator/(const float scalar) const {
        return div(scalar);
    }
    // Versor Division
    Versor operator/(const Versor &v) const {
        return div(v);
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
        return ext(v);
    }

    Versor operator^(const float scalar) const {
        return ext(scalar);
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
    // The inner product of itself is the square of the magnitude of the vector. A . A = |A|^2
    Versor operator|(const Versor &v) const {
        return inr(v);
    };
    Versor operator|(const float scalar) const {
        return inr(scalar);
    };

    //--------------------Negate--------------------
    Versor operator!() const {
        return negate();
    }

    //--------------------Reverse--------------------
    Versor operator~() const {
        return reverse();
    }

    // Contraction can be thought of the act of removing one object from another and leaving the result.
    // It has many elagent uses in physics and mathematics.
    // Given the two orthogonal basis vectores e1 and e2, contraction can be described by the following:
    // e1 << e1 = 1, e1 << e2 = 0
    // e1 << (e1 ^ e2) = e2, e1 << (e2 ^ e1) = -e2
    // (e1 ^ e2) << (e1 ^ e2) = e1 << (e2 << (e1 ^ e2)) = -1
    // a << rhs = arhs
    // lhs << a = 0 if lhs grade > 0
    //--------------------Left Contraction--------------------
    Versor operator<<(const Versor &v) const {
        return (v.lco(*this));
    }

    //--------------------Right Contraction--------------------
    Versor operator>>(const Versor &v) const {
        return (v.rco(*this));
    }

    //--------------------Reflection--------------------
    // Reflection is the act of flipping an object over a line or plane.
    // This can be done by seeing that any vector can be described as the sum of components to the reflected line and its perpendicular pair.
    // The reflection occurs through flipping the sign of the portion of the vector that is perpendicular to the line.
    // a = a|| + a_|_ , a is the vector, a|| is the projection of a onto the line of reflection, a_|_ is the projection of a onto the reflected lines normal.
    // a' = a|| - a_|_ , a' is the reflection of a.
    // Let n be the line or plane of reflection.
    // a|| = (a | n)n, a_|_ = a - a||
    // Therefor, a' = (a | n)n - (a - a_|_) =
    // (a | n)n - a - (a | n)n =
    // a - 2(a | n)n, now we can do some math magic to simplify this further. Lets add 1 to a.
    // ann - 2(a | n)n = (a | n + a ^ n)n - 2(a | n)n, due to associativity of the geometric product.
    // = (a | n)n + (a ^ n)n - (a | n)n - (a | n)n = (a ^ n)n - (a | n)n
    // = (a ^ n - a | n)n
    // = -(n ^ a + n | a)n this thing looks awfully like the geometric product of n and a now? In which case,
    // = -n * a * n
    // a' = -nan

    //--------------------IO-STREAM-FUNCTIONS--------------------
    // Console Outputd
    friend std::ostream &operator<<(std::ostream &os, const Versor &v) {
        os << std::fixed << std::setprecision(3) << std::setfill('0')
           << "[" << v.toString() << "]";
        return os;
    };
    // Console Input, create a Versor using A X Y Z input.
    friend std::istream &operator>>(std::istream &is, Versor &v) {
        is >> v.a >> v.x >> v.y >> v.b;
        return is;
    };
    // Return if two Versors are identical.
    bool operator==(const Versor & versor) const {
        return a == versor.a && x == versor.x && y == versor.y && b == versor.b;
    }
    // Return if two Versors are not identical.
    bool operator!=(const Versor & versor) const {
        return a != versor.a || x != versor.x || y != versor.y || b != versor.b;
    }
    // Assign a Versor to another Versor.
    Versor &operator=(const Versor &v) {
        a = v.a;
        x = v.x;
        y = v.y;
        b = v.b;
        return *this;
    }
//--------------------FUNCTIONS--------------------
public:
    Versor normalize() const;
    Versor sqNorm() const;
    Versor negate() const;
    Versor reverse() const;
    Versor add(const Versor &v) const;
    Versor add(const float scalar) const;
    Versor sub(const Versor &v) const;
    Versor sub(const float scalar) const;
    Versor mul(const Versor &v) const;
    Versor mul(const float scalar) const;
    Versor mul(const std::vector<float> &v) const;
    Versor div(const Versor &v) const;
    Versor div(const float scalar) const;
    Versor inr(const Versor &v) const;
    Versor inr(const float scalar) const;
    Versor ext(const Versor &v) const;
    Versor ext(const float scalar) const;
    Versor lco(const Versor &v) const;
    Versor lco(const float scalar) const;
    Versor rco(const Versor &v) const;
    Versor rco(const float scalar) const;

    Versor reflect(const Versor &v) const;

    std::string toString() const;
    std::string toLatex() const;
};

#endif //VERSORSTUDIO_VERSOR_H
