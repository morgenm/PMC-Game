cmake_minimum_required(VERSION 3.10)
project(PMC)


file(GLOB pmc_src {
	"src/*.h"
	"src/*.cpp"
	"src/*/*.h"
	"src/*/*.cpp"
})

if(CMAKE_SIZEOF_VOID_P EQUAL 8) #If 64 bit
	set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin/x64")
else()
	set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin/x86")
endif()

find_library(
	BulletCollision
	NAMES BulletCollision_gmake libBulletCollision_gmake BulletCollision
	PATHS ${BIN_DIR}
)

find_library(
	BulletDynamics
	NAMES BulletDynamics_gmake libBulletDynamics_gmake BulletDynamics
	PATHS ${BIN_DIR}
)
find_library(
	BulletLinearMath
	NAMES LinearMath_gmake libLinearMath_gmake LinearMath
	PATHS ${BIN_DIR}
)

find_library(
	Irrlicht
	NAMES Irrlicht Irrlicht.lib
	PATHS ${BIN_DIR}
)

configure_file(${BIN_DIR}/Irrlicht.dll ${CMAKE_SOURCE_DIR}/build COPYONLY)

include_directories(${CMAKE_SOURCE_DIR}/../irrlicht_engine/include ${CMAKE_SOURCE_DIR}/../bullet3/src)

add_executable(PMC ${pmc_src})

set_target_properties(PMC PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(PMC ${Irrlicht} ${BulletDynamics} ${BulletCollision} ${BulletLinearMath})

if(WIN32)
	target_compile_options(PMC PRIVATE /MT)
	target_link_options(PMC PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
	add_custom_command(
		TARGET PMC POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PMC> ${CMAKE_SOURCE_DIR}/build/PMC.exe
		COMMENT "Created PMC."
	)
endif()
