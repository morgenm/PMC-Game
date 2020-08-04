cmake_minimum_required(VERSION 3.10)

project(T_SINGLETON VERSION 1.0)

set(PMC_DIR "../../src")
set(ENGINE_DIR "${PMC_DIR}/engine")

add_executable(T_SINGLETON "test.cpp")

target_include_directories(T_SINGLETON PRIVATE "../../src" "../../src/*")

add_definitions( -DTESTING )

if(WIN32)
    target_compile_options(T_SINGLETON PRIVATE /MT)
    target_link_options(T_SINGLETON PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
