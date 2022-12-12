//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_DIRECTX_H
#define ASYLLUM_DIRECTX_H
#include <d3d9.h>


class DirectX {
public:
    static long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
    static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static long __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

};


#endif //ASYLLUM_DIRECTX_H
