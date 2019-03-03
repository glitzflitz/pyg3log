# ==================================================================================================
# CMake
# ==================================================================================================
cmake_minimum_required(VERSION 3.3.0)

# ==================================================================================================
# Project declaration
# ==================================================================================================
project(pyg3log)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# ==================================================================================================
#  Paths
# ==================================================================================================

# Where our libraries are
set(LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# ==================================================================================================
# General compiler flags
# ==================================================================================================
set(CXX_STANDARD "-std=c++14")
if (WIN32)
    set(CXX_STANDARD "/std:c++14")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STANDARD} ")


if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES=1")
endif()

# Add colors to ninja builds
if (UNIX AND CMAKE_GENERATOR STREQUAL "Ninja")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
endif()

# ==================================================================================================
# Linker flags
# ==================================================================================================
# Strip unused sections
set(GC_SECTIONS "-Wl,--gc-sections")
set(B_SYMBOLIC_FUNCTIONS "-Wl,-Bsymbolic-functions")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GC_SECTIONS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${GC_SECTIONS} ${B_SYMBOLIC_FUNCTIONS}")

# Common to all platforms

add_subdirectory(${LIBRARIES}/pybind11)

FIND_PACKAGE(PythonInterp 3)
FIND_PACKAGE(PythonLibs   3)

pybind11_add_module(pyg3log MODULE src/pyg3log.cpp)
target_link_libraries( pyg3log PRIVATE g3logger )
target_link_libraries( pyg3log PRIVATE g3logrotate )
