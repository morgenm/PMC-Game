#include "pmc.h"

PMC::PMC() {
    //Construct subengines
    //Construct/Initialize Messaging System

    //Create subengine message feeds
    EngineFeedRegisterRequest gameFeedRegReq = m_Game.GetFeedRegisterRequest();

    //Register subengine feeds with msg sys
    m_MsgSys.RegisterEngineFeedRequest(gameFeedRegReq);

    m_IsPMCRunning = true; //PMC is now running
}

void PMC::Run() {
    while(m_IsPMCRunning == true) {
        //Update all subengines
        //Send all Message System messages
    }
}
