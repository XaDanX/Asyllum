//
// Created by XaDanX on 12/4/2022.
//

#include "AiManager.h"
#include "Windows.h"
#include "../../../Locator/Locator.h"

std::vector<Vector3> AiManager::GetNavigationArray() {
    std::vector<Vector3> points;
    int navigationArraySize = *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(this) +
                                                      Offsets::AiManager::NavigationArray + 0x8);

    if (navigationArraySize > 1) {
        uint64_t navigationArray = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint64_t>(this) +
                                                       Offsets::AiManager::NavigationArray);
        for (int index = 0; index < navigationArraySize; index++) {
            auto point = *reinterpret_cast<Vector3 *>(navigationArray + (12 * index));
            points.push_back(point);
        }
    }
    return points;
}
