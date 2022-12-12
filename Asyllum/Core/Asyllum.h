//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_ASYLLUM_H
#define ASYLLUM_ASYLLUM_H


class Asyllum {
public:
    bool initialized = false;
public:
    bool Initialize();

    void OnGui();

    void OnTick();

    void OnThreadTick();

};


#endif //ASYLLUM_ASYLLUM_H
