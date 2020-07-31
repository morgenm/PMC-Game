#include "msg_sys.h"

#include "assert.h"

void MessageSystem::RegisterEngineFeedRequest(EngineFeedRegisterRequest in_FeedRegReq,
E_Error *out_Error) {
    while(in_FeedRegReq.IsMoreFeeds()) {
        EngineMessageFeed *engFeed = in_FeedRegReq.GetFeed();

        //Create the new Message Feed
        MessageFeedID newFeedID = CreateFeed();

        //Register the feed
        E_Error error;
        MessageFeed *msgFeed = &m_MsgFeeds.at(newFeedID);
        engFeed->ms_RegisterUnderlyingFeed(msgFeed, &error);

        if(error == E_Error::E_ErrorError) {
            *out_Error = error;
            return;
        }
    }
    *out_Error = E_Error::E_ErrorNoError;
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
