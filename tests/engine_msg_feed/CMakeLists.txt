cmake_minimum_required(VERSION 3.10)

project(T_ENGINE_MSG_FEED VERSION 1.0)

set(PMC_DIR "../../src")
set(MSG_SYS_DIR "${PMC_DIR}/msg_sys")

add_executable(T_ENGINE_MSG_FEED "test.cpp" "${MSG_SYS_DIR}/engine_msg_feed.cpp")

target_include_directories(T_ENGINE_MSG_FEED PRIVATE "../../src" "../../src/*")

if(WIN32)
    target_compile_options(T_ENGINE_MSG_FEED PRIVATE /MT)
    target_link_options(T_ENGINE_MSG_FEED PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
