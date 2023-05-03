//
// Created by XaDanX on 12/1/2022.
//

#include "Engine.h"
#include "../../Globals/Offsets.h"
#include "../../Globals/Globals.h"
#include "../../Math/Math.h"
#include "../../Protection/LazyImporter.h"
#include "../Locator/Locator.h"
#include "../../Utils/Utils.h"
#include "../Managers/EventManager/Event.h"
#include <sysinfoapi.h>

float Engine::GameTime() const {
    return *reinterpret_cast<float *>(RVA(Offsets::Game::GameTime));
}

Vector2 Engine::WorldToScreen(const Vector3 &pos) {
    Vector2 out = {0.f, 0.f};
    Vector2 screen = {(float) this->WindowWidth(), (float) this->WindowHeight()};
    static Vector4 clipCoords;
    clipCoords.x = pos.x * Globals::viewProjectionMatrix[0] + pos.y * Globals::viewProjectionMatrix[4] +
                   pos.z * Globals::viewProjectionMatrix[8] + Globals::viewProjectionMatrix[12];
    clipCoords.y = pos.x * Globals::viewProjectionMatrix[1] + pos.y * Globals::viewProjectionMatrix[5] +
                   pos.z * Globals::viewProjectionMatrix[9] + Globals::viewProjectionMatrix[13];
    clipCoords.z = pos.x * Globals::viewProjectionMatrix[2] + pos.y * Globals::viewProjectionMatrix[6] +
                   pos.z * Globals::viewProjectionMatrix[10] + Globals::viewProjectionMatrix[14];
    clipCoords.w = pos.x * Globals::viewProjectionMatrix[3] + pos.y * Globals::viewProjectionMatrix[7] +
                   pos.z * Globals::viewProjectionMatrix[11] + Globals::viewProjectionMatrix[15];

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
    auto renderer = *reinterpret_cast<uint64_t *>(RVA(Offsets::Game::Renderer));
    return *reinterpret_cast<int *>(renderer + Offsets::Renderer::Height);
}

int Engine::WindowWidth() const {
    auto renderer = *reinterpret_cast<uint64_t *>(RVA(Offsets::Game::Renderer));
    return *reinterpret_cast<int *>(renderer + Offsets::Renderer::Width);
}

void Engine::Update() {
    memcpy(&Globals::viewMatrix, (void *) RVA(Offsets::Game::ViewProjMatrices), 16 * sizeof(float));
    memcpy(&Globals::projectionMatrix, (void *) RVA(Offsets::Game::ViewProjMatrices + (16 * sizeof(float))),
           16 * sizeof(float));
    MultiplySquareMatrices(Globals::viewProjectionMatrix, Globals::viewMatrix, Globals::projectionMatrix);

    ProcessSpells();//

}

HudInstance *Engine::GetHudInstance() {
    return *reinterpret_cast<HudInstance **>(RVA(Offsets::Game::HudInstance));
}

float Engine::GetProcessorTime() {
    return static_cast<float>(LI_FN(GetTickCount).get()());
}

DWORD __cdecl Engine::CollisionFlag(float* a1) {
    return 0;
}

bool Engine::IsNotWall(Vector3 pos) {
   return true;

}

void Engine::ProcessSpells() {

    auto localPlayer = locator->GetObjectManager()->GetLocalPlayer();

    for (auto &caster: locator->GetObjectManager()->GetHeroList()) {

        //if (caster->IsLocalPlayer() || caster->IsAllyTo<Hero*>(localPlayer)) continue; // catching only enemy spells.
        auto activeSpellCast = caster->GetSpellCast();


        if (!Utils::IsValid(activeSpellCast)) continue;
        if (activeSpellCast->spellSlot == -1) {
            Event::OnAutoAttack eventArgs{};
            eventArgs.caster = caster;
            eventArgs.destIndex = 0; // TODO:: ADD DESTINATION INDEX
            locator->GetEventManager()->Publish<Event::OnAutoAttack>(eventArgs);
            return;

        } else if (activeSpellCast->spellSlot >= 0 && activeSpellCast->spellSlot <= 3) {
            Spell spell = Spell();
            spell.spellSlot = activeSpellCast->spellSlot;
            spell.startPos = activeSpellCast->startPos;
            spell.name = activeSpellCast->GetName();
            spell.endPos = activeSpellCast->endPos;
            spell.startTime = activeSpellCast->startTime;
            spell.endTime = activeSpellCast->endTime;
            spell.castTime = activeSpellCast->castTime;
            spell.caster = caster;
            spell.destIndex = 0; // TODO:: ADD DESTINATION INDEX
            spell.spellInfo = nullptr;


            auto spellInfo = locator->GetGameData()->GetSpellInfoByName(spell.name);
            if (Utils::IsValid(spellInfo)) {
                spell.spellInfo = spellInfo;
            }

            Event::OnSpellCast eventArgs{};
            eventArgs.caster = caster;
            eventArgs.spell = spell;

            locator->GetEventManager()->Publish<Event::OnSpellCast>(eventArgs);
            return;

        } else if (activeSpellCast->spellSlot == 13) {
            Event::OnRecall eventArgs{};
            eventArgs.caster = caster;
            eventArgs.startTime = activeSpellCast->startTime;
            locator->GetEventManager()->Publish<Event::OnRecall>(eventArgs);
        }


    }

}

float Engine::GetGameTick() {
    return *reinterpret_cast<float *>(RVA(Offsets::Game::GameTime)) * 1000;
}

__int16 Engine::flag(int a1, int a2, unsigned __int16 a3) {
    __int64 world; // r11
    int v5; // er9
    int v6; // er10
    int v7; // eax
    __int16 *v8; // rax
    __int64 v9; // r8
    __int16 *v10; // rdx
    __int16 *v11; // rax
    __int16 v12; // cx
    unsigned __int16 v13; // cx

    world = *(__int64 *)(RVA(0x20d5f28) + 8);
    v5 = *(DWORD *)(world + 0x680);              // 295
    v6 = v5 - 1;                                  // 295 - 1
    if ( a1 <= v5 - 1 )                           // if X <= 294
    {
        v6 = a1;                                    // v6 = X
        if ( a1 < 0 )                               // if X < 0
            v6 = 0;                                   // v6 = 0
    }
    v7 = *(DWORD *)(world + 0x684) - 1;          // v7 = 296 - 1
    if ( a2 <= v7 )                               // if Z <= 295
    {
        v7 = a2;                                    // v7 = Z
        if ( a2 < 0 )                               // if Z < 0
            v7 = 0;                                   // v7 = 0
        //
    }                                             // v5 = 295
    // v6 = 294
    // v7 = 295
    v8 = (__int16 *)(*(__int64 *)(world + 0xE8) + 0x10i64 * (v6 + v5 * v7));// v8 = 48 + 16 * (294 + 295 * 295) (=1397152) BYTE
    if ( !v8 )
        return 0;
    v9 = *(__int64 *)v8;
    v10 = v8 + 4;
    v11 = (__int16 *)(*(__int64 *)v8 + 6i64);
    if ( v9 )
        v12 = *v11;
    else
        v12 = *v10;
    v13 = v12 & 0xC00;
    if ( v13 )
        return (a3 & v13) == v13;
    if ( !v9 )
        v11 = v10;
    return (*(BYTE *)v11 & 2) == 0;
}

Vector2 Engine::WorldToMinimap(const Vector3& pos) {
    auto minimapObject = *reinterpret_cast<__int64*>(RVA(Offsets::MiniMap::MiniMapObject));
    auto minimapHud = *reinterpret_cast<__int64*>(minimapObject + Offsets::MiniMap::MiniMapHud);
    Vector2 minimapSize = *reinterpret_cast<Vector2*>(minimapHud + Offsets::MiniMap::MiniMapHudSize);
    Vector2 minimapPos = *reinterpret_cast<Vector2*>(minimapHud + Offsets::MiniMap::MiniMapHudPos);

    Vector2 res = {pos.x / 15000.f, pos.z / 15000.f};

    res.x = minimapPos.x + res.x * minimapSize.x;
    res.y = minimapPos.y + minimapSize.y - (res.y * minimapSize.y);
    return res;
}


