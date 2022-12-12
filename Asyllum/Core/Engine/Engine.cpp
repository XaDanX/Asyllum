//
// Created by XaDanX on 12/1/2022.
//

#include "Engine.h"
#include "../../Globals/Offsets.h"
#include "../../Globals/Globals.h"
#include "../../Math/Math.h"

float Engine::GameTime() const {
    return *reinterpret_cast<float*>(RVA((unsigned int)Offsets::Game::GameTime));
}

Vector2 Engine::WorldToScreen(const Vector3 &pos) {
    Vector2 out = { 0.f, 0.f };
    Vector2 screen = { (float)this->WindowWidth(), (float)this->WindowHeight() };
    static Vector4 clipCoords;
    clipCoords.x = pos.x * Globals::viewProjectionMatrix[0] + pos.y * Globals::viewProjectionMatrix[4] + pos.z * Globals::viewProjectionMatrix[8] + Globals::viewProjectionMatrix[12];
    clipCoords.y = pos.x * Globals::viewProjectionMatrix[1] + pos.y * Globals::viewProjectionMatrix[5] + pos.z * Globals::viewProjectionMatrix[9] + Globals::viewProjectionMatrix[13];
    clipCoords.z = pos.x * Globals::viewProjectionMatrix[2] + pos.y * Globals::viewProjectionMatrix[6] + pos.z * Globals::viewProjectionMatrix[10] + Globals::viewProjectionMatrix[14];
    clipCoords.w = pos.x * Globals::viewProjectionMatrix[3] + pos.y * Globals::viewProjectionMatrix[7] + pos.z * Globals::viewProjectionMatrix[11] + Globals::viewProjectionMatrix[15];

    if (clipCoords.w < 1.0f)
        clipCoords.w = 1.f;

    Vector3 M;
    M.x = clipCoords.x / clipCoords.w;
    M.y = clipCoords.y / clipCoords.w;
    M.z = clipCoords.z / clipCoords.w;

    out.x = (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f);
    out.y = -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f);


    return out;
}

int Engine::WindowHeight() const {
    auto renderer = *reinterpret_cast<int*>(RVA(Offsets::Game::Renderer));
    return *reinterpret_cast<int*>(renderer + Offsets::Renderer::Height);
}

int Engine::WindowWidth() const {
    auto renderer = *reinterpret_cast<int*>(RVA(Offsets::Game::Renderer));
    return *reinterpret_cast<int*>(renderer + Offsets::Renderer::Width);
}

void Engine::Update() {
    memcpy(&Globals::viewMatrix, (void*)RVA(Offsets::Game::ViewProjMatrices), 16 * sizeof(float));
    memcpy(&Globals::projectionMatrix, (void*)RVA(Offsets::Game::ViewProjMatrices + (16 * sizeof(float))), 16 * sizeof(float));
    MultiplySquareMatrices(Globals::viewProjectionMatrix, Globals::viewMatrix, Globals::projectionMatrix);
}

HudInstance* Engine::GetHudInstance() {
    return *reinterpret_cast<HudInstance**>(RVA(Offsets::Game::HudInstance));
}
