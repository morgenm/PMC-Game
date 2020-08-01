/*
Assert
Assert is a function used to ensure conditions which should never
happen are detected. This is to be used to ensure foreseen errors and
unwanted occurances are avoided. The assert function has no effect when
building Release code.
*/

#pragma once

static int testing = 0;

//If an assert occurs when testing, do nothing
#ifdef TESTING
#define exit_with_error()
#endif

//If an assert occurs when not testing, exit the program
#ifndef TESTING
#include <cstdlib>
#define exit_with_error() { \
    std::exit( EXIT_FAILURE ); \
}
#endif

#ifndef NDEBUG
#include <iostream>
#define assert( condition, message, action ) { \
    if( !( condition ) ) { \
        std::cout << "Assert failed: " << message << '\n'; \
        action; \
        exit_with_error(); \
    } \
}
#endif

#ifdef NDEBUG
#define assert( condition, message, action )
#endif
