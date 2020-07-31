#include "msg_sys/msg_sys.h"
#include "msg_sys/feed_register_req.h"
#include "msg_sys/engine_msg_feed.h"
#include "error.h"

#include <iostream>
#include <vector>

void TryRegisterReqGood() {
    EngineMessageFeed feed;
    EngineFeedRegisterRequest req;
    req.AddFeed( &feed );

    MessageSystem msgSys;
    E_Error error;
    msgSys.RegisterEngineFeedRequest( req, &error );

    if( error == E_Error::E_ErrorNoError ) {
        std::cout << "TryRegisterReq Good Data Test: Passed.\n";
    }
    else {
        std::cout << "TryRegisterReq Good Data Test: FAILED!\n";
    }
}

void TryRegisterReqManyGood() {
    std::vector<EngineMessageFeed> feeds;
    EngineFeedRegisterRequest req;
    for( int i=0; i<1000; i++ ) {
        EngineMessageFeed feed;
        feeds.push_back( feed );
        req.AddFeed( &feeds.back() );
    }

    MessageSystem msgSys;
    E_Error error;
    msgSys.RegisterEngineFeedRequest( req, &error );
    if( error == E_Error::E_ErrorNoError ) {
        std::cout << "TryRegisterReq Many Good Data Test: Passed.\n";
    }
    else {
        std::cout << "TryRegisterReq Many Good Data Test: FAILED!\n";
    }
}

int main() {
    TryRegisterReqGood();
    TryRegisterReqManyGood();
    return 0;
}
