include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Assimp_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(Assimp_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)

	get_filename_component(Assimp_ROOT_DIR "../Libraries/Assimp" ABSOLUTE)
	
	set(Assimp_INCLUDE_DIR "${Assimp_ROOT_DIR}/include")
	set(Assimp_LIBRARY_DIR "${Assimp_ROOT_DIR}/lib${Assimp_ARCHITECTURE}")
		
	find_library(
		Assimp_LIBRARY
		assimp.lib
		PATHS 
			${Assimp_LIBRARY_DIR}
	)
	
	function(Assimp_COPY_BINARIES TargetDirectory)
		add_custom_command(
			TARGET ${PROJECT_NAME} 
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Assimp_ROOT_DIR}/bin${Assimp_ARCHITECTURE}/Assimp${Assimp_ARCHITECTURE}.dll ${TargetDirectory}/Assimp${Assimp_ARCHITECTURE}.dll
			COMMENT "Copying file ${SOURCE} to ${DESTINATION}"
		)
	endfunction(Assimp_COPY_BINARIES)
	
else(WIN32)

	find_path(
		Assimp_INCLUDE_DIR 
		assimp/mesh.h
		PATHS
			/usr/include
	)

	find_library(
		Assimp_LIBRARY 
		assimp
		PATHS
			/usr/lib${Assimp_ARCHITECTURE}
	)
	
endif(WIN32)

find_package_handle_standard_args(Assimp "Assimp" Assimp_LIBRARY Assimp_INCLUDE_DIR)
mark_as_advanced(Assimp_INCLUDE_DIR Assimp_LIBRARY)

set(Assimp_INCLUDE_DIRS ${Assimp_INCLUDE_DIR})
set(Assimp_LIBRARIES ${Assimp_LIBRARY})
	
