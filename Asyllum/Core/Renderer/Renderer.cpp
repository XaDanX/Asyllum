//
// Created by XaDanX on 12/1/2022.
//

#include "Renderer.h"
#include "../Locator/Locator.h"
#include "../Hooking/DirectX.h"

void Renderer::Text(const Vector2 &pos, const char *text, const ImVec4 &color) {
    ImVec2 size = ImGui::CalcTextSize(text);
    drawList->AddText(ImVec2(pos.x - size.x / 2.f, pos.y - size.y / 2.f), ImColor(color), text);
}

void Renderer::DrawCircleAt(const Vector3 &worldPos, float radius, bool filled, int numPoints, ImColor color,
                            float thickness) {
    if (numPoints >= 200)
        return;

    static ImVec2 points[200];

    ImDrawList *canvas = ImGui::GetBackgroundDrawList();

    float step = 6.2831f / numPoints;
    float theta = 0.f;
    for (int i = 0; i < numPoints; i++, theta += step) {
        Vector3 worldSpace = {worldPos.x + radius * cos(theta), worldPos.y, worldPos.z - radius * sin(theta)};
        Vector2 screenSpace = locator->GetEngine()->WorldToScreen(worldSpace);

        points[i].x = screenSpace.x;
        points[i].y = screenSpace.y;
    }

    if (filled)
        canvas->AddConvexPolyFilled(points, numPoints, color);
    else
        canvas->AddPolyline(points, numPoints, color, true, thickness);
}


struct Vertex {
    float pos[3];
    D3DCOLOR col;
    float uv[2];
};


const static int VertexBuffSize = 10000;
LPDIRECT3DVERTEXBUFFER9 vertexBuff = NULL;

void Renderer::DrawRiotCircle(const Vector3 &pos, float radius, ImColor color, bool filled) {
    IDirect3DTexture9 *image;
    if (filled)
        image = locator->GetTextureManager()->GetTexture(XorStr("circle1"));
    else
        image = locator->GetTextureManager()->GetTexture(XorStr("circle1_nofill"));
    Vector2 size = Vector2(radius * 2, radius * 2);
    auto colorFixed = D3DCOLOR_ARGB((int) (color.Value.w * 255), (int) (color.Value.x * 255),
                                    (int) (color.Value.y * 255), (int) (color.Value.z * 255));

    float halfX = size.x / 2.f;
    float halfY = size.y / 2.f;

    auto p1 = Vector3(pos.x - halfX, pos.y, pos.z + halfY);
    auto p2 = Vector3(pos.x + halfX, pos.y, pos.z + halfY);
    auto p3 = Vector3(pos.x + halfX, pos.y, pos.z - halfY);
    auto p4 = Vector3(pos.x - halfX, pos.y, pos.z - halfY);


    if (!vertexBuff) {
        if (locator->GetHookingService()->GetDevice()->CreateVertexBuffer(VertexBuffSize * sizeof(Vertex),
                                                                          D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                                                          (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1),
                                                                          D3DPOOL_DEFAULT, &vertexBuff, NULL) < 0) {
            return;
        }
    }

    Vertex *vtx;
    if (vertexBuff->Lock(0, (UINT) (VertexBuffSize), (void **) &vtx, D3DLOCK_DISCARD) < 0) {
        return;
    }

    vtx->col = colorFixed;
    vtx->pos[0] = p1.x;
    vtx->pos[1] = p1.y;
    vtx->pos[2] = p1.z;
    vtx->uv[0] = 0.f;
    vtx->uv[1] = 0.f;

    vtx++;
    vtx->col = colorFixed;
    vtx->pos[0] = p2.x;
    vtx->pos[1] = p2.y;
    vtx->pos[2] = p2.z;
    vtx->uv[0] = 1.f;
    vtx->uv[1] = 0.f;

    vtx++;
    vtx->col = colorFixed;
    vtx->pos[0] = p4.x;
    vtx->pos[1] = p4.y;
    vtx->pos[2] = p4.z;
    vtx->uv[0] = 0.f;
    vtx->uv[1] = 1.f;

    vtx++;
    vtx->col = colorFixed;
    vtx->pos[0] = p4.x;
    vtx->pos[1] = p4.y;
    vtx->pos[2] = p4.z;
    vtx->uv[0] = 0.f;
    vtx->uv[1] = 1.f;

    vtx++;
    vtx->col = colorFixed;
    vtx->pos[0] = p3.x;
    vtx->pos[1] = p3.y;
    vtx->pos[2] = p3.z;
    vtx->uv[0] = 1.f;
    vtx->uv[1] = 1.f;

    vtx++;
    vtx->col = colorFixed;
    vtx->pos[0] = p2.x;
    vtx->pos[1] = p2.y;
    vtx->pos[2] = p2.z;
    vtx->uv[0] = 1.f;
    vtx->uv[1] = 0.f;

    vtx += 6;

    vertexBuff->Unlock();
    locator->GetHookingService()->GetDevice()->SetStreamSource(0, vertexBuff, 0, sizeof(Vertex));
    locator->GetHookingService()->GetDevice()->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

    RECT scissor = {0, 0, locator->GetEngine()->WindowWidth(), locator->GetEngine()->WindowHeight()};
    locator->GetHookingService()->GetDevice()->SetScissorRect(&scissor);


    locator->GetHookingService()->GetDevice()->SetTexture(0, image);

    locator->GetHookingService()->GetDevice()->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, 2);

}

bool Renderer::CustomGuiHotkey(int *k, const ImVec2 &size_arg) {
    static bool waitingforkey = false;
    if (waitingforkey == false) {
        if (ImGui::Button(KeyNames[*(int *) k], size_arg))
            waitingforkey = true;
    } else if (waitingforkey == true) {
        ImGui::Button("...", size_arg);
        for (auto &Key: KeyCodes) {
            if (GetAsyncKeyState(Key) & 0x8000) {
                *(int *) k = Key;
                waitingforkey = false;
            }
        }
    }
    return true;
}

void Renderer::DrawPolygon(Geometry::Polygon polygon, ImColor color, int thickness) {
    ImVec2 points[200];
    int i = 0;
    for (auto& point : polygon.points) {
        Vector2 screenSpace = locator->GetEngine()->WorldToScreen(point);
        points[i].x = screenSpace.x;
        points[i].y = screenSpace.y;
        i++;
    }

    ImGui::GetBackgroundDrawList()->AddPolyline(points, i, color, true, thickness);
}

