#include "feed_register_req.h"

void EngineFeedRegisterRequest::AddFeed(EngineMessageFeed *engineFeed) {
    m_Feeds.push_back(engineFeed);
}

EngineMessageFeed* EngineFeedRegisterRequest::GetFeed() {
    EngineMessageFeed* feed = m_Feeds.back();

    //Delete from vector because Requests are only handled once
    m_Feeds.pop_back();
    return feed;
}

bool EngineFeedRegisterRequest::IsMoreFeeds() const {
    if(m_Feeds.empty()) {
        return false;
    }
    else {
        return true;
    }
}
