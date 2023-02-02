#ifndef ASYLLUM_DIRECTX_H
#define ASYLLUM_DIRECTX_H
#include <d3d9.h>
#include <iostream>
#include <mutex>

class DirectX {
public:
    static long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
    static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static long __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
    static long __stdcall hkPresent(IDirect3DDevice9Ex* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);

};


#endif //ASYLLUM_DIRECTX_H