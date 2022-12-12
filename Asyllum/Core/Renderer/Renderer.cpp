//
// Created by XaDanX on 12/1/2022.
//

#include "Renderer.h"

void Renderer::Text(const Vector2 &pos, const char *text, const ImVec4 &color) {
    ImVec2 size = ImGui::CalcTextSize(text);
    drawList->AddText(ImVec2(pos.x - size.x/2.f, pos.y - size.y/2.f), ImColor(color), text);
}
