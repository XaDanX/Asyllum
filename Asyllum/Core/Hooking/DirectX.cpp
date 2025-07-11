#include <thread>
#include "DirectX.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "HookingService.h"
#include "../../kiero/kiero.h"
#include "../../Protection/XorStr.h"
#include "../Locator/Locator.h"


extern bool init = false;

long DirectX::hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
        locator->GetHookingService()->SetDevice(pDevice);
        if (!init) {
            locator->GetTextureManager()->LoadDeployables();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
            io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 16.0f);
            locator->GetMenu()->Initialize();
            ImGui_ImplWin32_Init(locator->GetHookingService()->GetWindow());
            ImGui_ImplDX9_Init(pDevice);
            init = true;
        }

        IDirect3DStateBlock9* dxStateBlock = NULL;
        if (locator->GetHookingService()->GetDevice()->CreateStateBlock(D3DSBT_ALL, &dxStateBlock) < 0) {
            return locator->GetHookingService()->GetOriginalEndScene()(pDevice);
        }

        D3DMATRIX last_world, last_view, last_projection;
        locator->GetHookingService()->GetDevice()->GetTransform(D3DTS_WORLD, &last_world);
        locator->GetHookingService()->GetDevice()->GetTransform(D3DTS_VIEW, &last_view);
        locator->GetHookingService()->GetDevice()->GetTransform(D3DTS_PROJECTION, &last_projection);

        D3DVIEWPORT9 vp;
        vp.X = vp.Y = 0;
        vp.Width = locator->GetEngine()->WindowWidth();
        vp.Height = locator->GetEngine()->WindowHeight();
        vp.MinZ = 0.0f;
        vp.MaxZ = 1.0f;
        locator->GetHookingService()->GetDevice()->SetViewport(&vp);

        locator->GetHookingService()->GetDevice()->SetPixelShader(NULL);
        locator->GetHookingService()->GetDevice()->SetVertexShader(NULL);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
        locator->GetHookingService()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        locator->GetHookingService()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
        locator->GetHookingService()->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        locator->GetHookingService()->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

        static const D3DMATRIX identityMatrix = {{{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }}};

        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&Globals::viewMatrix[0]);
        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&Globals::projectionMatrix[0]);


        if (GetAsyncKeyState(VK_INSERT) & 1) {
            locator->GetHookingService()->isMenuOpen = !locator->GetHookingService()->isMenuOpen;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        if (locator->GetAsyllumInstance()->initialized) {
            __try {
                    locator->GetAsyllumInstance()->OnTick();
            } __except(1) {
                    locator->GetConsole()->Print(XorStr("[CORE] Exception in Asyllum::OnTick()").c_str());
                }
            if (locator->GetHookingService()->isMenuOpen) {
                __try {
                    locator->GetAsyllumInstance()->OnGui();
                } __except(1) {
                    locator->GetConsole()->Print(XorStr("[CORE] Exception in Asyllum::OnGui()").c_str());
                }
            }


        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_WORLD, &last_world);
        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_VIEW, &last_view);
        locator->GetHookingService()->GetDevice()->SetTransform(D3DTS_PROJECTION, &last_projection);

        dxStateBlock->Apply();
        dxStateBlock->Release();

        if (!locator->GetHookingService()->isHooked) {
            kiero::shutdown();
            (WNDPROC) SetWindowLongPtr(locator->GetHookingService()->GetWindow(), GWLP_WNDPROC,
                                       (LONG_PTR) (locator->GetHookingService()->GetOriginalWndProc()));
            locator->GetHookingService()->GetOriginalEndScene()(pDevice);
            return 0;

        }


        return locator->GetHookingService()->GetOriginalEndScene()(pDevice);



}

LRESULT __stdcall DirectX::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (locator->GetHookingService()->isMenuOpen) {
        if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {}
    }
    return CallWindowProc(locator->GetHookingService()->GetOriginalWndProc(), hWnd, uMsg, wParam, lParam);
}

long __stdcall DirectX::hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters) {
    ImGui_ImplDX9_InvalidateDeviceObjects();
    long result = locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);
    if (result >= 0) {
        ImGui_ImplDX9_CreateDeviceObjects();
    }
    if (!locator->GetHookingService()->isHooked) {
        locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);

        for (auto &it: locator->GetGameData()->Units) {
            delete it.second;
        }
        for (auto &it: locator->GetGameData()->Spells) {
            delete it.second;
        }
        locator->GetGameData()->Units.clear();
        locator->GetGameData()->Spells.clear();

        return 0;
    }
    return result;
}


long __stdcall DirectX::hkPresent(IDirect3DDevice9Ex *pDevice, const RECT *pSourceRect, const RECT *pDestRect,
                                  HWND hDestWindowOverride,
                                  const RGNDATA *pDirtyRegion) {

    return locator->GetHookingService()->GetOriginalPresent()(pDevice, pSourceRect, pDestRect, hDestWindowOverride,
                                                              pDirtyRegion);
}