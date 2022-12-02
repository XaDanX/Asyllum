//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_OBJECTMANAGER_H
#define ASYLLUM_OBJECTMANAGER_H


#include <vector>
#include "../../Objects/Hero/Hero.h"

class ObjectManager {
public:
    std::vector<Hero*> GetHeroList();
    Hero* GetLocalPlayer();
};


#endif //ASYLLUM_OBJECTMANAGER_H
