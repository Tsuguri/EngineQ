include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Mono_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(Mono_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)

	get_filename_component(Mono_ROOT_DIR "../Libraries/Mono" ABSOLUTE)
	
	set(Mono_INCLUDE_DIR "${Mono_ROOT_DIR}/include")
	set(Mono_LIBRARY_DIR "${Mono_ROOT_DIR}/lib${Mono_ARCHITECTURE}")
		
	find_library(
		Mono_LIBRARY
		monosgen-2.0.lib
		PATHS 
			${Mono_LIBRARY_DIR}
	)
	
	function(Mono_COPY_BINARIES TargetDirectory)
		add_custom_command(
			TARGET ${PROJECT_NAME} 
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Mono_ROOT_DIR}/bin${Mono_ARCHITECTURE}/monosgen-2.0.dll ${TargetDirectory}/monosgen-2.0.dll
			COMMENT "Copying file ${SOURCE} to ${DESTINATION}"
		)
	endfunction(Mono_COPY_BINARIES)
	
else(WIN32)

	find_path(
		Mono_INCLUDE_DIR 
		mono/jit/jit.h
		PATHS
		/usr/include/mono-2.0/
	)

	find_library(
		Mono_LIBRARY 
		monosgen-2.0
		PATHS
			/usr/lib${Mono_ARCHITECTURE}
	)
	
endif(WIN32)

find_package_handle_standard_args(Mono "Mono" Mono_LIBRARY Mono_INCLUDE_DIR)
mark_as_advanced(Mono_INCLUDE_DIR Mono_LIBRARY)

set(Mono_INCLUDE_DIRS ${Mono_INCLUDE_DIR})
set(Mono_LIBRARIES ${Mono_LIBRARY})
	
