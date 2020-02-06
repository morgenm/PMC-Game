#include "box.h"

Box::Box(vec3f p, vec3f r)
:position(p), rotation(r)
{

}

void Box::set_position(vec3f p)
{
    position = p;
}

void Box::set_rotation(vec3f r)
{
    rotation = r;
}

vec3f Box::get_position() const
{
    return position;
}

vec3f Box::get_rotation() const
{
    return rotation;
}
