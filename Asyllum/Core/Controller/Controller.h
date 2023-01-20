//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_CONTROLLER_H
#define ASYLLUM_CONTROLLER_H
#include <iostream>
#include <queue>
#include "Orders/OrderBase.h"
#include "../../Globals/KeyCodes.h"
#include <thread>

class Controller {
private:
    std::queue<std::unique_ptr<OrderBase>> orderQueue;
public:
    void Update();

    void IssueClickAt(int x, int y);
    void IssueClick();

    void IssueClickButtonAt(int x, int y, HKey button);

    void IssueClickButton(HKey button);



};


#endif //ASYLLUM_CONTROLLER_H
