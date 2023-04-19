cmake_minimum_required(VERSION 3.15)
project(MazeGame)

set(CMAKE_CXX_STANDARD 17)

# Finn og inkluder threepp og imgui biblioteker
find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Opprett en liste med alle .cpp-filer i src-mappen
file(GLOB_RECURSE SOURCES "*.cpp")

# Opprett en liste med alle .hpp-filer i src-mappen
file(GLOB_RECURSE HEADERS "*.hpp")

# Legg til alle .cpp-filer og .hpp-filer til et bibliotek kalt maze_library
add_library(maze_library ${SOURCES} ${HEADERS})

# Link maze_library med threepp og imgui biblioteker
target_link_libraries(maze_library PRIVATE threepp::threepp imgui::imgui)

# Opprett en exekverbar fil kalt MazeGame og link den med maze_library
add_executable(MazeGame main.cpp)
target_link_libraries(MazeGame PRIVATE maze_library)
