#include "msg_sys.h"

#include "error.h"

void MessageSystem::RegisterEngineFeedRequest(EngineFeedRegisterRequest in_FeedRegReq) {
    while(in_FeedRegReq.IsMoreFeeds()) {
        EngineMessageFeed *engFeed = in_FeedRegReq.GetFeed();

        //Create the new Message Feed
        MessageFeedID newFeedID = CreateFeed();

        //Register the feed
        E_Error error;
        MessageFeed *msgFeed = &m_MsgFeeds.at(newFeedID);
        engFeed->ms_RegisterUnderlyingFeed(msgFeed, &error);
    }
}

MessageFeedID MessageSystem::CreateFeed() {
    MessageFeedID msgFeedID;
    while(m_MsgFeeds.count(msgFeedID) > 0)
    {
        msgFeedID.NewID(); //Generate a new ID
    }

    MessageFeed newFeed;//Create the Message Feed
    m_MsgFeeds.emplace(msgFeedID, newFeed); //Add the Message Feed to the feed container

    return msgFeedID;
}
