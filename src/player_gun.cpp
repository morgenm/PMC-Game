#include "player_gun.h"

void PlayerGun::update(float dt)
{
    time_since_aim += dt;
    return;
}

void PlayerGun::try_aim_change()
{
    if(!aimed && time_since_aim >= aim_time_wait)
    {
        aimed = true;
        time_since_aim = 0;
    }
    else if(aimed && time_since_aim >= aim_time_wait)
    {
        aimed = false;
        time_since_aim = 0;
    }
    return;
}


bool PlayerGun::get_aimed() const
{
    return aimed;
}
