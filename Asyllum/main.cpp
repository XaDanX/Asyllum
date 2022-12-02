#include <Windows.h>
#include "kiero/kiero.h"
#include "Core/Hooking/HookingService.h"
#include "Core/Locator/Locator.h"
#include "Globals/Globals.h"
#include "Protection/XorStr.h"
#include <process.h>
HMODULE thread;

namespace {
    std::string deployablePath(XorStr("C:\\Deployable").c_str());
}

__declspec(safebuffers) int __stdcall Main(LPVOID lpReserved) {
    Globals::baseAddress = reinterpret_cast<int>(GetModuleHandle(NULL));
    locator->GetGameData()->Load(deployablePath);
    locator->GetHookingService()->Initialize();
    locator->GetAsyllumInstance()->Initialize();
    locator->GetModuleManager()->Initialize();

    while (locator->GetHookingService()->isHooked) {
        locator->GetAsyllumInstance()->OnThreadTick();
        Sleep(1);
    }
    Sleep(1000);
    FreeLibrary(thread);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
        thread = hMod;
        _beginthreadex(nullptr, 0, reinterpret_cast<_beginthreadex_proc_type>(Main), hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
