cmake_minimum_required(VERSION 3.0)

project(EngineQDemonstrationScripts)

set(BUILD_BIN_PATH "bin/\$(Configuration)")
set(BUILD_OBJ_PATH "obj/")

set(DEPENDENCIES
	EngineQScripting
)

set(PROJECT_GUID "50F6A5A2-668F-4000-A608-20CEEAD52D32")









# Set output directories
get_filename_component(PROJECT_ROOT_PATH "./" ABSOLUTE)

set(CS_PROJECT_FILE_PATH "${PROJECT_ROOT_PATH}/${PROJECT_NAME}.csproj")

file(RELATIVE_PATH BUILD_ROOT_RELATIVE_PATH ${PROJECT_ROOT_PATH} ${BUILD_ROOT_PATH})

set(BUILD_BIN_PATH "${BUILD_ROOT_RELATIVE_PATH}/${PROJECT_NAME}/${BUILD_BIN_PATH}")
set(BUILD_OBJ_PATH "${BUILD_ROOT_RELATIVE_PATH}/${PROJECT_NAME}/${BUILD_OBJ_PATH}")

string(REPLACE "/" "\\" BUILD_BIN_PATH ${BUILD_BIN_PATH})
string(REPLACE "/" "\\" BUILD_OBJ_PATH ${BUILD_OBJ_PATH})

file(STRINGS ${CS_PROJECT_FILE_PATH} CS_PROJECT_CONTENT)

set(CS_PROJECT_NEW_FILE_PATH "${CS_PROJECT_FILE_PATH}.tmp")
file(WRITE ${CS_PROJECT_NEW_FILE_PATH})

foreach(LINE IN ITEMS ${CS_PROJECT_CONTENT})
	string(REGEX MATCH "<OutputPath>.*</OutputPath>" FOUND ${LINE})	
	if(FOUND)
		string(REPLACE ${FOUND} "<OutputPath>${BUILD_BIN_PATH}</OutputPath>" LINE ${LINE})
	endif(FOUND)
	
	string(REGEX MATCH "<BaseIntermediateOutputPath>.*</BaseIntermediateOutputPath>" FOUND ${LINE})
	if(FOUND)
		string(REPLACE ${FOUND} "<BaseIntermediateOutputPath>${BUILD_OBJ_PATH}</BaseIntermediateOutputPath>" LINE ${LINE})
	endif(FOUND)
	
	if(CMAKE_BUILD_TYPE)
		string(REGEX MATCH "<Configuration Condition=\\\" \\'\\\$\\(Configuration\\)\\' == \\'\\' \\\">(Debug|Release)</Configuration>" FOUND ${LINE})
		if(FOUND)
			if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
				string(REGEX REPLACE "(Debug|Release)" "Debug" LINE ${LINE})
			endif()
			if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
				string(REGEX REPLACE "(Debug|Release)" "Release" LINE ${LINE})
			endif()
		endif(FOUND)
	endif(CMAKE_BUILD_TYPE)

	file(APPEND ${CS_PROJECT_NEW_FILE_PATH} "${LINE}\n")
endforeach()

file(RENAME ${CS_PROJECT_NEW_FILE_PATH} ${CS_PROJECT_FILE_PATH})

# Add project file
if(MSVC)

	include_external_msproject(
		${PROJECT_NAME} ${CS_PROJECT_FILE_PATH}
		TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
		GUID ${PROJECT_GUID}
	)

else(MSVC)
	
	file(STRINGS ${CS_PROJECT_FILE_PATH} CS_PROJECT_CONTENT)
	
	foreach(LINE IN ITEMS ${CS_PROJECT_CONTENT})
		string(REGEX MATCH "<Compile( )*Include( )*=( )*\\\".*\\\"( )*/>" FOUND ${LINE})
		if(FOUND)
			string(REGEX MATCH "\\\".*\\\"" INCLUDED_FILE ${FOUND})
			string(REPLACE "\"" "" INCLUDED_FILE ${INCLUDED_FILE})
			string(REPLACE "\\" "/" INCLUDED_FILE ${INCLUDED_FILE})
			
			set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDED_FILE})
		endif(FOUND)
	endforeach()
	
	add_custom_target(
		${PROJECT_NAME}
		COMMAND ${XBUILD_PATH} ${CS_PROJECT_FILE_PATH} 
		SOURCES ${CS_PROJECT_FILE_PATH} ${SOURCE_FILES}
	)
	
	foreach(SOURCE_FILE IN ITEMS ${SOURCE_FILES})
		get_filename_component(SOURCE_FILE_PATH ${SOURCE_FILE} PATH)
		string(CONCAT SOURCE_FILE_RELATIVE_PATH "Source/" ${SOURCE_FILE_PATH})
		string(REPLACE "/" "\\" SOURCE_GROUP_PATH ${SOURCE_FILE_RELATIVE_PATH})
		source_group(${SOURCE_GROUP_PATH} FILES ${SOURCE_FILE})
	endforeach()

endif(MSVC)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "EngineQDemonstration")

if(DEPENDENCIES)
	add_dependencies(${PROJECT_NAME} ${DEPENDENCIES})
endif(DEPENDENCIES)
