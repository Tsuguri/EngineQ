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
		ALWAYS_DO_POST_BUILD
		EngineQScripting
		EngineQDemonstrationScripts
	
	SOURCES 
		${SOURCE_FILES}
	
	RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/_Resources/"
	RESOURCES 
		${RESOURCE_FILES}
	
	ADDITIONAL_FILES
		${ALWAYS_DO_POST_BUILD_FILE}
	
	OUTPUT_PATH "${BUILD_ROOT_PATH}/${PROJECT_NAME}/bin"
	FOLDER "EngineQDemonstration"
)

if(WIN32)
	Assimp_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
	Mono_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
	
	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		message( "64 bits compiler detected" )
		set( PLATFORM_NAME "x64" )
	else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
		message( "32 bits compiler detected" )
		set( PLATFORM_NAME "Win32" )
	endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	
	set(DEBUGGER_WORKING_DIR "\$(TargetDir)")
	
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/_Templates/${PROJECT_NAME}.vcxproj.user.template" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user") 
	
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