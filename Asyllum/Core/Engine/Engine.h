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

    HudInstance *GetHudInstance();

    Vector2 WorldToScreen(const Vector3 &pos);
    Vector2 WorldToMinimap(const Vector3& pos);

    float GetProcessorTime();
    float GetGameTick();

    DWORD __cdecl CollisionFlag(float* a1);

    bool IsNotWall(Vector3 pos);

    void ProcessSpells();

    __int16 __fastcall flag(int a1, int a2, unsigned __int16 a3);


};


#endif //ASYLLUM_ENGINE_H
