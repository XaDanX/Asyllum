//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectBase.h"
#include "../Locator/Locator.h"
#include "../Helpers/StringUtils.h"
#include "../../Utils/Utils.h"

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


bool ObjectBase::IsOnScreen(float offsetX, float offsetY) {
    auto point = locator->GetEngine()->WorldToScreen(this->position);
    return point.x > -offsetX && point.x < (locator->GetEngine()->WindowWidth() + offsetX) && point.y > -offsetY && point.y < (locator->GetEngine()->WindowHeight() + offsetY);
}

AiManager *ObjectBase::GetAiManager() {
    int v1 = *reinterpret_cast<__int8*>(reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager);
    int v2 = reinterpret_cast<DWORD>(this) + Offsets::GameObject::AiManager - 8;
    int v3 = *reinterpret_cast<int*>(v2 + 4);
    int v4 = *reinterpret_cast<int*>((v2 + (4 * v1 + 12)));
    v4 = v4 ^ (~v3);
    return reinterpret_cast<AiManager*>(*reinterpret_cast<int*>(v4 + 8));
}

Vector3 ObjectBase::PredictPosition(float futureTime) {
    auto aiManager = GetAiManager();
    if (!Utils::IsValid(aiManager)) {
        return this->position;
    }
    if (futureTime < 0.03) {
        return this->position;
    }

    auto path = aiManager->GetNavigationArray();

    auto pathSize = aiManager->PathSize();

    if(aiManager->isMoving) {
        float unitsPerSec = aiManager->isDashing ? aiManager->dashSpeed : movementSpeed;
        if (unitsPerSec < 1.f)
            return position;

        for (int i = 0; i < pathSize - 1; ++i) {
            float segmentDistance = path[i].distance(path[i + 1]);
            float secsToFinishSegment = segmentDistance / unitsPerSec;

            if (secsToFinishSegment < futureTime) {
                futureTime -= secsToFinishSegment;
            }
            else {
                Vector3 delta = path[i + 1].sub(path[i]).normalize().scale(futureTime * unitsPerSec);
                return Vector3(path[i].x + delta.x, path[i].y, path[i].z + delta.z);
            }

        }

        Vector3 lastNode = path[pathSize - 1];
        Vector3 delta = lastNode.sub(path[pathSize - 2]).normalize().scale(futureTime * unitsPerSec);
        return Vector3(lastNode.x + delta.x, lastNode.y, lastNode.z + delta.z);
    }

    return position;
}
