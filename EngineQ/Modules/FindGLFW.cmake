include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(GLFW_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(GLFW_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)

	get_filename_component(GLFW_ROOT_DIR "../Libraries/GLFW" ABSOLUTE)
	
	set(GLFW_INCLUDE_DIR "${GLFW_ROOT_DIR}/include")
	set(GLFW_LIBRARY_DIR "${GLFW_ROOT_DIR}/lib${GLFW_ARCHITECTURE}")
		
	find_library(
		GLFW_LIBRARY
		glfw3.lib
		PATHS 
			${GLFW_LIBRARY_DIR}
	)
	
else(WIN32)

	find_path(
		GLFW_INCLUDE_DIR 
		GLFW/glfw3.h
		PATHS
			/usr/include
	)

	find_library(
		GLFW_LIBRARY 
		glfw
		PATHS
			/usr/lib${GLFW_ARCHITECTURE}
	)
	
endif(WIN32)

find_package_handle_standard_args(GLFW "GLFW" GLFW_LIBRARY GLFW_INCLUDE_DIR)
mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)

set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set(GLFW_LIBRARIES ${GLFW_LIBRARY})
	
