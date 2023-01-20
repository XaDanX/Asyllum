//
// Created by XaDanX on 12/1/2022.
//

#include "Renderer.h"
#include "../Locator/Locator.h"

void Renderer::Text(const Vector2 &pos, const char *text, const ImVec4 &color) {
    ImVec2 size = ImGui::CalcTextSize(text);
    drawList->AddText(ImVec2(pos.x - size.x/2.f, pos.y - size.y/2.f), ImColor(color), text);
}

void Renderer::DrawCircleAt(const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) {
    if (numPoints >= 200)
        return;

    static ImVec2 points[200];

    ImDrawList* canvas = ImGui::GetBackgroundDrawList();

    float step = 6.2831f / numPoints;
    float theta = 0.f;
    for (int i = 0; i < numPoints; i++, theta += step) {
        Vector3 worldSpace = { worldPos.x + radius * cos(theta), worldPos.y, worldPos.z - radius * sin(theta) };
        Vector2 screenSpace = locator->GetEngine()->WorldToScreen(worldSpace);

        points[i].x = screenSpace.x;
        points[i].y = screenSpace.y;
    }

    if (filled)
        canvas->AddConvexPolyFilled(points, numPoints, color);
    else
        canvas->AddPolyline(points, numPoints, color, true, thickness);
}