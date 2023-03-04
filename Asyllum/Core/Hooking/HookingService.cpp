//
// Created by XaDanX on 12/1/2022.
//

#include "HookingService.h"
#include "DirectX.h"
#include "DirectInputHook.h"
#include "../../kiero/kiero.h"
#include "Helpers.h"
#include "../../kiero/minhook/include/MinHook.h"
#include "FakeMouse.h"


bool HookingService::Initialize() {
    bool attached = false;
    do {
        if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
            kiero::bind(16, (void **) &oReset, DirectX::hkReset);
            kiero::bind(42, (void **) &oEndScene, DirectX::hkEndScene);
            FakeMouse::Init();
            DirectInputHook::Hook();
            kiero::bind(17, (void **) &oPresent, DirectX::hkPresent);
            do {
                this->window = HookingHelper::GetProcessWindow();
            } while (window == NULL);
            oWndProc = (WNDPROC) SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR) DirectX::WndProc);
            attached = true;
        }
    } while (!attached);

    return TRUE;
}

bool HookingService::UnHook() {
    this->isHooked = false;
    return true;
}

