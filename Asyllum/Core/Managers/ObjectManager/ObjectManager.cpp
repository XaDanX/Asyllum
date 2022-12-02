//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectManager.h"
#include "Template.h"

std::vector<Hero*> ObjectManager::GetHeroList() {
    return Template::ReadTemplate<Hero*>(RVA((unsigned int)Offsets::Templates::HeroTemplate));
}

Hero *ObjectManager::GetLocalPlayer() {
    return *reinterpret_cast<Hero**>(RVA((unsigned int)Offsets::Game::LocalPlayer));
}
