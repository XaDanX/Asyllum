//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_HELPERS_H
#define ASYLLUM_HELPERS_H

#include <Windows.h>
#include <TlHelp32.h>

namespace Helpers {
    MODULEENTRY32 GetModule(const char *modName, DWORD proc_id) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!strcmp(modEntry.szModule, modName)) {
                        CloseHandle(hSnap);
                        return modEntry;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        MODULEENTRY32 module = {static_cast<DWORD>(-1)};
        return module;
    }
}
#endif //ASYLLUM_HELPERS_H
