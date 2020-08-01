cmake_minimum_required(VERSION 3.10)

project(T_MSG_FEED_ID VERSION 1.0)

set(PMC_DIR "../../src")
set(MSG_SYS_DIR "${PMC_DIR}/msg_sys")

add_executable(T_MSG_FEED_ID "test.cpp" "${MSG_SYS_DIR}/msg_feed_id.cpp")

target_include_directories(T_MSG_FEED_ID PRIVATE "../../src" "../../src/*")

add_definitions( -DTESTING )

if(WIN32)
    target_compile_options(T_MSG_FEED_ID PRIVATE /MT)
    target_link_options(T_MSG_FEED_ID PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
