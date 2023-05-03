//
// Created by XaDanX on 2/25/2023.
//

#ifndef ASYLLUM_EVADE_H
#define ASYLLUM_EVADE_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/imgui/imgui.h"
#include "SpellDetector.h"
#include "../../Asyllum/Core/Locator/Locator.h"



struct PathResult {
    bool Safe = true;
    int UnsafSegment = 0;
    int UnsafePoint = 0;
    Vector3 LastSafePoint;
};

class Evade : public Module {
public:
    SpellDetector* spellDetector;
public:
    Evade(std::string _name, ModuleType _type, HashName _champion) : Module(_name, _type, _champion) {
        this->name = std::move(_name);
        this->type = _type;
        this->champion = _champion;
    }

    void OnTick();

    void OnLoad() {
        spellDetector = new SpellDetector;
        spellDetector->Initialize();
    }

    void OnGui();

    void OnConfigLoad() {};

    void OnConfigSave() {};

    static float evadeEndTime;
    static Vector3 evadePoint;
    static DangerLevel currentDangerLevel;

    Vector3 lastMovement = {0, 0, 0};
    static bool isEvading;

public:
    Vector3 GetLinearEvadePoint(DetectedSpell* spell, Vector3 pos);
    std::unique_ptr<DetectedSpell> GetSpellToEvade();

    Vector3 GetMovePath();

    bool IsDangerous(Vector3 pos);
    void TryEvadeSpell(DetectedSpell *spell);

    PathResult IsPathSafe();

public: // config
    bool enabled = true;
    float extraEvadeLength = 20;
    bool continueLastMovement = true;

    bool extendEvadeMove = true;
    float extendEvadeMoveBy = 100.0;
};



#endif //ASYLLUM_EVADE_H
