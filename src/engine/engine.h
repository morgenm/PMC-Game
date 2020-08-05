/*
    Engine
    The Base class abstraction for engines to inherit from.
*/

#pragma once

#include "msg_sys/feed_register_req.h"

class Engine {
public:
    virtual EngineFeedRegisterRequest GetFeedRegisterRequest() = 0;
};
