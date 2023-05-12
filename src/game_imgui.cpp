#include "game_imgui.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


GameImGui::GameImGui(GLFWwindow* window, Game* game) : game_(game) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void GameImGui::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Game Control");
    if (ImGui::Button("Start")) {
        game_->start();
    }
    if (ImGui::Button("Stop")) {
        game_->stop();
    }
    if (ImGui::Button("Reset")) {
        game_->reset();
    }
    ImGui::End();

    if (game_->isRunning()) {
        // Other ImGui rendering logic goes here
    }

    if (game_->winOverlay) {
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;

        ImVec2 winOverlayPos(windowSize.x / 2 - 200, windowSize.y / 2 - 150);
        ImVec2 winOverlaySize(400, 75);

        ImGui::SetNextWindowPos(winOverlayPos);
        ImGui::SetNextWindowSize(winOverlaySize);

        ImGui::Begin("Congratulations!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Congratulations! You have won the game!");
        ImGui::Text("Time taken: %.2f seconds", game_->duration.count());
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GameImGui::~GameImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
