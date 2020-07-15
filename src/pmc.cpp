#include "pmc.h"

PMC::PMC() {
    //Construct subengines
    //Construct/Initialize Messaging System
    //Create subengine message feeds
    //Pass message feeds to subengines
    m_IsGameRunning = true; //Game is now running
}

void PMC::run() {
    while(m_IsGameRunning == true) {
        //Update all subengines
        //Send all Message System messages
    }
}
