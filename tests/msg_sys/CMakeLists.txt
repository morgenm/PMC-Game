cmake_minimum_required(VERSION 3.10)

project(T_MSG_SYS VERSION 1.0)

set(PMC_DIR "../../src")
set(MSG_SYS_DIR "${PMC_DIR}/msg_sys")

add_executable(T_MSG_SYS "test.cpp" "${MSG_SYS_DIR}/feed_register_req.cpp" "${MSG_SYS_DIR}/engine_msg_feed.cpp" "${MSG_SYS_DIR}/msg_sys.cpp" "${MSG_SYS_DIR}/msg_feed_id.cpp")

target_include_directories(T_MSG_SYS PRIVATE "../../src" "../../src/*")

if(WIN32)
    target_compile_options(T_MSG_SYS PRIVATE /MT)
    target_link_options(T_MSG_SYS PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
