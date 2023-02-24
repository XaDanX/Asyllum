//
// Created by XaDanX on 2/22/2023.
//

#include "Menu.h"
#include "../imgui/imgui.h"
#include "../Protection/XorStr.h"
#include "../Core/Locator/Locator.h"

void Menu::Initialize() {
    ImGuiStyle& style = ImGui::GetStyle( );

    style.ScrollbarRounding = 0;
    style.ChildRounding = 0.2;

    style.Colors[ImGuiCol_TitleBg] = ImColor(3, 3, 3);
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(3, 3, 3);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(3, 3, 3);
    style.Colors[ImGuiCol_WindowBg] = ImColor( 16 , 16 , 16 );
    style.Colors[ImGuiCol_ChildBg] = ImColor( 24 , 24 , 24 );
    style.Colors[ImGuiCol_Text] = ImColor( 255 , 255 , 255 );
    style.Colors[ImGuiCol_CheckMark] = ImColor( 255 , 255 , 255 );

    style.Colors[ImGuiCol_Header] = ImColor( 30 , 30 , 30 );
    style.Colors[ImGuiCol_HeaderActive] = ImColor( 28 , 28 , 28 );
    style.Colors[ImGuiCol_HeaderHovered] = ImColor( 28 , 28 , 28 );

    style.Colors[ImGuiCol_Button] = ImColor( 31 , 31 , 31 );
    style.Colors[ImGuiCol_ButtonActive] = ImColor( 47 , 47 , 47 );
    style.Colors[ImGuiCol_ButtonHovered] = ImColor( 44 , 44 , 44 );

    style.Colors[ImGuiCol_Border] = ImColor( 0 , 0 , 0 , 255 );
}

void Menu::Update() {
    ImGui::SetNextWindowSize(ImVec2( 480 * 2 , 295  * 2));
    ImGui::Begin( "MW" , 0 , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);


    ImGui::BeginChild("##Logo", ImVec2(208, 58), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::SameLine();

    ImGui::SetCursorPos(ImVec2(1, 5));//
    ImGui::Image(locator->GetTextureManager()->GetTexture("logo"), ImVec2(200, 50));
    ImGui::EndChild();


    ImGui::BeginChild( "##LeftSide", ImVec2(208, ImGui::GetContentRegionAvail().y), true );
    for (int i = 0; i < static_cast<int>(locator->GetModuleManager()->moduleList.size()); i++) {
        auto& module = locator->GetModuleManager()->moduleList.at(i);
        if (ImGui::Button(module->name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
            tab = i;
        }
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetContentRegionAvail().y - 40);
    if (ImGui::Button(XorStr("UNLOAD").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
        locator->GetHookingService()->UnHook();
    }

    ImGui::EndChild( );

    ImGui::SameLine( );

    ImGui::SetCursorPosY(8);

    ImGui::BeginChild( "##RightSide" , ImVec2( ImGui::GetContentRegionAvail().x , ImGui::GetContentRegionAvail( ).y ) , true );
    for (int i = 0; i < static_cast<int>(locator->GetModuleManager()->moduleList.size()); i++) {
        auto& module = locator->GetModuleManager()->moduleList.at(i);
        if (i == this->tab) {
            module->OnGui();
        }
    }
    ImGui::EndChild( );


    ImGui::End( );
}
