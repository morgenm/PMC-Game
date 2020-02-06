/*
box.h
Contains Box class
A simple box object implemented to test bullet physics.
*/

#ifndef BOX_H
#define BOX_H

#include "vec3.h"

class Box
{
    vec3f position;
    vec3f rotation;
public:
    Box(vec3f p, vec3f r);

    void set_position(vec3f p);
    void set_rotation(vec3f r);

    vec3f get_position() const;
    vec3f get_rotation() const;
};

#endif
