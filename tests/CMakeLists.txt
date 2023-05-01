cmake_minimum_required(VERSION 3.10)
project(MazeGameTests)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
include_directories(../threepp)

add_executable(MazeGameTests maze_tests.cpp)

target_link_libraries(MazeGameTests ${YOUR_PROJECT_LIBRARIES})
