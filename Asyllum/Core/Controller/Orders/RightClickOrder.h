//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_RIGHTCLICKORDER_H
#define ASYLLUM_RIGHTCLICKORDER_H
#include "OrderBase.h"
#include <Windows.h>


class RightClickOrder : public OrderBase {
private:
    int clickType;
public:
    RightClickOrder(int type) {
        this->clickType = type;
    }
    bool Execute() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        if (this->clickType == 0)
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        else
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(1, &input, sizeof(INPUT));
        return true;

    }
};
#endif //ASYLLUM_RIGHTCLICKORDER_H
