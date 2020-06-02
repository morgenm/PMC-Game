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

#include <iostream> //To be replaced by error handling

struct vec3f
{
    //Actual values of the vector
    float x;
    float y;
    float z;

    vec3f(float inX, float inY, float inZ)
    :x(inX), y(inY), z(inZ)
    {
    }

    vec3f(const vec3f& v)
    :x(v.x), y(v.y), z(v.z)
    {
    }

    float get_magnitude() const
    {
        float tot = (float)pow(x,2) + (float)pow(y,2) + (float)pow(z,2);
        return (float)sqrt(tot);
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
    bool operator==(const vec3f &v) const
    {
        return x==v.x && y==v.y && z==v.z;
    }
    bool operator!=(const vec3f &v) const
    {
        return x!=v.x || y==v.y || z==v.z;
    }

    //Scalar operations
    vec3f operator*(const float mult) const
    {
        vec3f new_vec(*this);
        new_vec.x *= mult; new_vec.y *= mult; new_vec.z *= mult;
        return new_vec;
    }
    vec3f operator+(const float a) const
    {
        vec3f new_vec(*this);
        new_vec.x += a; new_vec.y += a; new_vec.z += a;
        return new_vec;
    }
    vec3f operator-(const float sub) const
    {
        vec3f new_vec(*this);
        new_vec.x -= sub; new_vec.y -= sub; new_vec.z -= sub;
        return new_vec;
    }

    //Vector algebraic operations
    vec3f operator+(const vec3f& v)
    {
        vec3f new_vec(*this);
        new_vec.x += v.x; new_vec.y += v.y; new_vec.z += v.z;
        return new_vec;
    }
    vec3f operator-(const vec3f& v)
    {
        vec3f new_vec(*this);
        new_vec.x -= v.x; new_vec.y -= v.y; new_vec.z -= v.z;
        return new_vec;
    }

    float operator[](const size_t i) const
    {
        switch(i)
        {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                std::cout << "ERROR: VEC3F ACCESSOR OUT OF BOUNDS!\n";
                return -1;
        }
    }
};

struct vec3ui
{
    unsigned int x,y,z;
};

#endif
