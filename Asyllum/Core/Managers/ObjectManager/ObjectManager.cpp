//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectManager.h"
#include "Template.h"

std::vector<Hero*> ObjectManager::GetHeroList() {
    return Template::ReadTemplate<Hero*>(RVA(Offsets::Templates::HeroTemplate));
}

Hero *ObjectManager::GetLocalPlayer() {
    return *reinterpret_cast<Hero**>(RVA(Offsets::Game::LocalPlayer));
}

std::vector<Minion *> ObjectManager::GetMinionList() {
    return Template::ReadTemplate<Minion*>(RVA(Offsets::Templates::MinionTemplate));
}

std::vector<Turret *> ObjectManager::GetTurretList() {
    return Template::ReadTemplate<Turret*>(RVA(Offsets::Templates::TurretTemplate));
}
