/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Vec2 class with useful methods for determining the distance between two points;
*
*	NOTE: not implemented. I used my own logic which is similar
***/
#include <cmath>

#include "Vec2.h"

float Distance(const Vec2& a, const Vec2& b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx*dx + dy*dy);
}

float DistanceSquared(const Vec2& a, const Vec2& b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx*dx + dy*dy;
}
