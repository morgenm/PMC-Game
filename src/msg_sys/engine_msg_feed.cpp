#include "engine_msg_feed.h"

#include "assert.h"

void EngineMessageFeed::ms_RegisterUnderlyingFeed(MessageFeed *in_MessageFeed, E_Error *in_Error) {
    if(in_MessageFeed == NULL) {
        //Replace with Error Handling
        assert(false, "EngineMessageFeed::ms_RegisterUnderlyingFeed Assert Failed: Null pointer.\n", *in_Error=E_ErrorError);
        return;
    }
    m_UnderlyingFeed = in_MessageFeed;
}
