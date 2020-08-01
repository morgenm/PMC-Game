#include "feed_register_req.h"

#include <iostream>
#include "assert.h"

void EngineFeedRegisterRequest::AddFeed( EngineMessageFeed *in_EngineFeed ) {
    if( in_EngineFeed == nullptr ) {
        //Replace with better error handling
        assert( false, "EngineFeedRegisterRequest::AddFeed Assert Failed: Null Pointer", return );
        return;
    }
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
