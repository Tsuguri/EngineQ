include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Glew_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(Glew_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)

	get_filename_component(Glew_ROOT_DIR "../Libraries/Glew" ABSOLUTE)
	
	set(Glew_INCLUDE_DIR "${Glew_ROOT_DIR}/include")
	set(Glew_LIBRARY_DIR "${Glew_ROOT_DIR}/lib${Glew_ARCHITECTURE}")
		
	find_library(
		Glew_LIBRARY
		glew32s.lib
		PATHS 
			${Glew_LIBRARY_DIR}
	)
	
else(WIN32)

	find_path(
		Glew_INCLUDE_DIR 
		GL/glew.h
		PATHS
		/usr/include
	)

	find_library(
		Glew_LIBRARY 
		GLEW
		PATHS
		/usr/lib${Glew_ARCHITECTURE}
	)
	
endif(WIN32)

find_package_handle_standard_args(Glew "Glew" Glew_LIBRARY Glew_INCLUDE_DIR)
mark_as_advanced(Glew_INCLUDE_DIR Glew_LIBRARY)

set(Glew_INCLUDE_DIRS ${Glew_INCLUDE_DIR})
set(Glew_LIBRARIES ${Glew_LIBRARY})
	
