//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_OBJECTMANAGER_H
#define ASYLLUM_OBJECTMANAGER_H


#include <vector>
#include "../../Objects/Hero/Hero.h"
#include "../../Objects/Minion/Minion.h"
#include "../../Objects/Turret/Turret.h"

class ObjectManager {
public:
    std::vector<Hero*> GetHeroList();
    std::vector<Minion*> GetMinionList();
    std::vector<Turret*> GetTurretList();
    Hero* GetLocalPlayer();
    //TODO: Missile list
};


#endif //ASYLLUM_OBJECTMANAGER_H
