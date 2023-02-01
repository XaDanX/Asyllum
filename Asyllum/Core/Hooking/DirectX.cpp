//
// Created by XaDanX on 12/1/2022.
//

#include <thread>
#include "DirectX.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "HookingService.h"
#include "../../kiero/kiero.h"
#include "../../Protection/XorStr.h"
#include "../Locator/Locator.h"


std::mutex dxLock;


extern bool init = false;

long DirectX::hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    locator->GetHookingService()->SetDevice(pDevice);
    if (!init) {
        locator->GetTextureManager()->LoadDeployables();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 16.0f);

        ImGuiStyle* style = &ImGui::GetStyle();

        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.8f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
        style->Colors[ImGuiCol_Border] = ImColor(135, 21, 161, 255);

        style->AntiAliasedLines = true;
        style->AntiAliasedFill = true;
        style->WindowRounding = 0;
        style->WindowPadding = ImVec2(8, 10.0f);
        style->WindowRounding = 2.0f;
        style->ScrollbarRounding = 3.0f;
        style->GrabRounding = 2.0f;
        style->AntiAliasedLines = true;
        style->AntiAliasedFill = true;
        style->WindowRounding = 2;
        style->ChildRounding = 2;
        style->ScrollbarSize = 16;
        style->ScrollbarRounding = 3;
        style->GrabRounding = 2;
        style->ItemSpacing.x = 10;
        style->ItemSpacing.y = 4;
        style->IndentSpacing = 22;
        style->FramePadding.x = 6;
        style->FramePadding.y = 4;
        style->Alpha = 1.0f;
        style->FrameRounding = 3.0f;


        style->WindowRounding = 0;
        style->WindowPadding = ImVec2(8, 10.0f);
        style->ItemSpacing = ImVec2(8, 12.0f);
        style->ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        ImGui_ImplWin32_Init(locator->GetHookingService()->GetWindow());
        ImGui_ImplDX9_Init(pDevice);
        init = true;
    }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            locator->GetHookingService()->isMenuOpen = !locator->GetHookingService()->isMenuOpen;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        if (locator->GetAsyllumInstance()->initialized) {
            locator->GetAsyllumInstance()->OnTick();
            if (locator->GetHookingService()->isMenuOpen) {
                locator->GetAsyllumInstance()->OnGui();

                ImGui::Begin(XorStr("Panic menu").c_str(), 0,
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
                        ImGuiWindowFlags_NoScrollWithMouse);
                if (ImGui::Button(XorStr("Unload").c_str())) {
                    locator->GetHookingService()->UnHook();
                }
                ImGui::End();

            }


        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

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

long __stdcall DirectX::hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    long result = locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);
    if (result >= 0) {
        ImGui_ImplDX9_CreateDeviceObjects();
    }
    if (!locator->GetHookingService()->isHooked) {
        locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);
        return 0;
    }
    return result;
}




long __stdcall DirectX::hkPresent(IDirect3DDevice9Ex *pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride,
                   const RGNDATA *pDirtyRegion) {

    return locator->GetHookingService()->GetOriginalPresent()(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
