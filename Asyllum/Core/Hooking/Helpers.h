//
// Created by XaDanX on 12/1/2022.
//
#include <Windows.h>

#ifndef ASYLLUM_HELPERS_H
#define ASYLLUM_HELPERS_H

extern HWND pWindow = NULL;

namespace HookingHelper {
    BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
        DWORD wndProcId;
        GetWindowThreadProcessId(handle, &wndProcId);

        if (GetCurrentProcessId() != wndProcId)
            return TRUE;

        pWindow = handle;
        return FALSE;
    }

    HWND GetProcessWindow() {
        pWindow = NULL;
        EnumWindows(EnumWindowsCallback, NULL);
        return pWindow;
    }
}
#endif //ASYLLUM_HELPERS_H
