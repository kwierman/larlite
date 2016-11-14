cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(larlite)

if (NOT DEFINED ENV{ROOTSYS} )
    message(FATAL_ERROR, "PLEASE INSTALL ROOT AND/OR source thisroot.sh")
endif()

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})
set(ROOT_INCLUDE_DIR)

FIND_PACKAGE(Boost 1.45.0 COMPONENTS python)
find_package(PythonLibs REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS}  ${PYTHON_INCLUDE_DIRS})
endif()

add_subdirectory(core)


# copy the python library in
FILE(GLOB python_libs python/*)
INSTALL(DIRECTORY ${python_libs} DESTINATION lib)
