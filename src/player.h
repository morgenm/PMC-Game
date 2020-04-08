/*
player.h
Contains the player class.
The player class holds the player's position in the world
and handles moving the player through the world.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "vec3.h"

class Player
{
    vec3f position;
    vec3f velocity; //Units traveled per frame

    const float max_velocity_magnitude = 3.5f/60.f;
    const float min_velocity_magnitude = 0.5f/60.f;
    const float acceleration_scalar = 1/60.f;
    const float decceleration_scalar = 0.2f/60;

public:
    Player(vec3f p);
    void update();
    void walk(vec3f w); //Walk in given vector direction
    void stop_walk();
    vec3f get_position() const;
};

#endif
