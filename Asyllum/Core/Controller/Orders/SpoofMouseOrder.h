//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_SPOOFMOUSEORDER_H
#define ASYLLUM_SPOOFMOUSEORDER_H
#include "OrderBase.h"
#include "../../Hooking/FakeMouse.h"

class SpoofMouseOrder : public OrderBase {
private:

    bool state = false;
public:
    SpoofMouseOrder(bool _state) {
        this->state = _state;
    }
    bool Execute() {
        if (this->state)
            FakeMouse::Spoof();
        else
            FakeMouse::UnSpoof();
        return true;

    }
};
#endif //ASYLLUM_SPOOFMOUSEORDER_H
