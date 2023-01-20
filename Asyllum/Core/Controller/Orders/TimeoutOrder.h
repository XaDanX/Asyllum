//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_TIMEOUTORDER_H
#define ASYLLUM_TIMEOUTORDER_H
#include <iostream>
#include <chrono>
#include <thread>
#include "OrderBase.h"
#include <windows.h>
using namespace std::chrono_literals;

class TimeoutOrder : public OrderBase {
private:

    float time = 10;
    bool started = false;
    DWORD startTime;
    DWORD timeDiff;
public:
    TimeoutOrder(float _time) {
        this->time = _time;
    }
    bool Execute() {
        if (!started) {
            startTime = locator->GetEngine()->GetProcessorTime();
            started = true;
        }
        timeDiff = locator->GetEngine()->GetProcessorTime() - startTime;
        if (timeDiff > time) {
            return true;
        }
        return false;

    }
};
#endif //ASYLLUM_TIMEOUTORDER_H
