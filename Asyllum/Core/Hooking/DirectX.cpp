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


extern bool init = false;


long DirectX::hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    auto timeBegin = std::chrono::high_resolution_clock::now();
    if (!init) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        io.Fonts->AddFontFromFileTTF(XorStr("C:\\Deployable\\Font.ttf").c_str(), 16.0f);
        ImGuiStyle* style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.08f, 0.08f, 0.08f, 0.88f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.07f, 0.07f, 0.94f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.09f, 0.09f, 0.09f, 0.88f);
        colors[ImGuiCol_Border]                 = ImVec4(0.72f, 0.72f, 0.72f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.03f, 0.03f, 0.03f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.16f, 0.16f, 0.16f, 0.40f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.33f, 0.34f, 0.34f, 0.67f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(0.53f, 0.53f, 0.53f, 0.31f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.81f, 0.81f, 0.81f, 0.31f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
        colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.86f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.34f, 0.34f, 0.34f, 0.80f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style->ScrollbarSize = 20.f;
        style->GrabMinSize = 20.f;

        style->WindowBorderSize = 1.5f;
        style->ChildBorderSize = 1.5f;
        style->PopupBorderSize = 1.5f;
        style->FrameBorderSize = 1.5f;
        style->TabBorderSize = 1.5f;

        style->WindowRounding = 4.f;
        style->ChildRounding = 4.f;
        style->FrameRounding = 6.f;
        style->PopupRounding = 6.f;
        style->ScrollbarRounding = 6.f;
        style->GrabRounding = 6.f;
        style->TabRounding = 8.f;
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

    locator->GetAsyllumInstance()->OnTick();
    if (locator->GetHookingService()->isMenuOpen) {
        locator->GetAsyllumInstance()->OnGui();
    }


    std::chrono::duration<float, std::milli> updateTime = std::chrono::high_resolution_clock::now() - timeBegin;

    ImGui::Begin(XorStr("DEBUG INFO").c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text(XorStr("Update: %f ms").c_str(), static_cast<float>(updateTime.count()));

    if (ImGui::InvisibleButton(XorStr("UNLOAD").c_str(), ImVec2(100, 50))) {
        locator->GetHookingService()->UnHook();
    }
    ImGui::End();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    if (!locator->GetHookingService()->isHooked) {
        kiero::shutdown();
        (WNDPROC)SetWindowLongPtr(locator->GetHookingService()->GetWindow(), GWLP_WNDPROC, (LONG_PTR)(locator->GetHookingService()->GetOriginalWndProc()));
        locator->GetHookingService()->GetOriginalEndScene()(pDevice);
        return 0;

    }

    return locator->GetHookingService()->GetOriginalEndScene()(pDevice);
}

LRESULT __stdcall DirectX::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (locator->GetHookingService()->isMenuOpen) {
        if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {}
    } else {
    }
    ImGui::GetIO().WantCaptureMouse = locator->GetHookingService()->isMenuOpen;

    return CallWindowProc(locator->GetHookingService()->GetOriginalWndProc(), hWnd, uMsg, wParam, lParam);
}

long __stdcall DirectX::hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    long result = locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);
    ImGui_ImplDX9_CreateDeviceObjects();
    if (!locator->GetHookingService()->isHooked) {
        locator->GetHookingService()->GetOriginalReset()(pDevice, pPresentationParameters);
        return 0;
    }
    return result;
}