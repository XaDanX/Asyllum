//
// Created by XaDanX on 4/14/2023.
//

#include "Globals.h"

namespace Globals {
    std::string key = "";
    bool loggedIn = false;
    int width = 500;
    int height = 400;
    char keyBuffer[512];


    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
}