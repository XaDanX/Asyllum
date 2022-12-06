//
// Created by XaDanX on 12/4/2022.
//

#include "AiManager.h"
#include "Windows.h"

std::vector<Vector3> AiManager::GetNavigationArray() {
    std::vector<Vector3> points;
    int arrayLength = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + Offsets::AiManager::NavigationArrayLength);
    if (arrayLength > 1) {
        int navigationArray = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(this) + Offsets::AiManager::NavigationArray);
        for (int index = 0; index < arrayLength; index++) {
            auto point = *reinterpret_cast<Vector3*>(navigationArray + (12 * index));
            points.push_back(point);
        }
    }
    return points;
}
