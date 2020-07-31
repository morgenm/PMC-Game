#include "msg_feed_id.h"

void MessageFeedID::NewID() {
    m_ID++;
}

bool MessageFeedID::operator==(const MessageFeedID& in_CompareID) const {
    if(m_ID == in_CompareID.m_ID) {
        return true;
    }
    else {
        return false;
    }
}

bool MessageFeedID::operator<(const MessageFeedID &in_CompareID) const {
    if(m_ID < in_CompareID.m_ID) {
        return true;
    }
    else {
        return false;
    }
}

bool MessageFeedID::operator>(const MessageFeedID &in_CompareID) const {
    if(m_ID > in_CompareID.m_ID) {
        return true;
    }
    else {
        return false;
    }
}
