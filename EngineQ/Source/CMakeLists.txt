cmake_minimum_required(VERSION 3.0)

project(EngineQ)

get_filename_component(ROOT_PATH "../" ABSOLUTE)
get_filename_component(SOURCE_ROOT_PATH "./" ABSOLUTE)
get_filename_component(BUILD_ROOT_PATH "${ROOT_PATH}/Build" ABSOLUTE)
get_filename_component(LIBRARIES_ROOT_PATH "${ROOT_PATH}/Libraries" ABSOLUTE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROOT_PATH}/Modules") 

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(
	Utilities
)

set(CMAKE_CXX_STANDARD 14)

set(CURRENT_PLATFORM "x64")

if(MSVC AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	string(REPLACE "-gline-tables-only" "-g2 -gdwarf-2" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

#message(STATUS "CMAKE_CXX_IGNORE_EXTENSIONS = " "${CMAKE_CXX_IGNORE_EXTENSIONS}")
#message(STATUS "CMAKE_CXX_SOURCE_FILE_EXTENSIONS = " "${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")
#message(STATUS "CMAKE_CXX_COMPILER_ID = " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})
#message(STATUS "CMAKE_CXX_FLAGS_DEBUG = " ${CMAKE_CXX_FLAGS_DEBUG})
#message(STATUS "CMAKE_CXX_FLAGS_RELEASE = " ${CMAKE_CXX_FLAGS_RELEASE})
#message(STATUS "CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})

find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(GLFW REQUIRED)
find_package(SOIL REQUIRED)
find_package(Assimp REQUIRED)
find_package(Mono REQUIRED)

if(WIN32)
	set(XBUILD_PATH "C:/Program Files/Mono/bin/xbuild")
else(WIN32)
	set(XBUILD_PATH "xbuild")
endif(WIN32)

add_subdirectory(EngineQScripting)
add_subdirectory(EngineQDemonstrationScripts)

add_subdirectory(EngineQ)
add_subdirectory(EngineQCommon)
add_subdirectory(EngineQRenderer)
add_subdirectory(EngineQDemonstration)
