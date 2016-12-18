cmake_minimum_required(VERSION 3.7.1)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)
set (SOURCE src/simNetEval.cpp src/simulation.cpp)
set (TEST_SOURCE test/simulation_test.cpp)
set (TEST_EXEC runUnitTestsSimulation)

find_package(fann)
 
## Create Library
add_library (simulation ${SOURCE})
target_include_directories (simulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)
target_include_directories (simulation PUBLIC ../ccea/include)
target_include_directories (simulation PUBLIC ../models/include)

enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE})
target_link_libraries(${TEST_EXEC} gtest gtest_main)
target_link_libraries(${TEST_EXEC} fann)
target_link_libraries(${TEST_EXEC} simulation)
target_link_libraries(${TEST_EXEC} ${CMAKE_BINARY_DIR}/ccea/libccea.a)
target_link_libraries(${TEST_EXEC} ${CMAKE_BINARY_DIR}/models/libmodels.a)
add_test(NAME gtest-simulation COMMAND ${TEST_EXEC})
