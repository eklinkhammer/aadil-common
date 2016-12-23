cmake_minimum_required(VERSION 3.7.1)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)

set (LIB_NAME ccea)
set (WRAPPER_DIR /Users/klinkhae/research/cpp_ws/fann-cpp-vector)
set (SOURCE src/ccea.cpp)
set (TEST_SOURCE test/ccea_test.cpp)
set (TEST_EXEC runUnitTestsCCEA)
set (INCLUDE_DIRS ${WRAPPER_DIR}/include include)
set (TEST_LINK_DIRS gtest gtest_main fann ${LIB_NAME})

find_package(fann)
 
## Create Library
add_library (${LIB_NAME} ${SOURCE})
target_include_directories (${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})

enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE})
target_link_libraries(${TEST_EXEC} ${TEST_LINK_DIRS})
add_test(NAME gtest-${LIB_NAME} COMMAND ${TEST_EXEC})
