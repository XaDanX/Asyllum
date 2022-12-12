//
// Created by XaDanX on 12/11/2022.
//

#include "Utils.h"

bool Utils::IsValid(void *pointer) {
    if ((int)pointer < 0x100) return false;
    return true;
}