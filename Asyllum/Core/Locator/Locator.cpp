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

Console *Locator::GetConsole() {
    if (!console) {
        console = std::make_unique<Console>();
    }
    return console.get();
}

TextureManager *Locator::GetTextureManager() {
    if (!textureManager) {
        textureManager = std::make_unique<TextureManager>();
    }
    return textureManager.get();
}

Renderer *Locator::GetRenderer() {
    if (!renderer) {
        renderer = std::make_unique<Renderer>();
    }
    return renderer.get();
}

EventManager *Locator::GetEventManager() {
    if (!eventManager) {
        eventManager = std::make_unique<EventManager>();
    }
    return eventManager.get();
}

Menu *Locator::GetMenu() {
    if (!menu) {
        menu = std::make_unique<Menu>();
    }
    return menu.get();
}

