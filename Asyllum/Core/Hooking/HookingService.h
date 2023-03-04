//
// Created by XaDanX on 12/1/2022.
//
#ifndef ASYLLUM_HOOKINGSERVICE_H
#define ASYLLUM_HOOKINGSERVICE_H

#include <d3d9.h>
#include <iostream>
#include "FakeMouse.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class HookingService {
private:
    typedef long(__stdcall *EndScene)(LPDIRECT3DDEVICE9);

    EndScene oEndScene;

    typedef LRESULT(CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

    WNDPROC oWndProc;

    typedef long(__stdcall *Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS *);

    Reset oReset;

    typedef long(__stdcall *Present)(IDirect3DDevice9Ex *, const RECT *, const RECT *, HWND, const RGNDATA *);

    Present oPresent;

    HWND window = NULL;
    LPDIRECT3DDEVICE9 device = NULL;

public:
    bool isMenuOpen = true;
    bool isHooked = true;

    bool Initialize();

    bool UnHook();

    Present GetOriginalPresent() {
        return this->oPresent;
    }

    EndScene GetOriginalEndScene() {
        return this->oEndScene;
    };

    WNDPROC GetOriginalWndProc() {
        return this->oWndProc;
    };

    Reset GetOriginalReset() {
        return this->oReset;
    };

    HWND GetWindow() {
        return this->window;
    }

    LPDIRECT3DDEVICE9 GetDevice() {
        return this->device;
    }

    void SetDevice(LPDIRECT3DDEVICE9 dev) {
        this->device = dev;
    }


};


#endif //ASYLLUM_HOOKINGSERVICE_H
