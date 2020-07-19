/*
Engine Message Feed
This is the Message Feed representation that Engines use.
It is linked to an underlying feed used by the Message System.
*/

#pragma once

#include "msg_feed.h"

class EngineMessageFeed {
public:
    //Interface
    //ms_RegisterUnderlyingFeed(MessageFeed *)
        //Abstraction Level is below the EngineMessageFeed.
        //Abstraction is broken here because Message System
        //needs to know the implementation of EngineMessageFeed
        //because it uses MessageFeed pointers. This is only
        //called by MessageSystem (as denoted by "ms_").
    void ms_RegisterUnderlyingFeed(MessageFeed* in_MessageFeed);
private:
    MessageFeed *m_UnderlyingFeed;
};
