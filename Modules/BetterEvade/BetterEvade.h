//
// Created by XaDanX on 3/16/2023.
//

#ifndef ASYLLUM_BETTEREVADE_H
#define ASYLLUM_BETTEREVADE_H


#include "../../Asyllum/Core/Managers/ModuleManager/Module.h"
#include "../../Asyllum/imgui/imgui.h"
#include "../Evade/SpellDetector.h"
#include "../../Asyllum/Core/Locator/Locator.h"


class BetterEvade : public Module {
public:
    SpellDetector* spellDetector;
public:
    BetterEvade(std::string _name, ModuleType _type, HashName _champion) : Module(_name, _type, _champion) {
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

public:

    Vector3 heroPos = {0, 0, 0};
    Vector3 evadePos = {0, 0, 0};
    float evadeTime = 0;
    bool evading = false;

    bool IsDangerous(Vector3 pos);

    Vector3 GetMovePath();
    std::vector<Vector3> FindIntersections(Geometry::Polygon poly, Vector3 p1, Vector3 p2);

    void StartEvading();

    Vector3 PrependVector(Vector3 pos1, Vector3 pos2, float dist);

    Vector3 GetBestEvadePos();


public: // config
    bool enabled = true;
    float extraEvadeLength = 15;
    bool continueLastMovement = true;
};



#endif //ASYLLUM_BETTEREVADE_H
