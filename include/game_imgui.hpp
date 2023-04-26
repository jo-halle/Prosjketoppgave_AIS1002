#ifndef MAZEGAME_GAME_IMGUI_HPP
#define MAZEGAME_GAME_IMGUI_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "game.hpp"

class GameImGui {
public:
    GameImGui(GLFWwindow *window, Game *game);
    ~GameImGui();
    void render();

private:
    Game* game_;
};

#endif // MAZEGAME_GAME_IMGUI_HPP
