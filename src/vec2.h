#pragma once
#include "fixed_math.h"
// todo
namespace MOU
{

using namespace CKSDK::Fixed;
class Vec2
{
public:
    Vec2(int32_t x, int32_t y)
        : x(x), y(y)
    {}
    
public:
    Fixed<int32_t, 12> x;
    Fixed<int32_t, 12> y;
};
}

