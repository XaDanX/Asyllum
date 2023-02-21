//
// Created by XaDanX on 2/2/2023.
//

#include "DirectInputHook.h"
#include <dinput.h>
#include "../../kiero/minhook/include/MinHook.h"
#include "../Locator/Locator.h"

typedef HRESULT(WINAPI* DirectInputGetDeviceData)(IDirectInputDevice8*, DWORD a, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
bool                                DirectInputHook::DisableGameKeys = false;
DirectInputGetDeviceData            DirectInputHook::OriginalDirectInputGetDeviceData;
std::set<DWORD>                     DirectInputHook::DisabledGameKeys;
std::map<DWORD, InputEventInfo>     DirectInputHook::AdditionalEvents;
DWORD                               DirectInputHook::SequenceNumber;

void DirectInputHook::Hook()
{
    HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
    IDirectInput8 *pDirectInput = NULL;

    if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&pDirectInput, NULL) != DI_OK) {
    }

    LPDIRECTINPUTDEVICE8  lpdiKeyboard;
    if (pDirectInput->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL) != DI_OK) {
        pDirectInput->Release();
        return;
    }

    void ** VTable = *reinterpret_cast<void***>(lpdiKeyboard);
    OriginalDirectInputGetDeviceData = (DirectInputGetDeviceData)(VTable[10]);

    if (MH_CreateHook((DirectInputGetDeviceData)(VTable[10]), &HookedDirectInputGetDeviceData, reinterpret_cast<void**>(&OriginalDirectInputGetDeviceData)) != MH_OK) {
    }

    if (MH_EnableHook((DirectInputGetDeviceData)(VTable[10])) != MH_OK) {
    }
}

void DirectInputHook::QueueKey(HKey key, bool pressed)
{
    AdditionalEvents[key] = {
            ConvertToDIKey(key),
            pressed ? 0x80u : 0u,
            GetTickCount(),
            SequenceNumber++,
            pressed
    };
}

void DirectInputHook::SetKeyActive(HKey key, bool active) {
    if (active)
        DisabledGameKeys.erase(ConvertToDIKey(key));
    else
        DisabledGameKeys.insert(ConvertToDIKey(key));
}

HRESULT __stdcall DirectInputHook::HookedDirectInputGetDeviceData(IDirectInputDevice8 * pThis, DWORD a, LPDIDEVICEOBJECTDATA data, LPDWORD numElemsPtr, DWORD d) {
    auto result = OriginalDirectInputGetDeviceData(pThis, a, data, numElemsPtr, d);
    if (result != DI_OK)
        return result;

    if (DisableGameKeys) {
        *numElemsPtr = 0;
        return DI_OK;
    }

    int numElems = *numElemsPtr;
    if (!GetAsyncKeyState(VK_CONTROL)) {
        for (int i = 0; i < numElems; ++i) {
            auto find = DisabledGameKeys.find(data[i].dwOfs);
            if (find != DisabledGameKeys.end()) {
                data[i].dwOfs = 0;
            }
        }
    }

    if (numElems > 0)
        SequenceNumber = data[numElems - 1].dwSequence + 1;

    auto it = AdditionalEvents.begin();
    while (it != AdditionalEvents.end()) {
        auto event = it->second;

        data[numElems].dwData = event.data;
        data[numElems].dwOfs = event.offset;
        data[numElems].dwSequence = event.sequence;
        data[numElems].dwTimeStamp = event.timestamp;
        numElems++;

        it = AdditionalEvents.erase(it);
    }

    *numElemsPtr = numElems;

    return DI_OK;
}

DWORD DirectInputHook::ConvertToDIKey(HKey key) {
    return key;
}