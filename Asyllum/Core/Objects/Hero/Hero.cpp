//
// Created by XaDanX on 12/1/2022.
//

#include "Hero.h"
#include "../../Locator/Locator.h"
#include "../../Helpers/StringUtils.h"
#include "../../../Utils/Utils.h"


Vector2 Hero::GetHealthBarPosition() {

    Vector3 point = position.clone();

    auto unit = GetUnitInfo();
    auto height = 100.f;
    if (Utils::IsValid(unit)) {
        height = unit->healthBarHeight;
    }

    point.y += height;

    auto zoomMultiplier = 2250.0 / 100;
    auto zoomPercent = (locator->GetEngine()->GetHudInstance()->zoomInstance->visibleZoom / zoomMultiplier) / 100;

    Vector2 out = locator->GetEngine()->WorldToScreen(point);

    auto delta = (float)locator->GetEngine()->WindowHeight() * 0.00083333335f * (height * this->scale);
    delta = (float)delta / zoomPercent;
    out.y -= delta;
    out.x -= 70.0f;
    return out;

}

UnitInfo *Hero::GetUnitInfo() {
    auto fixedName = StringUtils::ToLower(name);
    return locator->GetGameData()->GetUnitInfoByName(fixedName);
}

AiManager *Hero::GetAiManager() {
    int v1 = *reinterpret_cast<__int8*>(reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager);
    int v2 = reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager - 8;
    int v3 = *reinterpret_cast<int*>(v2 + 4);
    int v4 = *reinterpret_cast<int*>((v2 + (4 * v1 + 12)));
    v4 = v4 ^ (~v3);
    return reinterpret_cast<AiManager*>(*reinterpret_cast<int*>(v4 + 8));
}

SpellSlot *Hero::GetSpellSlotById(int id) {
    return reinterpret_cast<SpellSlot*>(*reinterpret_cast<int*>((DWORD)this + Offsets::GameObject::SpellBook + (0x4 * id)));
}
