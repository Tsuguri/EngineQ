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