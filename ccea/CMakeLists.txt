cmake_minimum_required(VERSION 3.7.1)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)
set (SOURCE src/ccea.cpp)
set (TEST_SOURCE test/ccea_test.cpp)
set (TEST_EXEC runUnitTestsCCEA)

find_package(fann)
 
## Create Library
#project (CCEA)
add_library (ccea ${SOURCE})
target_include_directories (ccea PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)

enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE})
target_link_libraries(${TEST_EXEC} gtest gtest_main)
target_link_libraries(${TEST_EXEC} fann)
target_link_libraries(${TEST_EXEC} ccea)
add_test(NAME gtest-ccea COMMAND ${TEST_EXEC})
