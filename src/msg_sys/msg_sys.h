/*
Message System
This is the Message System. It handles all messages sent by all engines.
It contains and handles message feeds.
*/

#pragma once

#include "msg_feed.h"
#include "engine_msg_feed.h"
#include "feed_register_req.h"
#include "msg_feed_id.h"

#include <map>

class MessageSystem {
public:
    //Interface
    //MessageSystem():
        //Initialize MessageSystem. No data passed.
        //Abstraction Level: Message System
    //RegisterEngineFeedRequest(FeedRegisterRequest):
        //Register all message feeds described in the request.
        //Abstraction Level: FeedRegisterRequest
    //MessageSystem();
    void RegisterEngineFeedRequest(EngineFeedRegisterRequest in_FeedRegReq);
private:
    void CreateFeed(const MessageFeedID *out_MsgFeedID);

    std::map<MessageFeedID, MessageFeed> m_MsgFeeds;
};
