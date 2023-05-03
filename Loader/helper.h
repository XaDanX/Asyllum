//
// Created by XaDanX on 4/14/2023.
//

#ifndef ASYLLUM_HELPER_H
#define ASYLLUM_HELPER_H
#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "XorStr.h"
#include <vector>

typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI* NtResumeProcess)(IN HANDLE ProcessHandle);

void suspend(HANDLE hProc)
{

    NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(
            GetModuleHandleA(XorStr("ntdll").c_str()), XorStr("NtSuspendProcess").c_str());

    pfnNtSuspendProcess(hProc);
}

void resume(HANDLE hProc) {


    NtResumeProcess pfnNtResumeProcesss = (NtResumeProcess)GetProcAddress(
            GetModuleHandleA(XorStr("ntdll").c_str()), XorStr("NtResumeProcess").c_str());

    pfnNtResumeProcesss(hProc);
}

DWORD GetPid(const std::wstring& processName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    DWORD pid = 0;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return pid;
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return pid;
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do {
        // Check if the process name matches the one we're looking for
        if (_wcsicmp(pe32.szExeFile, processName.c_str()) == 0) {
            pid = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    // Close the handle to the process snapshot.
    CloseHandle(hProcessSnap);

    return pid;
}
#endif //ASYLLUM_HELPER_H
