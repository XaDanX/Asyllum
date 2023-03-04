//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_GAMEDATA_H
#define ASYLLUM_GAMEDATA_H

#include <string>
#include "UnitInfo.h"
#include "SpellInfo.h"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

class GameData {
public:
    void Load(std::string &path);

    UnitInfo *GetUnitInfoByName(std::string &name);

    SpellInfo *GetSpellInfoByName(std::string &name);

public:
    std::map<std::string, UnitInfo *> Units{};
    std::map<std::string, SpellInfo *> Spells{};

private:
    void LoadUnitData(std::string &path);

    void LoadSpellData(std::string &path);

};


#endif //ASYLLUM_GAMEDATA_H
