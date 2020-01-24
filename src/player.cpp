#include "player.h"

#include <iostream>

Player::Player(vec3f p)
: position(p), velocity(0,0,0)
{
}

void Player::update()
{
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;
}

void Player::walk(vec3f w)
{
    if(velocity.get_magnitude() < max_velocity_magnitude)
    {
        velocity.x += (w.x/acceleration_scalar);
        velocity.y += (w.y/acceleration_scalar);
        velocity.z += (w.z/acceleration_scalar);
    }
    if(velocity.get_normalized() != w && velocity.get_magnitude() != 0)
    {
        float magnitude = velocity.get_magnitude();
        velocity.x = magnitude*w.x;
        velocity.y = magnitude*w.y;
        velocity.z = magnitude*w.z;
    }
}

void Player::stop_walk()
{
    vec3f normalized = velocity.get_normalized();
    float nx = abs(normalized.x);
    float nz = abs(normalized.z);
    
    if(velocity.x > 0)
        velocity.x -= nx*decceleration_scalar;
    else if(velocity.x < 0)
        velocity.x += nx*decceleration_scalar;

    if(velocity.z > 0)
        velocity.z -= nz*decceleration_scalar;
    else if(velocity.z < 0)
        velocity.z += nz*decceleration_scalar;

    if(velocity.get_magnitude() < min_velocity_magnitude && velocity.get_magnitude()>0)
    {
        velocity.x = 0;
        velocity.z = 0;
    }
    else if(velocity.get_magnitude() > -min_velocity_magnitude && velocity.get_magnitude()<0)
    {
        velocity.x = 0;
        velocity.z = 0;
    }

}

vec3f Player::get_position() const
{
    return position;
}
