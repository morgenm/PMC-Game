/*
    Engine Handler
    Handles the creation of Engines.
*/

#pragma once

#include "singleton.h"
#include "game.h"
#include "msg_sys/msg_sys.h"

class EngineHandler {
public:
    // Interface:
    // CreateGameEngine():
        // Creates the Game Engine and returns a reference to it.
        // Abstracts away the fact it is a Singleton
    // CreateMsgSys()
        // Creates the MsgSys and returns a reference to it.
        // Abstracts away the fact it is a Singleton

    Game& CreateGameEngine();
    MessageSystem& CreateMsgSys();

private:
    Singleton<Game> m_GameEngine;
    Singleton<MessageSystem> m_MsgSys;
};
