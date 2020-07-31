/*
Message Feed ID
An ID value which represents a Message Feed within
the Messaging System.
*/

#pragma once

class MessageFeedID {
public:
    void NewID(); //Generate a new ID value
    bool operator==(const MessageFeedID &in_CompareID) const;
    bool operator<(const MessageFeedID &in_CompareID) const;
    bool operator>(const MessageFeedID &in_CompareID) const;
private:
    unsigned int m_ID = 0;
};
