#include "pmc.h"

#include "error.h"
#include "assert.h"

PMC::PMC() {
    //Construct subengines
    //Construct/Initialize Messaging System

    //Create subengine message feeds
    EngineFeedRegisterRequest gameFeedRegReq = m_Game.GetFeedRegisterRequest();

    //Register subengine feeds with msg sys
    E_Error error;
    m_MsgSys.RegisterEngineFeedRequest( gameFeedRegReq, &error );
    assert( error != E_Error::E_ErrorError, "PMC::PMC() RegisterEngineFeedRequest Error!\n", {} );

    m_IsPMCRunning = true; //PMC is now running
}

void PMC::Run() {
    while( m_IsPMCRunning == true ) {
        //Update all subengines
        //Send all Message System messages
    }
}
