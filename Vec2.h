/***
* Christopher Di Conza, Final Project, PROG33921
*
*	Vec2 header
***/
#ifndef VEC2_H_
#define VEC2_H_

struct Vec2
{
    float x, y;

    Vec2()
        : x(0.0f), y(0.0f)
    { }

    Vec2(float x, float y)
        : x(x), y(y)
    { }
};

float Distance(const Vec2& a, const Vec2& b); //passed by reference because we want to avoid making a copy.

float DistanceSquared(const Vec2& a, const Vec2& b);

#endif
