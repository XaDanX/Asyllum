//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_LOCATOR_H
#define ASYLLUM_LOCATOR_H


#include <memory>
#include "../Hooking/HookingService.h"
#include "../Asyllum.h"
#include "../Engine/Engine.h"
#include "../Managers/ObjectManager/ObjectManager.h"
#include "../Data/GameData.h"
#include "../Managers/ModuleManager/ModuleManager.h"
#include "../Renderer/Console/Console.h"
#include "../Renderer/TextureManager/TextureManager.h"
#include "../Renderer/Renderer.h"
#include "../Controller/Controller.h"
#include "../Managers/EventManager/EventManager.h"
#include "../../Menu/Menu.h"

class Locator {
public:
    HookingService *GetHookingService();

    Asyllum *GetAsyllumInstance();

    Engine *GetEngine();

    ObjectManager *GetObjectManager();

    GameData *GetGameData();

    ModuleManager *GetModuleManager();

    Console *GetConsole();

    TextureManager *GetTextureManager();

    Renderer *GetRenderer();

    EventManager *GetEventManager();

    Menu *GetMenu();

private:
    std::unique_ptr<HookingService> hookingService;
    std::unique_ptr<Asyllum> asyllum;
    std::unique_ptr<Engine> engine;
    std::unique_ptr<ObjectManager> objectManager;
    std::unique_ptr<GameData> gameData;
    std::unique_ptr<ModuleManager> moduleManager;
    std::unique_ptr<Console> console;
    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<Menu> menu;
};

inline extern std::unique_ptr<Locator> locator = std::make_unique<Locator>();


#endif //ASYLLUM_LOCATOR_H
