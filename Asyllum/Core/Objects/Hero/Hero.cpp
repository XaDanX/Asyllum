//
// Created by XaDanX on 12/1/2022.
//

#include "Hero.h"
#include "../../Locator/Locator.h"

Vector2 Hero::GetHealthBarPosition() {

    Vector3 point = position.clone();
    point.y += 100;//this->unitInfo->healthBarHeight;

    Vector2 out = locator->GetEngine()->WorldToScreen(point);
    out.y -= ((float)locator->GetEngine()->WindowHeight() * 0.00083333335f * 100);//this->unitInfo->healthBarHeight);
    out.x -= 70.0f;
    return out;

}
