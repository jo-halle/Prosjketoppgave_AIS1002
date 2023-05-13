cmake_minimum_required(VERSION 3.10)
project(MazeGameTests)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
include_directories(../threepp)

add_executable(MazeGameTests maze_tests.cpp ../src/maze.cpp ../src/box.cpp)
add_executable(GameTests game_test.cpp ../src/game.cpp ../src/box.cpp ../src/maze.cpp)
add_executable(MainGameTests main_test.cpp ../src/maze.cpp ../src/box.cpp ../src/game.cpp)

target_link_libraries(MazeGameTests PRIVATE threepp::threepp imgui::imgui)
target_link_libraries(GameTests PRIVATE threepp::threepp imgui::imgui)
target_link_libraries(MainGameTests PRIVATE threepp::threepp imgui::imgui)
