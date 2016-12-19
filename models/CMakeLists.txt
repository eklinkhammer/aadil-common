cmake_minimum_required(VERSION 3.7.1)

enable_language(CXX)

set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_MACOSX_RPATH 1)
set (SOURCE src/actor.cpp src/agent.cpp src/globalAgent.cpp src/globalAgentDpp.cpp src/localAgent.cpp src/localAgentDpp.cpp src/location.cpp src/poi.cpp src/roverDomain.cpp src/world.cpp)
set (TEST_SOURCE test/actor_test.cpp test/agent_test.cpp test/globalAgent_test.cpp test/globalAgentDpp_test.cpp test/localAgent_test.cpp test/location_test.cpp test/poi_test.cpp test/roverDomain_test.cpp test/world_test.cpp)
set (TEST_EXEC runUnitTestsModels)

find_package(fann)

add_library(models ${SOURCE})
target_include_directories (models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)

enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE})
target_link_libraries(${TEST_EXEC} gtest gtest_main)
target_link_libraries(${TEST_EXEC} fann)
target_link_libraries(${TEST_EXEC} models)
add_test(NAME gtest-models COMMAND ${TEST_EXEC})
