//
// Created by XaDanX on 2/2/2023.
//
#define DIRECTINPUT_VERSION 0x0800
#ifndef ASYLLUM_DIRECTINPUTHOOK_H
#define ASYLLUM_DIRECTINPUTHOOK_H


#include "../../Globals/KeyCodes.h"
#include <set>
#include <map>
#include <dinput.h>
typedef HRESULT(WINAPI* DirectInputGetDeviceData)(IDirectInputDevice8*, DWORD a, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
struct InputEventInfo {
    DWORD offset;
    DWORD data;
    DWORD timestamp;
    DWORD sequence;
    bool  persistent;
};

class DirectInputHook {

public:
    static void Hook();
    static void QueueKey(HKey key, bool pressed);
    static void SetKeyActive(HKey key, bool active);

    static HRESULT WINAPI HookedDirectInputGetDeviceData(IDirectInputDevice8* pThis, DWORD a, LPDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d);

public:
    static bool                        DisableGameKeys;

private:
    static DWORD                           ConvertToDIKey(HKey key);
    static DirectInputGetDeviceData        OriginalDirectInputGetDeviceData;
    static std::set<DWORD>                 DisabledGameKeys;
    static std::map<DWORD, InputEventInfo> AdditionalEvents;

    static DWORD                           SequenceNumber;
};


#endif //ASYLLUM_DIRECTINPUTHOOK_H
