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
    std::vector<Missile*> ret;

    /*std::map<int, __int64>* objMap = (std::map<int, __int64>*)(*reinterpret_cast<__int64*>(*reinterpret_cast<__int64*>(RVA(Offsets::Templates::MissileTemplate)) + 0x8));

    for (auto t : *objMap) {
        auto missile = t.second;
        if (Utils::IsValid((void*)missile)) {
            ret.push_back(reinterpret_cast<Missile *>(missile));
        }
    }*/


    auto missileTemplate = *reinterpret_cast<uint64_t *>(RVA(Offsets::Templates::MissileTemplate));

    auto rootNode = *reinterpret_cast<uint64_t*>(missileTemplate + 0x8);

    auto size = *reinterpret_cast<int*>(missileTemplate + 0x10);

    std::set<uint64_t> checked;
    std::queue<uint64_t> toCheck;
    toCheck.push(rootNode);

    int reads = 0;
    uint64_t child_node1, child_node2, child_node3;

    while (toCheck.size() > 0) {
        auto node = toCheck.front();
        toCheck.pop();

        if (checked.contains(node))
            continue;

        reads++;
        checked.insert(node);
        child_node1 = *reinterpret_cast<uint64_t*>(node);
        child_node2 = *reinterpret_cast<uint64_t*>(node + 0x8);
        child_node3 = *reinterpret_cast<uint64_t*>(node + 0x10);
        if (Utils::IsValid((void*)child_node1))
            toCheck.push(child_node1);
        if (Utils::IsValid((void*)child_node2))
            toCheck.push(child_node2);
        if (Utils::IsValid((void*)child_node3))
            toCheck.push(child_node3);

        if (checked.size() > size)
            break;

    }
    std::vector<uint64_t> c(checked.begin(), checked.end());
    for (auto i = 1; i < c.size(); i++) {
        auto current = c.at(i);
        if (!Utils::IsValid((void*)current))
            continue;
        auto missile = *reinterpret_cast<uint64_t*>(current + 0x28);
        if (!Utils::IsValid((void*)missile))
            continue;

        ret.push_back(reinterpret_cast<Missile*>(missile));

    }

    return ret;
}

Hero *ObjectManager::GetHeroByIndex(BYTE index) {

    for (auto& hero : GetHeroList()) {
        if (hero->index == index)
            return hero;
    }

    return nullptr;
}

/***** READING FROM TREE (slow) ******
void ObjectManager::UpdateMissileList() {
    missileList.clear();

    auto missileTemplate = *reinterpret_cast<uint64_t *>(RVA(Offsets::Templates::MissileTemplate));

    auto rootNode = *reinterpret_cast<uint64_t*>(missileTemplate + 0x8);

    auto size = *reinterpret_cast<int*>(missileTemplate + 0x10);

    std::set<uint64_t> checked;
    std::queue<uint64_t> toCheck;
    toCheck.push(rootNode);

    int reads = 0;
    uint64_t child_node1, child_node2, child_node3;

    while (toCheck.size() > 0) {
        auto node = toCheck.front();
        toCheck.pop();

        if (checked.contains(node))
            continue;

        reads++;
        checked.insert(node);
        child_node1 = *reinterpret_cast<uint64_t*>(node);
        child_node2 = *reinterpret_cast<uint64_t*>(node + 0x8);
        child_node3 = *reinterpret_cast<uint64_t*>(node + 0x10);
        if (Utils::IsValid((void*)child_node1))
            toCheck.push(child_node1);
        if (Utils::IsValid((void*)child_node2))
            toCheck.push(child_node2);
        if (Utils::IsValid((void*)child_node3))
            toCheck.push(child_node3);

        if (checked.size() > size)
            break;

    }
    std::vector<uint64_t> c(checked.begin(), checked.end());
    for (auto i = 1; i < c.size(); i++) {
        auto current = c.at(i);
        if (!Utils::IsValid((void*)current))
            continue;
        auto missile = *reinterpret_cast<uint64_t*>(current + 0x28);
        if (!Utils::IsValid((void*)missile))
            continue;

        missileList.push_back(reinterpret_cast<Missile*>(missile));

    }
}*/



