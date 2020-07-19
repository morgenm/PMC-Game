/*
PMC
PMC is the game engine itself. It controls all other subengines and
controls the main game loop. It controls the Messaging System.
*/

#pragma once

#include "game.h"
#include "msg_sys/msg_sys.h"

class PMC {
public:
    PMC(); //Constructs all other engines and the messaging system
    void Run(); //Runs the engine.
private:
    Game m_Game;
    MessageSystem m_MsgSys;
    bool m_IsPMCRunning;
};
