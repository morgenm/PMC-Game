#ifndef PLAYER_H
#define PLAYER_H

#include "vec3.h"

class Player
{
    vec3f position;
    vec3f velocity;

    const float max_velocity_magnitude = 4;
    const float min_velocity_magnitude = 0.5;
    const float acceleration_scalar = 10;
    const float decceleration_scalar = 0.2;

public:
    Player(vec3f p);
    void update();
    void walk(vec3f w);
    void stop_walk();
    vec3f get_position() const;
};

#endif
