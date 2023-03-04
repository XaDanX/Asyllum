//
// Created by XaDanX on 12/1/2022.
//

#include "Hero.h"
#include "../../Locator/Locator.h"

#include "../../../Utils/Utils.h"


Vector2 Hero::GetHealthBarPosition() {
    auto unit = GetUnitInfo();
    auto height = 100.f;
    if (Utils::IsValid(unit)) {
        height = unit->healthBarHeight;
    }
    auto pos = position.clone();

    auto sizeMultiplier = this->scale;

    auto maxZoom = 2250.0;
    auto currentZoom = locator->GetEngine()->GetHudInstance()->zoomInstance->visibleZoom;
    auto delta = maxZoom / currentZoom;

    pos.y += height * sizeMultiplier;

    auto ret = locator->GetEngine()->WorldToScreen(pos);
    ret.y -= ((locator->GetEngine()->WindowHeight() * 0.00083333335f * delta) * height * sizeMultiplier);
    return ret;



}

UnitInfo *Hero::GetUnitInfo() {
    auto fixedName = StringUtils::ToLower(name);
    return locator->GetGameData()->GetUnitInfoByName(fixedName);
}


SpellSlot *Hero::GetSpellSlotById(int id) {
    return reinterpret_cast<SpellSlot *>(*reinterpret_cast<int *>((DWORD) this + Offsets::GameObject::SpellBook +
                                                                  (0x4 * id)));
}

BuffManager *Hero::GetBuffManager() {
    return reinterpret_cast<BuffManager *>((DWORD) this + Offsets::GameObject::BuffManager);
}


float Hero::GetTotalAttackSpeed() {
    auto unitInfo = this->GetUnitInfo();
    float attackSpeed = static_cast<float>(
            (static_cast<float>(this->attackSpeedMultiplier) - 1.0) * unitInfo->attackSpeedRatio +
            unitInfo->baseAttackSpeed);
    if (attackSpeed <= 2.5) {
        return attackSpeed;
    }
    if (IsLethalTempoActive()) {
        return attackSpeed;
    }
    return 2.5;
}

bool Hero::IsLethalTempoActive() {
    for (auto buff: this->GetBuffManager()->GetBuffList()) {
        std::string buffName(buff->scriptBaseBuff->name);
        if (buffName.contains(XorStr("assets/perks/styles/precision/lethaltempo/lethaltempo.lua").c_str())) continue;
        if (buff->stacks != 6) continue;
        return true;
    }
    return false;
}

SpellCast *Hero::GetSpellCast() {
    if (!Utils::IsValid((void *) *reinterpret_cast<int *>((DWORD) this + Offsets::GameObject::SpellCast))) {
        return nullptr;
    }
    return reinterpret_cast<SpellCast *>(*reinterpret_cast<int *>((DWORD) this + Offsets::GameObject::SpellCast));
}

void Hero::ForceVisibility() {
    *reinterpret_cast<int *>((DWORD) this + Offsets::GameObject::Visibility) = 8;
}
