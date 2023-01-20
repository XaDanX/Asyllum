//
// Created by XaDanX on 12/28/2022.
//

#include "Controller.h"
#include "../Locator/Locator.h"
#include "Orders/SpoofMouseOrder.h"
#include "Orders/SpoofMousePosOrder.h"
#include "Orders/TimeoutOrder.h"
#include "Orders/RightClickOrder.h"

void Controller::Update() {
    __try {
        if (this->orderQueue.empty())
            return;
        auto& current = this->orderQueue.front();
        if (current->Execute()) {
            this->orderQueue.pop();
        }
        else {
            return;
        }
}
    __except (true) {
        return;
    }
}

void Controller::IssueClickAt(int x, int y) {
    POINT p;
    auto lastPos = GetCursorPos(&p);

    this->orderQueue.emplace(new SpoofMousePosOrder(x, y));
    this->orderQueue.emplace(new SpoofMouseOrder(true));
    this->orderQueue.emplace(new RightClickOrder(0));
    this->orderQueue.emplace(new TimeoutOrder(8));
    this->orderQueue.emplace(new RightClickOrder(1));
    this->orderQueue.emplace(new SpoofMousePosOrder(p.x, p.y));
    this->orderQueue.emplace(new TimeoutOrder(2));
    this->orderQueue.emplace(new SpoofMouseOrder(false));

}

void Controller::IssueClick() {
    this->orderQueue.emplace(new RightClickOrder(0));
    this->orderQueue.emplace(new TimeoutOrder(8));
    this->orderQueue.emplace(new RightClickOrder(1));
}
