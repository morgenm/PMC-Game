/*
Game
This is the Game Engine. It handles all game logic,
including player and enemy movement and maps.
*/

#pragma once

#include "msg_sys/engine_msg_feed.h"
#include "msg_sys/feed_register_req.h"

class Game {
public:

    //Interface
    //GetFeedRegisterRequest():
        //Return the Register request to register with the msg_sys.
        //Abstraction Level: FeedRegisterRequest
    EngineFeedRegisterRequest GetFeedRegisterRequest();

private:
    EngineMessageFeed m_GameMsgFeed; //Game Message Feed
};
