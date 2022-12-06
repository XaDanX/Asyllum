//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectBase.h"
#include "../Locator/Locator.h"
#include "../Helpers/StringUtils.h"

bool ObjectBase::CompareObjectFlags(int a2) {

    unsigned int v3; // edx
    unsigned int v4; // esi
    unsigned __int8 *v5; // ecx
    int v6; // eax
    unsigned __int8 v7; // al
    unsigned int v8; // eax
    unsigned __int8 *v9; // edx
    char v10; // cl
    int v12; // [esp+8h] [ebp-4h]

    v5 = (unsigned __int8*)this;

    v3 = 0;
    v4 = v5[57];
    v12 = *(DWORD *)&v5[4 * v5[64] + 68];
    if ( v4 )
    {
        v5 = v5 + 60;
        do
        {
            v6 = *(DWORD *)v5;
            v5 += 4;
            *(&v12 + v3++) ^= ~v6;
        }
        while ( v3 < v4 );
    }
    v7 = v5[58];
    if ( v7 )
    {
        v8 = 4 - v7;
        if ( v8 < 4 )
        {
            v9 = &v5[v8 + 60];
            do
            {
                v10 = *v9++;
                *((BYTE *)&v12 + v8++) ^= ~v10;
            }
            while ( v8 < 4 );
        }
    }
    return (v12 & a2) != 0;

}
