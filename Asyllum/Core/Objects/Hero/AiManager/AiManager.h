//
// Created by XaDanX on 12/4/2022.
//

#ifndef ASYLLUM_AIMANAGER_H
#define ASYLLUM_AIMANAGER_H

#include <vector>
#include "../../../../Globals/Globals.h"
#include "../../../../Globals/Offsets.h"
#include "../../../../Math/Vector.h"
#include <algorithm>
#include <iostream>
#include <minmax.h>

class AiManager {
public:
    union {
        DEFINE_MEMBER_N(Vector3, serverPosition, Offsets::AiManager::ServerPosition);
        DEFINE_MEMBER_N(int, currentSegment, Offsets::AiManager::CurrentSegment);
        DEFINE_MEMBER_N(bool, isDashing, Offsets::AiManager::IsDashing);
        DEFINE_MEMBER_N(bool, isMoving, Offsets::AiManager::IsMoving);
        DEFINE_MEMBER_N(float, dashSpeed, Offsets::AiManager::DashSpeed);
        DEFINE_MEMBER_N(Vector3, startPath, Offsets::AiManager::StartPath);
        DEFINE_MEMBER_N(Vector3, endPath, Offsets::AiManager::EndPath);
    };

    std::vector<Vector3> GetNavigationArray();
};


#endif //ASYLLUM_AIMANAGER_H
