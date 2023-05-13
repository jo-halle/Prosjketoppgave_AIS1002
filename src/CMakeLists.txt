cmake_minimum_required(VERSION 3.15)
project(MazeGame)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")

file(GLOB_RECURSE HEADERS "*.hpp")

add_library(maze_library ${SOURCES} ${HEADERS})

target_link_libraries(maze_library PRIVATE threepp::threepp imgui::imgui)

add_executable(MazeGame main.cpp)
target_link_libraries(MazeGame PRIVATE maze_library)
