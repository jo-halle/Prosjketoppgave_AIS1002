#include "../tests/maze_tests.cpp"
#include "../tests/game_test.cpp"

int main() {
    test_maze_generation();
    test_game();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
