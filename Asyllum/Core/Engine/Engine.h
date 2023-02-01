//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_ENGINE_H
#define ASYLLUM_ENGINE_H


#include "../../Math/Vector.h"
#include "../HudInstance/HudInstance.h"
#include <Windows.h>

class Engine {
public:
    void Update();
    float GameTime() const;
    int WindowWidth() const;
    int WindowHeight() const;
    HudInstance* GetHudInstance();
    Vector2 WorldToScreen(const Vector3& pos);

    float GetProcessorTime();

    DWORD __cdecl CollisionFlag(float a1, float a2, float a3);
    bool IsNotWall(Vector3 pos);

    void ProcessSpells();

};


#endif //ASYLLUM_ENGINE_H
