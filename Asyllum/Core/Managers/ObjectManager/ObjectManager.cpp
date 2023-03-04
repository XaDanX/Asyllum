//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectManager.h"
#include "Template.h"
#include "../../../Utils/Utils.h"
#include "../../Locator/Locator.h"
#include <queue>
#include <set>

std::vector<Hero *> ObjectManager::GetHeroList() {
    return Template::ReadTemplate<Hero *>(RVA(Offsets::Templates::HeroTemplate));
}

Hero *ObjectManager::GetLocalPlayer() {
    return *reinterpret_cast<Hero **>(RVA(Offsets::Game::LocalPlayer));
}

std::vector<Minion *> ObjectManager::GetMinionList() {
    return Template::ReadTemplate<Minion *>(RVA(Offsets::Templates::MinionTemplate));
}

std::vector<Turret *> ObjectManager::GetTurretList() {
    return Template::ReadTemplate<Turret *>(RVA(Offsets::Templates::TurretTemplate));
}

std::vector<Missile*> ObjectManager::GetMissileList() {
    std::vector<Missile*> result;

    auto missileTemplate = *reinterpret_cast<int*>(RVA(Offsets::Templates::MissileTemplate));

    auto rootNode = *reinterpret_cast<int*>(missileTemplate + 0x4);

    auto size = *reinterpret_cast<int*>(missileTemplate + 0x8);

    if (size <= 0)
        return result;

    std::set<int> checked;
    std::queue<int> toCheck;
    toCheck.push(rootNode);

    int reads = 0, child_node1, child_node2, child_node3;

    while (toCheck.size() > 0) {
        auto node = toCheck.front();
        toCheck.pop();

        if (checked.contains(node))
            continue;

        reads++;
        checked.insert(node);
        child_node1 = *reinterpret_cast<int*>(node);
        child_node2 = *reinterpret_cast<int*>(node + 0x4);
        child_node3 = *reinterpret_cast<int*>(node + 0x8);
        if (Utils::IsValid((void*)child_node1))
            toCheck.push(child_node1);
        if (Utils::IsValid((void*)child_node2))
            toCheck.push(child_node2);
        if (Utils::IsValid((void*)child_node3))
            toCheck.push(child_node3);


        /*if (!checked.contains(node)) {
            c.push_back(node);
        }*/

        if (checked.size() > size)
            break;

    }
    std::vector<int> c(checked.begin(), checked.end());
    for (auto i = 1; i < c.size(); i++) {
        auto current = c.at(i);
        if (!Utils::IsValid((void*)current))
            continue;
        auto missile = *reinterpret_cast<int*>(current + 0x14);
        if (!Utils::IsValid((void*)missile))
            continue;

        result.push_back(reinterpret_cast<Missile*>(missile));
    }

    return result;




}

Hero *ObjectManager::GetHeroByIndex(BYTE index) {

    for (auto& hero : GetHeroList()) {
        if (hero->index == index)
            return hero;
    }

    return nullptr;
}

