//
// Created by zerth on 07/05/24.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>

class Versor {
// Variables
public:
    static const std::vector<float> e1,e2,e3;

    Versor(float x, float y, float z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    void x(float a)
    {
        _x = a;
    }
    float x()
    {
        return _x;
    }
    void y(float a)
    {
        _y = a;
    }
    float y()
    {
        return _y;
    }
    void z(float a)
    {
        _z = a;
    }
    float z()
    {
        return _z;
    }
private:
    float _x, _y, _z;
};

