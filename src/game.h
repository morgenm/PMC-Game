/*
    Game
    The Game Engine
*/

#pragma once

#include "engine/engine.h"

class Game: public Engine {
public:
    EngineFeedRegisterRequest GetFeedRegisterRequest() override;
private:
    EngineMessageFeed m_GameMsgFeed;
};
