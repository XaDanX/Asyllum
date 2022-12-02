//
// Created by XaDanX on 12/1/2022.
//
#ifndef ASYLLUM_HOOKINGSERVICE_H
#define ASYLLUM_HOOKINGSERVICE_H
#include <d3d9.h>


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class HookingService {
private:
    typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
    EndScene oEndScene;

    typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
    WNDPROC oWndProc;

    typedef long(__stdcall* Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
    Reset oReset;

    HWND window = NULL;
public:
    bool isMenuOpen = true;
    bool isHooked = true;
    bool Initialize();
    bool UnHook();

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


};


#endif //ASYLLUM_HOOKINGSERVICE_H
