//
// Created by XaDanX on 4/14/2023.
//
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <string>
#include <windows.h>
#include "Ui.h"
#include "../imgui/imgui.h"
#include "../XorStr.h"
#include "../Globals/Globals.h"
#include <experimental/filesystem>
#include "../helper.h"

namespace fs = std::experimental::filesystem;

using namespace std;

void Ui::Draw() {
    ImGui::SetNextWindowSize(ImVec2((float)Globals::width+5, (float)Globals::height+5));
    ImGui::SetNextWindowPos(ImVec2(-5, -5));

    if (Globals::key.empty() && !Globals::loggedIn) {
        ImGui::Begin(XorStr("##Login").c_str(), 0, Globals::flags);
        ImGui::TextColored(ImColor(232, 192, 46, 255), "%s", XorStr("Asyllum Loader").c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImColor(232, 192, 46, 255), "%s", XorStr("|").c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImColor(0, 181, 33, 255), "%s", XorStr("CONNECTED").c_str());
        ImGui::Separator();

        ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() + 4));
        ImGui::TextColored(ImColor(232, 192, 46, 255), "%s", XorStr("License key: ").c_str());
        ImGui::SameLine();
        ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 4));
        ImGui::InputText(XorStr("").c_str(), Globals::keyBuffer, IM_ARRAYSIZE(Globals::keyBuffer));
        if (ImGui::Button(XorStr("Login").c_str())) {
            std::cout << std::string(Globals::keyBuffer);
            Globals::loggedIn = true;
        }

        ImGui::End();

    } else { // check for user etc..
        ImGui::Begin(XorStr("##Loader").c_str(), 0, Globals::flags);
        ImGui::TextColored(ImColor(232, 192, 46, 255), "%s", XorStr("Asyllum Loader").c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImColor(232, 192, 46, 255), "|  %s", XorStr("?????").c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImColor(232, 192, 46, 255), "|  %s", XorStr("05-05-2023").c_str());
        ImGui::Separator();

        // check for access


        if (ImGui::Button(XorStr("Load").c_str())) {
            DWORD pid = 0;
            string fullPath;
            char buf[MAX_PATH] = { 0 };
            auto dllpath = fs::current_path().string() + XorStr("/") + XorStr("Asyllum.dll");
            GetFullPathNameA(dllpath.c_str(), MAX_PATH, buf, nullptr);
            fullPath = string(buf, MAX_PATH);

            do {
                pid = GetPid(L"League of Legends.exe");
                if (pid != 0) {

                    cout << XorStr("Found game!").c_str() << std::endl;
                    break;
                    }
            } while (pid == 0);
            Sleep(600);

            HWND hwnd = FindWindowEx(NULL, NULL, NULL, NULL);
            while (hwnd) {
                DWORD currentProcessId;
                GetWindowThreadProcessId(hwnd, &currentProcessId);

                if (currentProcessId == pid) {
                    break;
                }

                hwnd = FindWindowEx(NULL, hwnd, NULL, NULL);
            }
            ShowWindow(hwnd, 1);

            auto process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, pid);
            if (process) {


                auto fpLoadLibrary = (LPVOID) GetProcAddress(GetModuleHandleA(XorStr("kernel32.dll").c_str()),
                                                             XorStr("LoadLibraryA").c_str());

                auto mem = VirtualAllocEx(process, NULL, fullPath.length() + 1, MEM_RESERVE | MEM_COMMIT,
                                          PAGE_READWRITE);
                if (!mem) {
                    cerr << XorStr("Library name cannot be allocated") << endl;
                }

                if (!WriteProcessMemory(process, mem, fullPath.c_str(), fullPath.length() + 1, nullptr)) {
                    cerr << XorStr("Library name cannot be written") << endl;
                }
                //resume(process);
                if (!CreateRemoteThread(process, nullptr, 0, (LPTHREAD_START_ROUTINE) fpLoadLibrary, mem, 0, nullptr)) {
                    cerr << XorStr("Threads cannot be created") << endl;
                } else {
                    cout << XorStr("Injected!") << endl;
                }
            }

            process ? CloseHandle(process) : 0;

        }




        ImGui::End();
    }
}
