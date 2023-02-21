//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_HERO_H
#define ASYLLUM_HERO_H


#include "../ObjectBase.h"
#include "AiManager/AiManager.h"
#include "SpellBook/SpellSlot.h"
#include "BuffManager/BuffManager.h"
#include "SpellCast/SpellCast.h"

class Hero : public ObjectBase { // TODO: Active spell / IsCasting flag
public:
    Vector2 GetHealthBarPosition();
    UnitInfo* GetUnitInfo();
    BuffManager* GetBuffManager();

    SpellSlot* GetSpellSlotById(int id);

    SpellCast* GetSpellCast();

    float GetTotalAttackSpeed();

    bool IsLethalTempoActive();

    void ForceVisibility();

};


#endif //ASYLLUM_HERO_H
