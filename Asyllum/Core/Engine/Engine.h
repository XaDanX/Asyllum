//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_ENGINE_H
#define ASYLLUM_ENGINE_H


#include "../../Math/Vector.h"

class Engine {
public:
    void Update();
    float GameTime() const;
    int WindowWidth() const;
    int WindowHeight() const;
    Vector2 WorldToScreen(const Vector3& pos);
};


#endif //ASYLLUM_ENGINE_H
