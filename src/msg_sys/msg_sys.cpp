#include "msg_sys.h"

void MessageSystem::RegisterEngineFeedRequest(EngineFeedRegisterRequest in_FeedRegReq) {
    while(in_FeedRegReq.IsMoreFeeds()) {
        EngineMessageFeed *engFeed = in_FeedRegReq.GetFeed();

        //Create the new Message Feed
        const MessageFeedID *newFeedID;
        CreateFeed(newFeedID);

        //Register the feed
        MessageFeed *msgFeed = &m_MsgFeeds.at(*newFeedID);
        engFeed->ms_RegisterUnderlyingFeed(msgFeed);
    }
}

void MessageSystem::CreateFeed(const MessageFeedID *out_MsgFeedID) {
    MessageFeedID msgFeedID;
    while(m_MsgFeeds.count(msgFeedID) > 0)
    {
        msgFeedID.NewID(); //Generate a new ID
    }

    MessageFeed newFeed;//Create the Message Feed
    auto emplaceResult = m_MsgFeeds.emplace(msgFeedID, newFeed); //Add the Message Feed to the feed container
    //Replace this with Resource Engine's pointers
    const MessageFeedID *msgFeedIDPtr = &((emplaceResult.first)->first);
    out_MsgFeedID = msgFeedIDPtr;
}
