//
// Created by XaDanX on 12/28/2022.
//

#include "FakeMouse.h"
#include "../../kiero/minhook/include/MinHook.h"
#include "../Locator/Locator.h"

bool FakeMouse::Enabled = false;
GetCursorPosFunc FakeMouse::TrueGetCursorPos = GetCursorPos;
std::function<Vector2()>  FakeMouse::FakePositionGetter;

void FakeMouse::Init() {

    if (MH_CreateHook(GetCursorPos, &FakeMouse::HookedGetCursorPos, reinterpret_cast<void **>(&TrueGetCursorPos)) !=
        MH_OK) {
    }

    if (MH_EnableHook(GetCursorPos) != MH_OK) {
    }
}

BOOL __stdcall FakeMouse::HookedGetCursorPos(LPPOINT lpPoint) {
    if (lpPoint != NULL && FakeMouse::Enabled) {
        __try{
                return SpoofedGetCursorPos(lpPoint);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return TRUE;
        }
    } else
        return TrueGetCursorPos(lpPoint);
}

BOOL __stdcall FakeMouse::SpoofedGetCursorPos(LPPOINT lpPoint) {
    Vector2 v = FakeMouse::FakePositionGetter();
    lpPoint->x = (LONG) v.x;
    lpPoint->y = (LONG) v.y;
    return TRUE;
}

void FakeMouse::UnSpoof() {
    FakeMouse::Enabled = false;
}

void FakeMouse::Spoof() {
    FakeMouse::Enabled = true;
}
