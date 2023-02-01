//
// Created by XaDanX on 12/1/2022.
//

#include "Hero.h"
#include "../../Locator/Locator.h"

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

    float delta = (float)locator->GetEngine()->WindowHeight() * 0.00083333335f * (height * this->scale);
    delta = static_cast<float>(delta) / static_cast<float>(zoomPercent);
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

BuffManager *Hero::GetBuffManager() {
    return reinterpret_cast<BuffManager*>((DWORD)this + Offsets::GameObject::BuffManager);
}


float Hero::GetTotalAttackSpeed() {
    auto unitInfo = this->GetUnitInfo();
    float attackSpeed = static_cast<float>((static_cast<float>(this->attackSpeedMultiplier) - 1.0) * unitInfo->attackSpeedRatio + unitInfo->baseAttackSpeed);
    if (attackSpeed <= 2.5) {
        return attackSpeed;
    }
    if (IsLethalTempoActive()) {
        return attackSpeed;
    }
    return 2.5;
}

bool Hero::IsLethalTempoActive() {
    for (auto buff : this->GetBuffManager()->GetBuffList()) {
        std::string buffName(buff->scriptBaseBuff->name);
        if (buffName.contains(XorStr("assets/perks/styles/precision/lethaltempo/lethaltempo.lua").c_str())) continue;
        if (buff->stacks != 6) continue;
        return true;
    }
    return false;
}

SpellCast *Hero::GetSpellCast() {
    if (!Utils::IsValid((void*)*reinterpret_cast<int*>((DWORD)this + Offsets::GameObject::SpellCast))) {
        return nullptr;
    }
    return reinterpret_cast<SpellCast*>(*reinterpret_cast<int*>((DWORD)this + Offsets::GameObject::SpellCast));
}
