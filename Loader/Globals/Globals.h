//
// Created by XaDanX on 4/14/2023.
//

#ifndef ASYLLUM_GLOBALS_H
#define ASYLLUM_GLOBALS_H
#include <string>
#include <iostream>
#include "../imgui/imgui.h"

struct UserInfo {

};


namespace Globals {
    extern std::string key;
    extern bool loggedIn;
    extern int width;
    extern int height;
    extern char keyBuffer[512];

    extern ImGuiWindowFlags flags;
    static ImFont* LogoFont;
    static ImFont* MainFont;
}
inline extern std::string encryptionKey = "xd";

#endif //ASYLLUM_GLOBALS_H
