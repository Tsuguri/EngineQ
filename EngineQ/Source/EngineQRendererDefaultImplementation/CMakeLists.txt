cmake_minimum_required(VERSION 3.0)

file(
    GLOB_RECURSE SOURCE_FILES 
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.inl"
)

project(EngineQRendererDefaultImplementation CXX)

SetupProject(
	${PROJECT_NAME}
	
	LIBRARY STATIC
	
	INCLUDES 
		${CMAKE_SOURCE_DIR}
		${GLFW_INCLUDE_DIRS}
		${Glew_INCLUDE_DIRS}
		${Assimp_INCLUDE_DIRS}
		${SOIL_INCLUDE_DIRS}
	
	LIBRARIES
		EngineQCommon
		EngineQRenderer
		${OPENGL_LIBRARIES}
		${GLFW_LIBRARIES}
		${Glew_LIBRARIES}
		${SOIL_LIBRARIES}
		${Assimp_LIBRARIES}
			
	SOURCES 
		${SOURCE_FILES}
	
#	OUTPUT_PATH "${BUILD_ROOT_PATH}/${PROJECT_NAME}/bin"
	FOLDER "EngineQ"
)

target_compile_definitions(${PROJECT_NAME} PUBLIC 
	"-DGLEW_STATIC"
)
