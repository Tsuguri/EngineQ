cmake_minimum_required(VERSION 3.6)

project(EngineQRenderer)

set(INCLUDE_DIRS
	${SOURCE_ROOT_PATH}
	${EngineQCommon_INCLUDE_DIRS}
	${Glew_INCLUDE_DIRS}
	${SOIL_INCLUDE_DIRS}
)

set(LIBRARIES
	EngineQCommon
	${OPENGL_LIBRARIES}
	${Glew_LIBRARIES}
	${SOIL_LIBRARIES}
)

get_filename_component(PROJECT_ROOT_PATH "./" ABSOLUTE)

file(
    GLOB_RECURSE SOURCE_FILES 
    LIST_DIRECTORIES false
    "${PROJECT_ROOT_PATH}/*.cpp"
    "${PROJECT_ROOT_PATH}/*.hpp"
    "${PROJECT_ROOT_PATH}/*.h"
    "${PROJECT_ROOT_PATH}/*.c"
    "${PROJECT_ROOT_PATH}/*.inl"
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${INCLUDE_DIRS}	
)

target_link_libraries(${PROJECT_NAME}
	${LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC 
	"-DGLEW_STATIC"
)










# Do not touch
set(LIBRARY_OUTPUT_PATH "${BUILD_ROOT_PATH}/${PROJECT_NAME}/bin")
set(EXECUTABLE_OUTPUT_PATH "${BUILD_ROOT_PATH}/${PROJECT_NAME}/bin")

foreach(SOURCE_FILE IN ITEMS ${SOURCE_FILES})
    get_filename_component(SOURCE_FILE_PATH ${SOURCE_FILE} PATH)
	file(RELATIVE_PATH SOURCE_FILE_RELATIVE_PATH ${PROJECT_ROOT_PATH} ${SOURCE_FILE_PATH})
	string(CONCAT SOURCE_FILE_RELATIVE_PATH "Source/" ${SOURCE_FILE_RELATIVE_PATH})
    string(REPLACE "/" "\\" SOURCE_GROUP_PATH ${SOURCE_FILE_RELATIVE_PATH})
    source_group(${SOURCE_GROUP_PATH} FILES ${SOURCE_FILE})
endforeach()
