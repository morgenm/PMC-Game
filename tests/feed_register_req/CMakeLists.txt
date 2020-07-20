cmake_minimum_required(VERSION 3.10)

project(TEST_PROG VERSION 1.0)

set(PMC_DIR "../../src")
set(MSG_SYS_DIR "${PMC_DIR}/msg_sys")

add_executable(TEST_PROG "test.cpp" "${MSG_SYS_DIR}/feed_register_req.cpp" "${MSG_SYS_DIR}/engine_msg_feed.cpp")

target_include_directories(TEST_PROG PRIVATE "../../src" "../../src/*")

if(WIN32)
    target_compile_options(TEST_PROG PRIVATE /MT)
    target_link_options(TEST_PROG PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
