cmake_minimum_required(VERSION 3.10)

project(T_FEED_REGISTER_REQ VERSION 1.0)

set(PMC_DIR "../../src")
set(MSG_SYS_DIR "${PMC_DIR}/msg_sys")

add_executable(T_FEED_REGISTER_REQ "test.cpp" "${MSG_SYS_DIR}/feed_register_req.cpp" "${MSG_SYS_DIR}/engine_msg_feed.cpp")

target_include_directories(T_FEED_REGISTER_REQ PRIVATE "../../src" "../../src/*")

add_definitions( -DTESTING )

if(WIN32)
    target_compile_options(T_FEED_REGISTER_REQ PRIVATE /MT)
    target_link_options(T_FEED_REGISTER_REQ PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
