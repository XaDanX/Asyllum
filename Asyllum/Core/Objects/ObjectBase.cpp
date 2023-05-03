//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectBase.h"
#include "../Locator/Locator.h"
#include "../Helpers/StringUtils.h"
#include "../../Utils/Utils.h"
#include <Windows.h>
#include <iostream>


bool ObjectBase::CompareObjectFlags(int a2) {

    int v3; // er8
    unsigned __int64 v4; // rcx
    unsigned __int64 i; // r8
    unsigned __int64 j; // rax
    __int64 v8; // [rsp+10h] [rbp+10h]

    unsigned __int8 *a1 = (unsigned __int8 *)this;


    v3 = *(DWORD *)&a1[4 * a1[0x48] + 0x4C];
    v4 = a1[0x41];
    v8 = (uint32_t)v3;
    for ( i = 0i64; i < v4; ++i )
        *(&v8 + i) ^= ~*(uint64_t*)&a1[8 * i + 0x44];
    if ( a1[0x42] )
    {
        for ( j = 4i64 - a1[0x42]; j < 4; ++j )
            *((BYTE *)&v8 + j) ^= ~a1[j + 0x44];
    }
    return (a2 & (unsigned int)v8) != 0;

}


bool ObjectBase::IsOnScreen(float offsetX, float offsetY) {
    auto point = locator->GetEngine()->WorldToScreen(this->position);
    return point.x > -offsetX && point.x < (locator->GetEngine()->WindowWidth() + offsetX) && point.y > -offsetY &&
           point.y < (locator->GetEngine()->WindowHeight() + offsetY);
}

AiManager *ObjectBase::GetAiManager() {

    return reinterpret_cast<AiManager *>((__int64)reinterpret_cast<AiManager * (__thiscall*)(ObjectBase*)>(this->vTable[152])(this));

    /*
   int v1 = *reinterpret_cast<__int8 *>(reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager);
    int v2 = reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager - 8;
    int v3 = *reinterpret_cast<int *>(v2 + 4);
    int v4 = *reinterpret_cast<int *>((v2 + (4 * v1 + 12)));
    v4 = v4 ^ (~v3);
    return reinterpret_cast<AiManager *>(*reinterpret_cast<int *>(v4 + 8));*/
}

