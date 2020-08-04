#include "msg_sys/engine_msg_feed.h"
#include "msg_sys/msg_feed.h"
#include "error.h"

#include <iostream>

// Message System placeholder class
// The placeholder is needed to be a friend class of EngineMessageFeed
// so that we may test the class.
class MessageSystem {
public:
    void RegisterEngineFeed(EngineMessageFeed *in_EngineMsgFeed,
        MessageFeed *in_MsgFeedPtr, E_Error *out_Error);
};

void MessageSystem::RegisterEngineFeed(EngineMessageFeed *in_EngineMsgFeed,
MessageFeed *in_MsgFeedPtr, E_Error *out_Error) {
    EngineMessageFeed engMsgFeed = *in_EngineMsgFeed;

    engMsgFeed.ms_RegisterUnderlyingFeed(in_MsgFeedPtr, out_Error);
}

void TryRegisterUnderlyingFeedBad() {
    MessageSystem msgSys;
    EngineMessageFeed engMsgFeed;
    MessageFeed *msgFeedPtr = NULL;
    E_Error error;

    msgSys.RegisterEngineFeed(&engMsgFeed, msgFeedPtr, &error);

    if(error != E_ErrorError) {
        std::cout << "ms_RegisterUnderlyingFeed Null Test: FAILED!\n";
    }
    else {
        std::cout << "ms_RegisterUnderlyingFeed Null Test: Passed.\n";
    }
}

void TryRegisterUnderlyingFeedGood() {
    MessageSystem msgSys;
    EngineMessageFeed engMsgFeed;
    MessageFeed msgFeed;
    E_Error error;

    msgSys.RegisterEngineFeed(&engMsgFeed, &msgFeed, &error);

    if(error == E_ErrorNoError) {
        std::cout << "ms_RegisterUnderlyingFeed Good Test: Passed.\n";
    }
    else {
        std::cout << "ms_RegisterUnderlyingFeed Good Test: FAILED!\n";
    }
}

int main() {
    TryRegisterUnderlyingFeedBad();
    TryRegisterUnderlyingFeedGood();

    return 0;
}
