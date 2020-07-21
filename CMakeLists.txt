cmake_minimum_required(VERSION 3.10)

project(PMC VERSION 0.1)

file(GLOB pmc_cpp {
    "src/*.cpp"
    "src/*/*.cpp"
})

add_executable(PMC "${pmc_cpp}")

target_include_directories(PMC PRIVATE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/*")

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release )
endif()

if( CMAKE_BUILD_TYPE MATCHES Debug)
    set( BUILD_TESTS TRUE )
endif()

if( BUILD_TESTS )
    add_subdirectory( tests )
endif()

if(WIN32)
    target_compile_options(PMC PRIVATE /MT)
    target_link_options(PMC PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
