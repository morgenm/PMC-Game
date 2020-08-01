#include "feed_register_req.h"

#include <iostream>
#include "assert.h"

void EngineFeedRegisterRequest::AddFeed( EngineMessageFeed *in_EngineFeed ) {
    assert(in_EngineFeed != nullptr, "EngineFeedRegisterRequest::AddFeed Null Pointer", return);
    m_Feeds.push_back( in_EngineFeed );
}

EngineMessageFeed* EngineFeedRegisterRequest::GetFeed() {
    //Calling back and pop_back on an empty vector causes undefined behaviors
    if ( m_Feeds.empty() ) {
        return nullptr;
    }

    EngineMessageFeed* feed = m_Feeds.back();

    //Delete from vector because Requests are only handled once
    m_Feeds.pop_back();
    return feed;
}

bool EngineFeedRegisterRequest::IsMoreFeeds() const {
    if( m_Feeds.empty() ) {
        return false;
    }
    else {
        return true;
    }
}
