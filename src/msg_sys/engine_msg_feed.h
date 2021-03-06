/*
Engine Message Feed
This is the Message Feed representation that Engines use.
It is linked to an underlying feed used by the Message System.
*/

#pragma once

#include "msg_feed.h"
#include "error.h"

class EngineMessageFeed {
public:
    //Interface
    //ms_RegisterUnderlyingFeed(MessageFeed *)
        //Abstraction Level is below the EngineMessageFeed.
        //Abstraction is broken here because Message System
        //needs to know the implementation of EngineMessageFeed
        //because it uses MessageFeed pointers.
        //This is only called by MessageSystem (as denoted by "ms_"),
        //hence MessageSystem is a friend class.

private:
    void ms_RegisterUnderlyingFeed( MessageFeed* in_MessageFeed, E_Error *out_Error );
    friend class MessageSystem;

    MessageFeed *m_UnderlyingFeed;
};
