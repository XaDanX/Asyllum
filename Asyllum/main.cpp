#include <Windows.h>
#include "kiero/kiero.h"
#include "Core/Hooking/HookingService.h"
#include "Core/Locator/Locator.h"
#include "Globals/Globals.h"
#include "Protection/XorStr.h"
#include "Protection/PebUnlink.h"
#include "Protection/LazyImporter.h"
#include <process.h>
#include <chrono>

HMODULE thread;
using namespace std::chrono_literals;

__declspec(safebuffers) int __stdcall Main(LPVOID lpReserved) {
    Globals::baseAddress = reinterpret_cast<int>(GetModuleHandle(NULL));
    bool status = locator->GetAsyllumInstance()->Initialize();
    locator->GetAsyllumInstance()->initialized = status;

    std::this_thread::sleep_for(std::chrono::microseconds(1000ms));


    while (locator->GetHookingService()->isHooked) {
        locator->GetAsyllumInstance()->OnThreadTick();
        std::this_thread::sleep_for(std::chrono::microseconds(1ms));
    }
    std::this_thread::sleep_for(std::chrono::microseconds(1000ms));
    LI_FN(FreeLibrary).get()(thread);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            LI_FN(DisableThreadLibraryCalls).get()(hMod);
            thread = hMod;
            _beginthreadex(nullptr, 0, reinterpret_cast<_beginthreadex_proc_type>(Main), hMod, 0, nullptr);

            break;
        case DLL_PROCESS_DETACH:
            kiero::shutdown();
            break;
    }
    return TRUE;
}
