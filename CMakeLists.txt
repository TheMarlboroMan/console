cmake_minimum_required(VERSION 3.6.0)
project(console)

option(BUILD_EXAMPLES "Build example code" ON)
option(BUILD_DEBUG "Build a debug release" OFF)
option(BUILD_SHARED "Build a shared library" ON)
option(BUILD_STATIC "Build a static library" OFF)

#library version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

if(${BUILD_DEBUG})

	set(RELEASE_VERSION "debug")

else()

	set(RELEASE_VERSION "prod")
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.22.0")

	add_definitions(-DMAJOR_VERSION=${MAJOR_VERSION})
	add_definitions(-DMINOR_VERSION=${MINOR_VERSION})
	add_definitions(-DPATCH_VERSION=${PATCH_VERSION})
	add_definitions(-DRELEASE_VERSION=\"${RELEASE_VERSION}\")
else()

	add_compile_definitions(MAJOR_VERSION=${MAJOR_VERSION})
	add_compile_definitions(MINOR_VERSION=${MINOR_VERSION})
	add_compile_definitions(PATCH_VERSION=${PATCH_VERSION})
	add_compile_definitions(RELEASE_VERSION=\"${RELEASE_VERSION}\")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#Add the include directory.
include_directories("include")
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

#library type and filenames.
if(${BUILD_DEBUG})

	set(CMAKE_BUILD_TYPE Debug)
	set(LIB_FILENAME "console_debug")
else()

	set(CMAKE_BUILD_TYPE Release)
	set(LIB_FILENAME "console")
endif()

if(${BUILD_SHARED})
	add_library(console_shared SHARED ${SOURCE})
	set_target_properties(console_shared PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(console_shared PUBLIC "-DLIB_VERSION=\"static\"")
	install(TARGETS console_shared DESTINATION lib)

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-shared")
endif()

if(${BUILD_STATIC})
	add_library(console_static STATIC ${SOURCE})
	set_target_properties(console_static PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(console_static PUBLIC "-DLIB_VERSION=\"static\"")
	install(TARGETS console_static DESTINATION lib)

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-static")
endif()

set(INSTALL_DIR "include")
install(DIRECTORY include/ DESTINATION ${INSTALL_DIR} FILES_MATCHING PATTERN "*.h")

IF(WIN32)
	if(${BUILD_SHARED)
		target_compile_definitions(console_shared PUBLIC -DWINBUILD)
	endif()
	if(${BUILD_STATIC})
		target_compile_definitions(console_static PUBLIC -DWINBUILD)
	endif()
ENDIF()

if(${BUILD_EXAMPLES})

	if(!${BUILD_SHARED})

		message(FATAL_ERROR "The shared library must be built to build the examples!")
	endif()

	add_executable(stdout-console examples/stdout-console.cpp)
	target_link_libraries(stdout-console console_shared)

	add_executable(ostringstream-console examples/ostringstream.cpp)
	target_link_libraries(ostringstream-console console_shared)

endif()
