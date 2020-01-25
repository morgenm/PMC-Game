/*
vec3.h
This contains the vec3f struct.
This is pretty much the same as the irr::core::vec3df but this is
here to reduce reliance on the irrlicht library for the sake of good
programming practices and in case we want to switch to a different
graphics engine.
*/

#ifndef VEC_3_H
#define VEC_3_H

#include <math.h>

struct vec3f
{
    float x;
    float y;
    float z;
    vec3f(float inX, float inY, float inZ)
    :x(inX), y(inY), z(inZ)
    {
    }

    float get_magnitude() const
    {
        float tot = pow(x,2) + pow(y,2) + pow(z,2);
        return sqrt(tot);
    }
    vec3f get_normalized() const
    {
        float nx = x;
        float ny = y;
        float nz = z;
        float mag = get_magnitude();
        if(mag == 0)
            return(vec3f(0,0,0));
        nx /= mag;
        ny /= mag;
        nz /= mag;
        return vec3f(nx, ny, nz);
    }
    bool operator==(vec3f v) const
    {
        return x==v.x && y==v.y && z==v.z;
    }
    bool operator!=(vec3f v) const
    {
        return x!=v.x || y==v.y || z==v.z;
    }
};

#endif
