cmake_minimum_required(VERSION 3.15)
project(MazeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(testMain main.cpp src/box.cpp src/game.cpp)
target_link_libraries(testMain PRIVATE threepp::threepp imgui::imgui)

add_executable(testMain2 main2.cpp )
target_link_libraries(testMain2 PRIVATE threepp::threepp imgui::imgui)

