#include "msg_sys/msg_feed_id.h"

#include <iostream>

void TryEquals() {
    MessageFeedID lhs;
    MessageFeedID rhs;
    rhs.NewID();

    if( lhs == rhs ) {
        std::cout << "MessageFeedID TryEquals Bad Test: FAILED!\n";
    }
    else {
        std::cout << "MessageFeedID TryEquals Bad Test: Passed.\n";
    }

    MessageFeedID newLHS;
    MessageFeedID newRHS;
    if( newLHS == newRHS ) {
        std::cout << "MessageFeedID TryEquals Good Test: Passed.\n";
    }
    else {
        std::cout << "MessageFeedID TryEquals Good Test: FAILED!\n";
    }
}

void TryLessThan() {
    MessageFeedID lhs;
    MessageFeedID rhs;
    if( lhs < rhs ) {
        std::cout << "MessageFeedID TryLessThan Bad Test: FAILED!\n";
    }
    else {
        std::cout << "MessageFeedID TryLessThan Bad Test: Passed.\n";
    }

    MessageFeedID newLHS;
    MessageFeedID newRHS;
    newRHS.NewID();
    if( newLHS < newRHS ) {
        std::cout << "MessageFeedID TryLessThan Good Test: Passed.\n";
    }
    else {
        std::cout << "MessageFeedID TryLessThan Good Test: FAILED!\n";
    }
}

void TryGreaterThan() {
    MessageFeedID lhs;
    MessageFeedID rhs;
    if( lhs > rhs ) {
        std::cout << "MessageFeedID TryGreaterThan Bad Test: FAILED!\n";
    }
    else {
        std::cout << "MessageFeedID TryLessThan Bad Test: Passed.\n";
    }

    MessageFeedID newLHS;
    MessageFeedID newRHS;
    newRHS.NewID();
    if( newRHS > newLHS ) {
        std::cout << "MessageFeedID TryGreaterThan Good Test: Passed.\n";
    }
    else {
        std::cout << "MessageFeedID TryGreaterThan Good Test: FAILED!\n";
    }
}

void TryNewID() {
    MessageFeedID oldID;
    MessageFeedID newID;

    newID.NewID();
    oldID = newID;

    for(int i=0; i<1000; i++) {
        newID.NewID();
    }

    if( newID > oldID ) {
        std::cout << "MessageFeedID TryNewID Many Test: Passed.\n";
    }
    else {
        std::cout << "MessageFeedID TryNewID Many Test: FAILED!\n";
    }
}

int main() {
    TryEquals();
    TryLessThan();
    TryGreaterThan();
    TryNewID();
    return 0;
}
