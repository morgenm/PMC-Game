cmake_minimum_required(VERSION 3.10)

project(PMC VERSION 0.1)

file(GLOB pmc_cpp {
    "src/*.cpp"
    "src/*/*.cpp"
})

add_executable(PMC "${pmc_cpp}")

target_include_directories(PMC PRIVATE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/*")

if(WIN32)
    target_compile_options(PMC PRIVATE /MT)
    target_link_options(PMC PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()
