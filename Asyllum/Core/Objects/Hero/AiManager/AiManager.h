//
// Created by XaDanX on 12/4/2022.
//

#ifndef ASYLLUM_AIMANAGER_H
#define ASYLLUM_AIMANAGER_H

#include <vector>
#include "../../../../Globals/Globals.h"
#include "../../../../Globals/Offsets.h"
#include "../../../../Math/Vector.h"

class AiManager {
public:
    union {
        DEFINE_MEMBER_N(Vector3, serverPosition, Offsets::AiManager::ServerPosition);
        DEFINE_MEMBER_N(int, currentSegment, Offsets::AiManager::CurrentSegment);
    };

    std::vector<Vector3> GetNavigationArray();
};


#endif //ASYLLUM_AIMANAGER_H
