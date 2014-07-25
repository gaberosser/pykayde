cmake_minimum_required(VERSION 2.8.3)

project( pykayde )

set(CMAKE_CXX_FLAGS "-fPIC -O3")

# put our local cmake find scripts at the beginning of the cmake
# module search path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Boost.Numpy/libs/numpy/cmake ${CMAKE_MODULE_PATH})

# configure output folders so artifacts are built into a single set of
# top-level folders rather than the default cmake build structure that
# matches the source tree.

# TEMPORARY: libs in main directory for easy testing
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Output directory for static libraries.")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    CACHE PATH "Output directory for shared libraries.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    CACHE PATH "Output directory for executables and DLL's.")

# find required python packages
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
#find_package(NumPy REQUIRED)
set(NUMPY_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Boost.Numpy)
set(ALGLIB_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/libalg)

# find boost
# 
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON) 
# set(Boost_USE_STATIC_RUNTIME ON)
FIND_PACKAGE(Boost COMPONENTS python REQUIRED)

message( STATUS "found boost:"
  "\nINCLUDE: ${Boost_INCLUDE_DIRS}"
  "\nLIB: ${Boost_LIBRARIES}"
)

message( STATUS "numpy:"
  "\nINCLUDE: ${NUMPY_INCLUDE_DIRS}"
)

# add_definitions( -DBOOST_ALL_NO_LIB )
# In some cases, you may need to explicitly specify that a dynamic Boost is used; if so use:
# add_definitions( -DBOOST_ALL_DYN_LINK )

# variable controlling whether the boost_numpy is a shared or static library
if (WIN32)
  set(LIBRARY_TYPE STATIC CACHE STRING "type of library to make for boost_numpy")
else()
  set(LIBRARY_TYPE SHARED CACHE STRING "type of library to make for boost_numpy")
endif()

# compiler definitions for non-windows builds
if (NOT WIN32)
  add_definitions(-fPIC)
endif()

# enable ctest targets
ENABLE_TESTING()

# global settings for include paths
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PYTHON_INCLUDE_DIRS}
  ${NUMPY_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${ALGLIB_INCLUDE_DIRS}
  )

# install headers
install(DIRECTORY boost
    DESTINATION "include"
    FILES_MATCHING
    PATTERN "*.hpp"
    ${INSTALL_PERMISSIONS_SRC}
  )

# add submodules
ADD_SUBDIRECTORY(Boost.Numpy/libs/numpy/src)
ADD_SUBDIRECTORY(src)

