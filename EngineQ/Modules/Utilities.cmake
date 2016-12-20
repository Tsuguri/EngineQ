function(CopyIfDifferent SOURCE DESTINATION)
	if(${ARGC} GREATER 2)
		message(FATAL_ERROR "Incorrect number of arguments")
	endif()

	add_custom_command(
		TARGET ${PROJECT_NAME} 
		POST_BUILD
		
		COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION}
		COMMAND ${CMAKE_COMMAND} -E echo Copying file ${SOURCE} to ${DESTINATION}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOURCE} ${DESTINATION}
		
		COMMENT Copying ${SOURCE} to ${DESTINATION}
	)
endfunction(CopyIfDifferent)

function(CopyDirectory SOURCE DESTINATION)
	if(${ARGC} GREATER 2)
		message(FATAL_ERROR "Incorrect number of arguments")
	endif()
	
	add_custom_command(
		TARGET ${PROJECT_NAME} 
		POST_BUILD
		
		COMMAND ${CMAKE_COMMAND} -E echo Copying directory ${SOURCE} to ${DESTINATION}
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE} ${DESTINATION}
		
		COMMENT Copying directory ${SOURCE} to ${DESTINATION}
	)
endfunction(CopyDirectory)

function(Echo)
	add_custom_command(
		TARGET ${PROJECT_NAME} 
		POST_BUILD
		
		COMMAND ${CMAKE_COMMAND} -E echo ${ARGN}
	)
endfunction(Echo)




function(SetupProject PROJECT_NAME)
	
	# Parse arguments
	set(options EXECUTABLE)
	set(oneValueArgs LIBRARY FOLDER RESOURCES_DIR OUTPUT_PATH)
	set(multiValueArgs INCLUDES LIBRARIES DEPENDENCIES SOURCES RESOURCES)
	cmake_parse_arguments(SetupProject "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	
	# Checks
	if(SetupProject_EXECUTABLE AND SetupProject_LIBRARY)
		message(FATAL_ERROR "Specified both EXECUTABLE and LIIBRARY flags. Only one is permited")
	endif(SetupProject_EXECUTABLE AND SetupProject_LIBRARY)
	
	if(NOT SetupProject_EXECUTABLE AND NOT SetupProject_LIBRARY)
		message(FATAL_ERROR "Did not specified build type. Set EXECUTABLE or LIBRARY flag")
	endif(NOT SetupProject_EXECUTABLE AND NOT SetupProject_LIBRARY)
	
	if(NOT SetupProject_SOURCES)
		message(FATAL_ERROR "SOURCES cannot be empty")
	endif(NOT SetupProject_SOURCES)
	
	
	# Create executable
	if(SetupProject_EXECUTABLE)
		add_executable(${PROJECT_NAME} ${SetupProject_SOURCES} ${SetupProject_RESOURCES})
	endif(SetupProject_EXECUTABLE)

	# Create library
	if(SetupProject_LIBRARY)
		if(SetupProject_LIBRARY STREQUAL STATIC)
			add_library(${PROJECT_NAME} STATIC ${SetupProject_SOURCES} ${SetupProject_RESOURCES})
		elseif(SetupProject_LIBRARY STREQUAL SHARED)
			add_library(${PROJECT_NAME} SHARED ${SetupProject_SOURCES} ${SetupProject_RESOURCES})	
		else()
			message(FATAL_ERROR "Invalid library type: " ${SetupPtoject_LIBRARY})
		endif()
	endif(SetupProject_LIBRARY)

	
	# Set output path
	if(SetupProject_OUTPUT_PATH)
		set(LIBRARY_OUTPUT_PATH ${SetupProject_OUTPUT_PATH})
		set(EXECUTABLE_OUTPUT_PATH ${SetupProject_OUTPUT_PATH})
	endif(SetupProject_OUTPUT_PATH)
	
	
	# Set includes, libraries and dependencies
	if(SetupProject_INCLUDES)
		target_include_directories(${PROJECT_NAME} PUBLIC ${SetupProject_INCLUDES})
	endif(SetupProject_INCLUDES)

	if(SetupProject_LIBRARIES)
		target_link_libraries(${PROJECT_NAME} ${SetupProject_LIBRARIES})
	endif(SetupProject_LIBRARIES)
	
	if(SetupProject_DEPENDENCIES)
		add_dependencies(${PROJECT_NAME} ${SetupProject_DEPENDENCIES})
	endif(SetupProject_DEPENDENCIES)
	
	
	# Set project folder
	if(SetupProject_FOLDER)
		set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${SetupProject_FOLDER})
	endif(SetupProject_FOLDER)
	
	
	# Set sources folders
	foreach(SOURCE_FILE IN ITEMS ${SetupProject_SOURCES})
		get_filename_component(SOURCE_FILE_PATH ${SOURCE_FILE} PATH)
		
		if(IS_ABSOLUTE ${SOURCE_FILE_PATH})
			file(RELATIVE_PATH SOURCE_FILE_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_FILE_PATH})
		else(IS_ABSOLUTE ${SOURCE_FILE_PATH})
			set(SOURCE_FILE_RELATIVE_PATH ${SOURCE_FILE_PATH})
		endif(IS_ABSOLUTE ${SOURCE_FILE_PATH})
		
		string(CONCAT SOURCE_FILE_RELATIVE_PATH "Source/" ${SOURCE_FILE_RELATIVE_PATH})
		string(REPLACE "/" "\\" SOURCE_GROUP_PATH ${SOURCE_FILE_RELATIVE_PATH})
		source_group(${SOURCE_GROUP_PATH} FILES ${SOURCE_FILE})
	endforeach()
	
	
	# Process resources
	if(SetupProject_RESOURCES)
		if(NOT SetupProject_RESOURCES_DIR)
			message(FATAL_ERROR "Resources directory not specified")
		endif(NOT SetupProject_RESOURCES_DIR)
		
		# Set resource flags
		set_source_files_properties(
			${SetupProject_RESOURCES}
			PROPERTIES
				HEADER_FILE_ONLY ON
		)
		
		# Set resources folders
		foreach(SOURCE_FILE IN ITEMS ${SetupProject_RESOURCES})
			get_filename_component(SOURCE_FILE_PATH ${SOURCE_FILE} PATH)
			
			if(IS_ABSOLUTE ${SOURCE_FILE_PATH})
				file(RELATIVE_PATH SOURCE_FILE_RELATIVE_PATH ${SetupProject_RESOURCES_DIR} ${SOURCE_FILE_PATH})
			else(IS_ABSOLUTE ${SOURCE_FILE_PATH})
				set(SOURCE_FILE_RELATIVE_PATH ${SOURCE_FILE_PATH})
			endif(IS_ABSOLUTE ${SOURCE_FILE_PATH})
			
			string(CONCAT SOURCE_FILE_RELATIVE_PATH "Resources/" ${SOURCE_FILE_RELATIVE_PATH})
			string(REPLACE "/" "\\" SOURCE_GROUP_PATH ${SOURCE_FILE_RELATIVE_PATH})
			source_group(${SOURCE_GROUP_PATH} FILES ${SOURCE_FILE})
		endforeach()
		
		CopyDirectory(${SetupProject_RESOURCES_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
	endif(SetupProject_RESOURCES)

	
#	if(WIN32)
#		Assimp_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
#		Mono_COPY_BINARIES($<TARGET_FILE_DIR:${PROJECT_NAME}>)
#	endif()
#
#	CopyDirectory("${PROJECT_ROOT_PATH}/_Resources" $<TARGET_FILE_DIR:${PROJECT_NAME}>)


	
	
endfunction(SetupProject)