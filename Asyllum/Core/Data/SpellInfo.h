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
    std::string name;
    std::string parent;
    std::string icon;
    float castTime;
    float castRange;
    float castRadius;
    float castConeAngle;
    float castConeDistance;
    float width;
    float height;
    float speed;
    float travelTime;
    float delay;
    bool projectDestination;

};

#endif //ASYLLUM_SPELLINFO_H
