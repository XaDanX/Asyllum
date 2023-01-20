//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_SPELLINFO_H
#define ASYLLUM_SPELLINFO_H
#include <map>
#include <string>
#include <bitset>
#include <array>
class SpellInfo {
public:
    std::string name = "";
    std::string parent = "";
    std::string icon = "";
    float castTime = 0;
    float castRange = 0;
    float castRadius = 0;
    float castConeAngle = 0;
    float castConeDistance = 0;
    float width = 0;
    float height = 0;
    float speed = 0;
    float travelTime = 0;
    float delay = 0;
    bool projectDestination = false;

};

#endif //ASYLLUM_SPELLINFO_H
