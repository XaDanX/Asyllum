//
// Created by XaDanX on 12/1/2022.
//

#include "Locator.h"

HookingService* Locator::GetHookingService() {
    if (!hookingService) {
        hookingService = std::make_unique<HookingService>();
    }
   return hookingService.get();
}


Asyllum *Locator::GetAsyllumInstance() {
    if (!asyllum) {
        asyllum = std::make_unique<Asyllum>();
    }
    return asyllum.get();
}

Engine* Locator::GetEngine() {
    if (!engine) {
        engine = std::make_unique<Engine>();
    }
    return engine.get();
}

ObjectManager *Locator::GetObjectManager() {
    if (!objectManager) {
        objectManager = std::make_unique<ObjectManager>();
    }
    return objectManager.get();
}

GameData *Locator::GetGameData() {
    if (!gameData) {
        gameData = std::make_unique<GameData>();
    }
    return gameData.get();
}

ModuleManager *Locator::GetModuleManager() {
    if (!moduleManager) {
        moduleManager = std::make_unique<ModuleManager>();
    }
    return moduleManager.get();
}
