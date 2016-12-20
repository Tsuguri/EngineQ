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

file(
	GLOB_RECURSE RESOURCE_FILES
	LIST_DIRECTORIES false
	"${CMAKE_CURRENT_SOURCE_DIR}/_Resources/*"
)

project(EngineQDemonstration CXX)

SetupProject(
	${PROJECT_NAME}
	
	EXECUTABLE
	
	INCLUDES 
		${CMAKE_SOURCE_DIR}
	
	LIBRARIES
		EngineQCommon
		EngineQRenderer
		EngineQ
			
	DEPENDENCIES
		EngineQScripting
		EngineQDemonstrationScripts
	
	SOURCES 
		${SOURCE_FILES}
	
	RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_Resources/"
	RESOURCES 
		${RESOURCE_FILES}
	
	OUTPUT_PATH "${BUILD_ROOT_PATH}/${PROJECT_NAME}/bin"
	FOLDER "EngineQDemonstration"
)

if(WIN32)
	Assimp_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
	Mono_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()


# Copy EngineQ.dll
set(DESTINATION "$<TARGET_FILE_DIR:${PROJECT_NAME}>/")

set(SOURCES_DIR "${BUILD_ROOT_PATH}/EngineQScripting/bin/$<CONFIGURATION:${PROJECT_NAME}>") 
set(SOURCES 
	"${SOURCES_DIR}/EngineQ.dll" 
#	"${SOURCES_DIR}/EngineQ.dll.mdb"
)

foreach(SOURCE IN ITEMS ${SOURCES})
	CopyIfDifferent(${SOURCE} ${DESTINATION})
endforeach()


# Copy scripts *.dll
set(DESTINATION "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Scripts/")

set(SOURCES_DIR "${BUILD_ROOT_PATH}/EngineQDemonstrationScripts/bin/$<CONFIGURATION:${PROJECT_NAME}>")
unset(SOURCES)
set(SOURCES
	${SOURCES}
	"${SOURCES_DIR}/QScripts.dll"
#	"${SOURCES_DIR}/QScripts.dll.mdb"
)

foreach(SOURCE IN ITEMS ${SOURCES})
	CopyIfDifferent(${SOURCE} ${DESTINATION})
endforeach()