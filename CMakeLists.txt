#################################################################
# \file      CMakeLists.txt 
# \brief     CMake file for gammet-cpp
# \author    Doug Hague
# \date      07.06.2014
# \copyright See License.txt
#################################################################

# ---------------------------------------------------------------
# CMake settings
# ---------------------------------------------------------------
# Due to Mac OSX we need to keep compatibility with CMake 2.6
# see http://www.cmake.org/Wiki/CMake_Policies
cmake_minimum_required(VERSION 2.6)
# --> where to put binaries (relative to CMAKE_BINARY_DIR)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")

# ---------------------------------------------------------------
# Build options
# ---------------------------------------------------------------
# --> CMake verbosity
option(CMAKE_VERBOSE_MAKEFILE "Makefiles that show each command line as it is used"         OFF)
option(CMAKE_RULE_MESSAGES    "Add a progress message describing what each build rule does" ON)
# --> This package
option(BUILD_SHARED_LIBS_ONLY "Build only the shared object library" OFF)
option(BUILD_STATIC_LIBS      "Build static library"                 OFF)
option(BUILD_CONFIG           "Build configuration helpers"          ON)
option(BUILD_MAIN             "Build main executable"                ON)

# ---------------------------------------------------------------
# OS specifics
# ---------------------------------------------------------------
# --> Apple
if(APPLE)
  # set better default install prefix for MacOS
  set(CMAKE_INSTALL_PREFIX /opt/local/)
endif()
# --> Windows
if(WIN32)
  message(WARNING "Develeped on *nix")
  # use or build Windows DLL
  add_definitions(-D${PROJECT_NAME}_DLL)
  # install prefix
  if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "C:/")
  endif()
  # .dll are in PATH, like executables
  set(_library_dir bin)
endif()

# ---------------------------------------------------------------
# Project settings
# ---------------------------------------------------------------
# --> Project Name.
#     Additionally this sets the variables 
#     <projectName>_BINARY_DIR and <projectName>_SOURCE_DIR.
#     See http://www.cmake.org/cmake/help/v2.8.12/cmake.html#command:project
project(BLOBB C CXX)
# --> Project tags
set(BLOBB_MONIKER  "blobb")
set(BLOBB_TITLE    "Bleed or Be Bled")
set(BLOBB_AUTHOR   "Doug Hague <doughague@gmail.com>, Jason Torpy <jason@dday76.net>")
set(BLOBB_YEAR     "2014")
set(BLOBB_LIB_NAME "blobb")
# --> Version-ing
set(BLOBB_VERSION_MAJOR "0")
set(BLOBB_VERSION_MINOR "2")
set(BLOBB_VERSION_PATCH "0")
set(BLOBB_VERSION "${BLOBB_VERSION_MAJOR}.${BLOBB_VERSION_MINOR}.${BLOBB_VERSION_PATCH}")


# ---------------------------------------------------------------
# Find & Configure Headers
# ---------------------------------------------------------------
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckCXXSymbolExists)
# --> c standard library header
check_include_file_cxx("cstdlib" HAVE_CSTDLIB_H)
if(NOT HAVE_CSTDLIB_H)
  message(FATAL_ERROR "Must have <cstdlib>!")
endif()
# --> std::vector template
check_include_file_cxx("vector" HAVE_VECTOR_H)
if(NOT HAVE_VECTOR_H)
  message(FATAL_ERROR "Must have <vector>!")
endif()
# --> std::string template
check_include_file_cxx("string" HAVE_STRING_H)
if(NOT HAVE_STRING_H)
  message(FATAL_ERROR "Must have <string>!")
endif()

# # --> std::chrono
# check_include_file_cxx("chrono" HAVE_CHRONO_H)
# if(NOT HAVE_CHRONO_H)
#   message(FATAL_ERROR "Must have <chrono>!")
# endif()

# # --> std::random
# check_include_file_cxx("random" HAVE_RANDOM_H)
# if(NOT HAVE_RANDOM_H)
#   message(FATAL_ERROR "Must have <random>!")
# endif()

# --> cmath for C++
check_include_file_cxx("cmath" HAVE_CMATH_H)
if(HAVE_CMATH_H)  
  check_cxx_symbol_exists(erf cmath HAVE_CMATH_ERF)
  check_cxx_symbol_exists(erfc cmath HAVE_CMATH_ERFC)
  check_cxx_symbol_exists(tgamma cmath HAVE_CMATH_TGAMMA)
  check_cxx_symbol_exists(lgamma cmath HAVE_CMATH_LGAMMA)
else()
  message(FATAL_ERROR "Must have <cmath>!")
endif()
# --> numerical limits for C++
check_include_file_cxx("limits" HAVE_LIMITS_H)
if(HAVE_LIMITS_H)
  add_definitions(-DHAVE_LIMITS_H)
endif()
# --> GNU getopt
check_include_file_cxx("getopt.h" HAVE_GETOPT_H)
if(HAVE_GETOPT_H)
  add_definitions(-DHAVE_GETOPT_H)
endif()
# --> configuration: pass some build/library settings to the source code
if(BUILD_CONFIG AND NOT BUILD_SHARED_LIBS_ONLY)
  configure_file("${BLOBB_SOURCE_DIR}/src/lib/Config.hh.in" 
                 "${BLOBB_SOURCE_DIR}/include/${BLOBB_MONIKER}/Config.hh")
  set(HAVE_CONFIG_H 1)
  add_definitions(-DHAVE_CONFIG_H)
endif()
# --> 64-bit?
if(${CMAKE_SIZEOF_VOID_P} MATCHES "8")
  message(STATUS "Detected 64-bit mode")
endif()

# ---------------------------------------------------------------
# GNU Compiler Collection (~v4.8)
# ---------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX OR 
   ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
  # --> C++ GCC flags ... -std=c++11 or -std=gnu++11 
  set(CMAKE_CXX_FLAGS                "-std=c++11 -pthread -Wfatal-errors")
  set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
  set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG          "-O1 -g -DDEBUG -Wall -Wextra -Woverloaded-virtual -pedantic -Wno-missing-field-initializers")
else()
  message(WARNING "Develeped with GNU Compiler Collection v4.2.1 and v4.8.0")
endif()

# ---------------------------------------------------------------
# Customized Targets
# ---------------------------------------------------------------
add_custom_target(release $(MAKE) clean
                  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
		  COMMENT "Adjusting settings for release compilation"
		  VERBATIM)
add_custom_target(min-size-release $(MAKE) clean
                  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=MinSizeRel ${CMAKE_SOURCE_DIR}
		  COMMENT "Adjusting settings for minimum size release compilation"
		  VERBATIM)
add_custom_target(release-debug $(MAKE) clean
                  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=RelWithDebInfo ${CMAKE_SOURCE_DIR}
		  COMMENT "Adjusting settings for releasable with debug info compilation"
		  VERBATIM)
add_custom_target(debug $(MAKE) clean
                  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
		  COMMENT "Adjusting settings for debug compilation"
		  VERBATIM)
# --> Check for build type
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

# ---------------------------------------------------------------
# Module sources, headers, directories and shared-library
# ---------------------------------------------------------------
# --> Actual header files
file(GLOB headers "include/${BLOBB_MONIKER}/[a-zA-Z]*.hh")
# --> Actual source files
file(GLOB sources "src/lib/[a-zA-Z]*.cxx")
# --> Add include directories to the build
if(HAVE_ROOTSYS)
  include_directories("${BLOBB_SOURCE_DIR}/include" ${ROOTSYS_INCDIR})
else()
  include_directories("${BLOBB_SOURCE_DIR}/include")
endif()
# --> The project shared object library
add_library(lib-shared SHARED ${headers} ${sources})
set_target_properties(lib-shared 
                      PROPERTIES
                      VERSION ${BLOBB_VERSION}
		      SOVERSION ${BLOBB_VERSION_MAJOR}.${BLOBB_VERSION_MINOR}
		      OUTPUT_NAME ${BLOBB_LIB_NAME}
		      BLOBB_LABEL ${BLOBB_LIB_NAME})


# ---------------------------------------------------------------
# more than shared object library: static lib, utility executable(s)
# ---------------------------------------------------------------
if(NOT BUILD_SHARED_LIBS_ONLY)
  if(BUILD_STATIC_LIBS)
    # --> The project static library (archive)
    add_library(lib-static STATIC ${headers} ${sources})
    set_target_properties(lib-static 
                          PROPERTIES
			  OUTPUT_NAME ${BLOBB_LIB_NAME})
    target_link_libraries(lib-static)
  endif()

  if(BUILD_CONFIG)
    # --> Configuration helper executable
    add_executable(${BLOBB_LIB_NAME}-config src/progs/${BLOBB_LIB_NAME}-config.cxx)
  endif() # BUILD_CONFIG

  if(BUILD_MAIN)
    # --> Main executable
    add_executable(sandbox src/progs/sandbox.cxx)
    target_link_libraries(sandbox lib-shared)

    # --> Main executable
    add_executable(blobb src/progs/blobb.cxx)
    if(BUILD_STATIC_LIBS)
      target_link_libraries(blobb lib-static)
    else()
      target_link_libraries(blobb lib-shared)
    endif()
  endif() # BUILD_MAIN
endif() # NOT BUILD_SHARED_LIBS_ONLY

# ---------------------------------------------------------------
# Tests
# ---------------------------------------------------------------
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  # # --> Test headers
  # file(GLOB test_headers src/test/*.hh)
  # # --> Test sources
  # file(GLOB test_sources src/test/*.cxx)
  # # --> Unit-test executable
  # add_executable(unit-tests ${test_headers} ${test_sources}) 
  # target_link_libraries(unit-tests lib-shared)
  # # --> run test executable
  # add_custom_target(run-unit-tests 
  #                   COMMAND ${CMAKE_BINARY_DIR}/bin/tests
  #                   COMMENT "Testing gammet-cpp ... "
  #                   VERBATIM)
  # # --> Data-test executable
  # add_executable(data-tests src/test/data-tests.cxx)
  # target_link_libraries(data-tests lib-shared)
endif()

# ---------------------------------------------------------------
# documentation
# ---------------------------------------------------------------
include(FindDoxygen)
if(DOXYGEN_FOUND)
  # --> Set the doc directory, and config options
  set(doc_dir "${BLOBB_SOURCE_DIR}/doc")
  set(doc_cfg "${doc_dir}/doxy.cfg")
  set(doc_log "${doc_dir}/doxy-log.txt")
  set(doc_wlog "${doc_dir}/doxy-warn-log.txt")
  set(doc_head_dir "${BLOBB_SOURCE_DIR}/include")
  set(doc_src_dir "${BLOBB_SOURCE_DIR}/src")
  # --> Configuration doxygen file
  configure_file("${doc_cfg}.in" "${doc_cfg}")
  # --> Configuration mainpage file
  configure_file("${doc_dir}/mainpage.cxx.in" "${doc_dir}/mainpage.cxx")
  # --> Documentation target
  add_custom_target(doc 
                    COMMAND ${DOXYGEN_EXECUTABLE} ${doc_cfg} > ${doc_log}
                    COMMENT "Creating doxygen documentation"
                    VERBATIM)
  # --> Clean documentation target
  add_custom_target(clean-doc 
                    COMMAND rm -rf ${doc_dir}/html
                    COMMENT "Cleaning doxygen documentation"
                    VERBATIM)
endif()

# ---------------------------------------------------------------
# Install
# ---------------------------------------------------------------
# --> Destinations
set(_INSTALL_DESTINATIONS
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
# --> Shared object library
install(TARGETS lib-shared ${_INSTALL_DESTINATIONS})
# --> Static library
if(BUILD_STATIC_LIBS AND NOT BUILD_SHARED_LIBS_ONLY)
  install(TARGETS lib-static ${_INSTALL_DESTINATIONS})
endif()
# --> Headers
install(DIRECTORY      include/${BLOBB_MONIKER}
	DESTINATION    include
	FILES_MATCHING PATTERN "*.hh")
# --> Package configuration
if(UNIX)
  set(PC_FILE ${CMAKE_BINARY_DIR}/${BLOBB_MONIKER}.pc)
  configure_file(src/lib/${BLOBB_MONIKER}.pc.cmake ${PC_FILE} @ONLY)
  install(FILES ${PC_FILE} DESTINATION lib/pkgconfig)
endif()

# ---------------------------------------------------------------
# Distribution bundle
# ---------------------------------------------------------------
include(FindGit)
if(GIT_FOUND)
  # --> Distribution name
  set(ARCHIVE_NAME ${BLOBB_MONIKER}-${BLOBB_VERSION})
  # --> Distribution target
  add_custom_target(dist 
                    COMMAND ${GIT_EXECUTABLE} archive --prefix=${ARCHIVE_NAME}/ HEAD 
		            | gzip > ${CMAKE_SOURCE_DIR}/${ARCHIVE_NAME}.tgz &&
			    chmod u+x ${CMAKE_SOURCE_DIR}/${ARCHIVE_NAME}.tgz
		    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    COMMENT "Creating distribution bundle ${ARCHIVE_NAME}.tgz"
                    VERBATIM)
endif()
