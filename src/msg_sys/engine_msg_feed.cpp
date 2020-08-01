#include "engine_msg_feed.h"

#include "assert.h"

void EngineMessageFeed::ms_RegisterUnderlyingFeed( MessageFeed *in_MessageFeed, E_Error *out_Error ) {
    if( in_MessageFeed == nullptr ) {
        assert( in_MessageFeed != nullptr, "EngineMessageFeed::ms_RegisterUnderlyingFeed Assert Failed: Null pointer.\n", *out_Error=E_Error::E_ErrorError);
        return;
    }
    m_UnderlyingFeed = in_MessageFeed;
    *out_Error = E_Error::E_ErrorNoError;
}
