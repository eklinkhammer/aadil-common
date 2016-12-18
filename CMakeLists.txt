cmake_minimum_required(VERSION 3.7.1)
project (DPP)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)
set (EXEC execProject)
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

find_package(fann)
 
## Create Libraries
add_subdirectory (ccea)
add_subdirectory (models)
add_subdirectory (simulation)

## Create Executable
add_executable(${EXEC} src/experiment.cpp)
target_include_directories(${EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_link_libraries(${EXEC} fann)

## Link created libraries
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/ccea/libccea.a)
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/models/libmodels.a)
target_link_libraries(${EXEC} ${CMAKE_BINARY_DIR}/simulation/libsimulation.a)

## Include libraries
target_include_directories (${EXEC} PUBLIC ccea/include)
target_include_directories (${EXEC} PUBLIC models/include)
target_include_directories (${EXEC} PUBLIC simulation/include)
