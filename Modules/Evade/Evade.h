//
// Created by XaDanX on 1/30/2023.
//

#ifndef ASYLLUM_EVADE_H
#define ASYLLUM_EVADE_H
#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/Core/Data/Spell/Spell.h"
#include "EvadableSpell.h"

class Evade : public Module {
public:
    static std::map<int, Spell> activeSpells;

    static std::map<HashName, Champion> championList;

    static float evadeTimeEnd;
    Vector3 evadePoint = {0, 0, 0};
    DangerLevel currentDangerLevel;

    float extraEvadeLength = 5;

public:
    void OnTick();

    void OnLoad();

    void OnGui();

    std::string ModuleType() {return XorStr("utility"); };

    std::string GetName() {return XorStr("Evade");};

    void ProcessActiveSpells();
    void InitEvadableSpells();
    Vector3 GetLinearEvadePoint(Spell *spell);

    void TryEvadeSpell(Spell *spell);

    std::vector<Spell> GetDangerousSpells();
    std::unique_ptr<Spell> GetEvadableSpell();

    static EvadeSpell* FindSpell(HashName hashName, Slot spellSlotId) {
        auto championIt = championList.find(hashName);
        if (championIt == championList.end()) {
            return nullptr;
        }

        Champion& champion = championIt->second;
        auto spellIt = champion.spells.find(spellSlotId);
        if (spellIt == champion.spells.end()) {
            return nullptr;
        }

        return &spellIt->second;
    }

};



#endif //ASYLLUM_EVADE_H
