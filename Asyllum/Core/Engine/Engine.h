//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_ENGINE_H
#define ASYLLUM_ENGINE_H


#include "../../Math/Vector.h"
#include "../HudInstance/HudInstance.h"

class Engine {
public:
    void Update();
    float GameTime() const;
    int WindowWidth() const;
    int WindowHeight() const;
    HudInstance* GetHudInstance();
    Vector2 WorldToScreen(const Vector3& pos);
};


#endif //ASYLLUM_ENGINE_H
