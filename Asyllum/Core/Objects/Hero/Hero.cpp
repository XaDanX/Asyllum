//
// Created by XaDanX on 12/1/2022.
//

#include "Hero.h"
#include "../../Locator/Locator.h"
#include "../../Helpers/StringUtils.h"


Vector2 Hero::GetHealthBarPosition() {

    Vector3 point = position.clone();
    point.y += GetUnitInfo()->healthBarHeight;

    Vector2 out = locator->GetEngine()->WorldToScreen(point);
    out.y -= ((float)locator->GetEngine()->WindowHeight() * 0.00083333335f * GetUnitInfo()->healthBarHeight);
    out.x -= 70.0f;
    return out;

}

UnitInfo *Hero::GetUnitInfo() {
    if (!unitInfo) {
        auto fixedName = StringUtils::ToLower(name);
        unitInfo = locator->GetGameData()->GetUnitInfoByName(fixedName);
    }
    return unitInfo;
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
