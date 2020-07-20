#pragma once

#ifndef NDEBUG
#define assert(condition, message, action) { \
    if(!(condition)) { \
        std::cout << "Assert failed: " << message << '\n'; \
        action; \
    } \
}
#endif
