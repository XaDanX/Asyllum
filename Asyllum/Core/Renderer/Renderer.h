//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_RENDERER_H
#define ASYLLUM_RENDERER_H


#include "../../imgui/imgui.h"
#include "../../Math/Vector.h"


class Renderer {
private:
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
public:
    void Text(const Vector2& pos, const char* text, const ImVec4& color);
    void DrawCircleAt(const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness);
    void DrawRiotCircle(const Vector3& pos, float radius, ImColor color);
};


#endif //ASYLLUM_RENDERER_H
