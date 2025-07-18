//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_FAKEMOUSE_H
#define ASYLLUM_FAKEMOUSE_H

#include <Windows.h>
#include <functional>
#include "../../Math/Vector.h"

typedef BOOL(WINAPI *GetCursorPosFunc)(LPPOINT lpPoint);

class FakeMouse {

public:
    static void Init();

    static void UnHook();

    static bool Enabled;

    static std::function<Vector2()> FakePositionGetter;

    static void Spoof();

    static void UnSpoof();

    static void SetSpoofedCursorPos(int x, int y);

private:
    static GetCursorPosFunc TrueGetCursorPos;

    static BOOL __stdcall    HookedGetCursorPos(LPPOINT lpPoint);

    static BOOL __stdcall    SpoofedGetCursorPos(LPPOINT lpPoint);
};

#endif //ASYLLUM_FAKEMOUSE_H
