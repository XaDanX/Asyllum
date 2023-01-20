//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_SPOOFMOUSEPOSORDER_H
#define ASYLLUM_SPOOFMOUSEPOSORDER_H
#include "OrderBase.h"
#include "../../Hooking/FakeMouse.h"

class SpoofMousePosOrder : public OrderBase {
private:

    int x = 0;
    int y = 0;
public:
    SpoofMousePosOrder(int _x, int _y) {
        x = _x;
        y = _y;
    }
    bool Execute() {
        FakeMouse::SetSpoofedCursorPos(x, y);
        return true;
    }
};
#endif //ASYLLUM_SPOOFMOUSEPOSORDER_H
