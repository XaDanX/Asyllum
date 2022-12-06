//
// Created by XaDanX on 12/7/2022.
//

#include "Console.h"
#include "../../../imgui/imgui.h"
#include "../../../Protection/XorStr.h"

void Console::Render() {
    ImGui::Begin(XorStr("Console").c_str(), &ShowConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::BeginChild(XorStr("console#scroll").c_str(), ImVec2(490, 225), true);
    for (auto i : consoleEvents) {
        ImGui::Text(i.c_str());
    }
    ImGui::EndChild();
    ImGui::End();
}

void Console::Show()
{
    ShowConsole = true;
}

void Console::Hide() {
    ShowConsole = false;
}

void Console::Print(const char* fmt, ...) {
    char buffer[512];
    ZeroMemory(buffer, 511);
    va_list argList;
            va_start(argList, fmt);
    vsprintf_s(buffer, fmt, argList);
            va_end(argList);
    consoleEvents.push_front(buffer);
    if (consoleEvents.size() > 300)
        consoleEvents.pop_back();
}