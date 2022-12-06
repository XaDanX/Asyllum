//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_HERO_H
#define ASYLLUM_HERO_H


#include "../ObjectBase.h"
#include "AiManager/AiManager.h"
#include "SpellBook/SpellSlot.h"

class Hero : public ObjectBase {
private:
    UnitInfo* unitInfo;
public:
    Vector2 GetHealthBarPosition();
    UnitInfo* GetUnitInfo();
    AiManager* GetAiManager();

    SpellSlot* GetSpellSlotById(int id);

};


#endif //ASYLLUM_HERO_H
