cmake_minimum_required(VERSION 3.0)

project(EngineQScripting)

set(DEPENDENCIES
)

set(PROJECT_GUID "9928F89E-BAE3-48B4-9EE4-10EA062E540D")

set(FOLDER_NAME "EngineQ")





# Set output directories
set(CS_PROJECT_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.csproj")

set(BUILD_BIN_PATH "bin/\$(Configuration)")
set(BUILD_OBJ_PATH "obj/")

set(BUILD_BIN_PATH "${CMAKE_CURRENT_BINARY_DIR}/${BUILD_BIN_PATH}/")
set(BUILD_OBJ_PATH "${CMAKE_CURRENT_BINARY_DIR}/${BUILD_OBJ_PATH}/")

file(RELATIVE_PATH BUILD_BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${BUILD_BIN_PATH})
file(RELATIVE_PATH BUILD_OBJ_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${BUILD_OBJ_PATH})

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
			else(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
				string(REGEX REPLACE "(Debug|Release)" "Release" LINE ${LINE})
			endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
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

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${FOLDER_NAME})

if(DEPENDENCIES)
	add_dependencies(${PROJECT_NAME} ${DEPENDENCIES})
endif(DEPENDENCIES)
