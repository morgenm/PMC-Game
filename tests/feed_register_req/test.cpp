#include "msg_sys/feed_register_req.h"
#include "msg_sys/engine_msg_feed.h"

#include <iostream>

void TryAddFeedNull() {
    EngineFeedRegisterRequest request;
    request.AddFeed(NULL);
    if(request.IsMoreFeeds()) {
        std::cout << "GetFeed NULL Test: FAILED!\n";
    }
    else {
        std::cout << "GetFeed NULL Test: Passed.\n";
    }
}

void TryAddFeedGood() {
    EngineFeedRegisterRequest request;
    EngineMessageFeed feed;
    request.AddFeed(&feed);
    if(!request.IsMoreFeeds()) {
        std::cout << "GetFeed Good Data Test: FAILED!\n";
    }
    EngineMessageFeed *feedPtr = request.GetFeed();
    if((feedPtr == &feed) && feedPtr != NULL) {
        std::cout << "GetFeed Good Data Test: Passed.\n";
    }
    else {
        std::cout << "GetFeed Good Data Test: FAILED!\n";
    }
}

void TryAddFeedManyGoodData() {
    EngineMessageFeed feeds[1000];
    EngineFeedRegisterRequest request;
    for(int i=0; i<1000; i++) {
        EngineMessageFeed *feedPtr = &feeds[i];
        request.AddFeed(feedPtr);
    }
    bool passed = true;
    for(int i=999; i>=0; i--) {
        EngineMessageFeed *feedPtr = request.GetFeed();
        if(feedPtr != &feeds[i]) {
            std::cout << "GetFeed Many Good Data Test: FAILED!\n";
            std::cout << "Test failed on i value: " << i << '\n';
            passed = false;
            break;
        }
    }
    if(passed) {
        std::cout << "GetFeed Many Good Data Test: Passed.\n";
    }
}

void TryAddFeed() {
    //Try bad data
    TryAddFeedNull();

    //Good Data
    TryAddFeedGood();

    //Lots of good data
    TryAddFeedManyGoodData();
}

int main() {
    TryAddFeed();

    return 0;
}
