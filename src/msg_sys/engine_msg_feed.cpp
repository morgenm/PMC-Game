#include "engine_msg_feed.h"

void EngineMessageFeed::ms_RegisterUnderlyingFeed(MessageFeed *in_MessageFeed) {
    m_UnderlyingFeed = in_MessageFeed;
}
