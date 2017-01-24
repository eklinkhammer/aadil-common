cmake_minimum_required(VERSION 3.7.1)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)

set (SOURCE src/simNetEval.cpp src/simulation.cpp)
set (LIB_NAME simulation)
set (INCLUDE_DIRS ../ccea/include ../models/include ../fann-cpp-vector/include include)

find_package(fann)
 
## Create Library
add_library (${LIB_NAME} ${SOURCE})
target_include_directories (${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
