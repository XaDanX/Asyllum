//
// Created by XaDanX on 12/28/2022.
//

#include "FakeMouse.h"
#include "../../kiero/minhook/include/MinHook.h"
#include "../Locator/Locator.h"

bool FakeMouse::Enabled = false;
GetCursorPosFunc FakeMouse::TrueGetCursorPos = GetCursorPos;
int FakeMouse::xPos = 0;
int FakeMouse::yPos = 0;

void FakeMouse::Init() {

    if (MH_CreateHook(GetCursorPos, &FakeMouse::HookedGetCursorPos, reinterpret_cast<void**>(&TrueGetCursorPos)) != MH_OK) {
    }

    if (MH_EnableHook(GetCursorPos) != MH_OK) {
    }
}

BOOL __stdcall FakeMouse::HookedGetCursorPos(LPPOINT lpPoint) {
    if (lpPoint != NULL && FakeMouse::Enabled) {
        __try {
                return SpoofedGetCursorPos(lpPoint);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return TRUE;
        }
    }
    else
        return TrueGetCursorPos(lpPoint);
}

BOOL __stdcall FakeMouse::SpoofedGetCursorPos(LPPOINT lpPoint) {
    lpPoint->x = xPos;
    lpPoint->y = yPos;
    return TRUE;
}

void FakeMouse::SetSpoofedCursorPos(int x, int y) {
    xPos = x;
    yPos = y;
    FakeMouse::xPos = x;
    FakeMouse::yPos = y;
}

void FakeMouse::UnSpoof()  {
    FakeMouse::Enabled = false;
}

void FakeMouse::Spoof(){
    FakeMouse::Enabled = true;
}
