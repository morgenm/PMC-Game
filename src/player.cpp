#include "player.h"

Player::Player(vec3f p)
: position(p), velocity(0,0,0)
{
}

void Player::update()
{
    //Displace by the velocity.
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;
}

void Player::walk(vec3f w)
{
    //If the velocity hasn't reached max, just add the walk vector
    //to the current velocity. Works well.
    if(velocity.get_magnitude() < max_velocity_magnitude)
    {
        velocity.x += (w.x/acceleration_scalar);
        velocity.y += (w.y/acceleration_scalar);
        velocity.z += (w.z/acceleration_scalar);
    }
    //If the direction of the velocity (normalized) doesn't equal the
    //walk vec (which is already normalized) and the player is actually
    //walking (magnitude) then set the direction to the walk vec.
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

    //Decelerate by direction and decceleration_scalar
    if(velocity.x > 0)
        velocity.x -= nx*decceleration_scalar;
    else if(velocity.x < 0)
        velocity.x += nx*decceleration_scalar;

    if(velocity.z > 0)
        velocity.z -= nz*decceleration_scalar;
    else if(velocity.z < 0)
        velocity.z += nz*decceleration_scalar;

    //If the velocity magnitude is smaller than minimum velocity, vel is zero
    if(velocity.get_magnitude() < min_velocity_magnitude && velocity.get_magnitude()>0)
    {
        velocity.x = 0;
        velocity.z = 0;
    }
}

vec3f Player::get_position() const
{
    return position;
}
