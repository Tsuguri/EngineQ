cmake_minimum_required(VERSION 3.6)

project(EngineQDemonstration)

set(INCLUDE_DIRS
	${SOURCE_ROOT_PATH}
	${EngineQCommon_INCLUDE_DIRS}
	${EngineQRenderer_INCLUDE_DIRS}
	${EngineQ_INCLUDE_DIRS}
)

set(LIBRARIES
	EngineQCommon
	EngineQRenderer
	EngineQ
)

set(DEPENDENCIES
	EngineQScripting
	EngineQDemonstrationScripts
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

file(
	GLOB_RECURSE RESOURCE_FILES
	LIST_DIRECTORIES false
	"${PROJECT_ROOT_PATH}/_Resources/*"
)

set_source_files_properties(
	${RESOURCE_FILES}
	PROPERTIES
	HEADER_FILE_ONLY ON
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RESOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "EngineQDemonstration")

target_include_directories(${PROJECT_NAME} PUBLIC 
	${INCLUDE_DIRS}	
)

target_link_libraries(${PROJECT_NAME}
	${LIBRARIES}
)
	
add_dependencies(${PROJECT_NAME}
	${DEPENDENCIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if(WIN32)
	Assimp_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
	Mono_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

CopyDirectory("${PROJECT_ROOT_PATH}/_Resources" $<TARGET_FILE_DIR:${PROJECT_NAME}>)










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

foreach(SOURCE_FILE IN ITEMS ${RESOURCE_FILES})
    get_filename_component(SOURCE_FILE_PATH ${SOURCE_FILE} PATH)
	file(RELATIVE_PATH SOURCE_FILE_RELATIVE_PATH "${PROJECT_ROOT_PATH}/_Resources/" ${SOURCE_FILE_PATH})
	string(CONCAT SOURCE_FILE_RELATIVE_PATH "Resources/" ${SOURCE_FILE_RELATIVE_PATH})
    string(REPLACE "/" "\\" SOURCE_GROUP_PATH ${SOURCE_FILE_RELATIVE_PATH})
    source_group(${SOURCE_GROUP_PATH} FILES ${SOURCE_FILE})
endforeach()


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
)

foreach(SOURCE IN ITEMS ${SOURCES})
	CopyIfDifferent(${SOURCE} ${DESTINATION})
endforeach()