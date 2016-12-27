cmake_minimum_required(VERSION 3.0)

project(EngineQ)

get_filename_component(ROOT_PATH "${CMAKE_SOURCE_DIR}/.." ABSOLUTE)
get_filename_component(LIBRARIES_ROOT_PATH "${ROOT_PATH}/Libraries" ABSOLUTE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROOT_PATH}/Modules") 

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(
	Utilities
)

set(CMAKE_CXX_STANDARD "std14")

if(MSVC AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
	string(REPLACE "-gline-tables-only" "-g2 -gdwarf-2" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

#message(STATUS "CMAKE_CXX_IGNORE_EXTENSIONS = " "${CMAKE_CXX_IGNORE_EXTENSIONS}")
#message(STATUS "CMAKE_CXX_SOURCE_FILE_EXTENSIONS = " "${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")
#message(STATUS "CMAKE_CXX_COMPILER_ID = " ${CMAKE_CXX_COMPILER_ID})
#message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})
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


# Setup always do post build. All projects dependent on this project will always execute post build
set(ALWAYS_DO_POST_BUILD_FILE "${CMAKE_SOURCE_DIR}/always_do_post_build")
file(WRITE ${ALWAYS_DO_POST_BUILD_FILE})
add_custom_target(ALWAYS_DO_POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E touch ${ALWAYS_DO_POST_BUILD_FILE}
)
set_property(TARGET ALWAYS_DO_POST_BUILD PROPERTY FOLDER "CMakePredefinedTargets")


add_custom_target(UPDATE_PROJECTS
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQCommon/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQRenderer/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQ/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQDemonstration/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQRendererDefaultImplementation/CMakeLists.txt"
	COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_SOURCE_DIR}/EngineQRendererDemonstration/CMakeLists.txt"
)
set_property(TARGET UPDATE_PROJECTS PROPERTY FOLDER "CMakePredefinedTargets")


add_subdirectory(EngineQScripting)
add_subdirectory(EngineQDemonstrationScripts)

add_subdirectory(EngineQCommon)
add_subdirectory(EngineQRenderer)
add_subdirectory(EngineQ)
add_subdirectory(EngineQDemonstration)
add_subdirectory(EngineQRendererDefaultImplementation)
add_subdirectory(EngineQRendererDemonstration)