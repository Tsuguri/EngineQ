include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(SOIL_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(SOIL_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)

	get_filename_component(SOIL_ROOT_DIR "../Libraries/SOIL" ABSOLUTE)
	
	set(SOIL_INCLUDE_DIR "${SOIL_ROOT_DIR}/include")
	set(SOIL_LIBRARY_DIR "${SOIL_ROOT_DIR}/lib${SOIL_ARCHITECTURE}")
		
	find_library(
		SOIL_LIBRARY
		SOIL.lib
		PATHS 
			${SOIL_LIBRARY_DIR}
	)
	
else(WIN32)

	find_path(
		SOIL_INCLUDE_DIR 
		SOIL/SOIL.h
		PATHS
		/usr/include
	)

	find_library(
		SOIL_LIBRARY 
		SOIL
		PATHS
			/usr/lib${SOIL_ARCHITECTURE}
	)
	
endif(WIN32)

find_package_handle_standard_args(SOIL "Simple OpenGL Image Library" SOIL_LIBRARY SOIL_INCLUDE_DIR)
mark_as_advanced(SOIL_INCLUDE_DIR SOIL_LIBRARY)

set(SOIL_INCLUDE_DIRS ${SOIL_INCLUDE_DIR})
set(SOIL_LIBRARIES ${SOIL_LIBRARY})
	
