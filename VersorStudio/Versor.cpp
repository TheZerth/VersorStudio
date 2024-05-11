//
// Created by zerth on 09/05/24.
//

#include "Versor.h"

static const std::vector<float> e1 = {1.0f,0.0f,0.0f};
static const std::vector<float> e2 = {0.0f,1.0f,0.0f};

Versor Versor::negate(Versor v) const {
    Versor temp{-v.a, -v.x, -v.y, -v.b};
    return temp;
}
