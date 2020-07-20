#include "msg_sys/engine_msg_feed.h"
#include "msg_sys/msg_feed.h"
#include "error.h"

#include <iostream>

void TryRegisterUnderlyingFeed() {
    EngineMessageFeed engMsgFeed;
    MessageFeed *msgFeedPtr = NULL;
    E_Error error;

    engMsgFeed.ms_RegisterUnderlyingFeed(msgFeedPtr, &error);
    if(error != E_ErrorError) {
        std::cout << "ms_RegisterUnderlyingFeed Null Test: FAILED!\n";
    }
    else {
        std::cout << "ms_RegisterUnderlyingFeed Null Test: Passed.\n";
    }
}

int main() {
    TryRegisterUnderlyingFeed();

    return 0;
}
