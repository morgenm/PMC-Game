#pragma once

#ifndef NDEBUG
#include <iostream>
#define assert(condition, message, action) { \
    if(!(condition)) { \
        std::cout << "Assert failed: " << message << '\n'; \
        action; \
    } \
}
#endif

#ifdef NDEBUG
#define assert(condition, message, action)
#endif
