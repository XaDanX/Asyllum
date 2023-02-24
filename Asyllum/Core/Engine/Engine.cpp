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
    ProcessSpells();
}

HudInstance* Engine::GetHudInstance() {
    return *reinterpret_cast<HudInstance**>(RVA(Offsets::Game::HudInstance));
}

float Engine::GetProcessorTime() {
    return static_cast<float>(LI_FN(GetTickCount).get()());
}

DWORD __cdecl Engine::CollisionFlag(float a1, float a2, float a3) {
    auto collisionFlag = *reinterpret_cast<DWORD*>(RVA(Offsets::Functions::IsNotWall));

    auto world = *reinterpret_cast<DWORD*>(collisionFlag + 0x4);
    auto fOffsetX = *reinterpret_cast<float*>(world + 0x64);
    auto fOffsetZ = *reinterpret_cast<float*>(world + 0x6C);
    auto fCellScale = *reinterpret_cast<float*>(world + 0x5AC);

    int x = (int)(((a1 - fOffsetX) * fCellScale));
    int y = (int)(((a3 - fOffsetZ) * fCellScale));

    auto target = *reinterpret_cast<unsigned int*>(world + 0x80);
    unsigned int target2 = target + 0x8 * (*reinterpret_cast<unsigned int*>(world + 0x5A0) * y + x);
    auto target3 = *reinterpret_cast<unsigned int*>(target2);
    unsigned short flag;

    if (target3 != 0) {
        flag = *reinterpret_cast<unsigned short*>(target3 + 0x6);
    }
    else {
        flag = *reinterpret_cast<unsigned short*>(target2 + 0x4);
    }

    return flag;
}

bool Engine::IsNotWall(Vector3 pos) {
    return !(CollisionFlag(pos.x, pos.y, pos.z) & 2);
}

void Engine::ProcessSpells() {

    auto localPlayer = locator->GetObjectManager()->GetLocalPlayer();

    for (auto& caster : locator->GetObjectManager()->GetHeroList()) {

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
