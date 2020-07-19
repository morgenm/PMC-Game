/*
Engine Feed Register Request
This is a request from an engine to register one or more feeds with
the Message System.
*/
#pragma once

#include "engine_msg_feed.h"
#include <string>
#include <vector>

class EngineFeedRegisterRequest {
public:
    //Interface
    //AddFeed(feed):
        //Adds a feed to the request
        //The abstraction is at the request level. It only knows of
        //the feed itself.
    //GetFeed()
        //Returns the next feed in the request list, if it exists
        //Abstraction level is at the request level.
    //IsMoreRequests()
        //Returns true if there are any more requests
        //Abstraction level is at request.

    void AddFeed(EngineMessageFeed *in_EngineFeed);
    EngineMessageFeed *GetFeed();
    bool IsMoreFeeds() const;

private:
    std::vector<EngineMessageFeed*> m_Feeds;
};
