cmake_minimum_required(VERSION 3.7.1)
project (DPP)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)


set (EXEC execProject)
set (EXTERNAL_DEPS fann yaml-cpp)
set (INTERNAL_DEPS ccea models simulation fann-cpp-vector)
set (INCLUDE_DIRS include ccea/include models/include simulation/include fann-cpp-vector/include)

## Google Test Setup
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

## Find external libraries
find_package(fann)
find_package(yaml-cpp)
 
## Add all subdirectories that have their own cmakes
add_subdirectory (ccea)
add_subdirectory (models)
add_subdirectory (simulation)
add_subdirectory (fann-cpp-vector)

## Create Executable
add_executable(${EXEC} src/experiment.cpp src/runner.cpp)
target_include_directories(${EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${EXEC} ${EXTERNAL_DEPS})

add_dependencies(${EXEC} ${INTERNAL_DEPS})

## Link created libraries
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/ccea/libccea.a)
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/models/libmodels.a)
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/simulation/libsimulation.a)
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/fann-cpp-vector/libfann-cpp-vector.a)
