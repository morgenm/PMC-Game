#ifndef PLAYER_GUN_H
#define PLAYER_GUN_H

class PlayerGun
{
    const float aim_time_wait = 0.2;
    float time_since_aim = 0.f; //Time since last aim change
    bool aimed = false;
public:
    void update(float dt);
    void try_aim_change();
    bool get_aimed() const;
};

#endif
