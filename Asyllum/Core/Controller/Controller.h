//
// Created by XaDanX on 12/28/2022.
//

#ifndef ASYLLUM_CONTROLLER_H
#define ASYLLUM_CONTROLLER_H
#include <iostream>
#include <queue>
#include "../../Globals/KeyCodes.h"
#include "../../Math/Vector.h"
#include "../Hooking/FakeMouse.h"
#include "../Hooking/DirectInputHook.h"
#include <windows.h>
#include <chrono>
#include <functional>

using namespace std::chrono;

enum IoStepId {
    IO_PRESS_KEY,
    IO_PRESS_KEY_AT,
    IO_CLICK,
    IO_CLICK_AT,
    IO_CLICK_UNIT,
    IO_HOLD_KEY,
    IO_UNHOLD_KEY,
    IO_UNHOLD_KEY_AT,
    IO_DELAY
};

enum ClickType {
    CT_LEFT_CLICK,
    CT_RIGHT_CLICK
};

class IoStep {

public:
    void         Start() {};
    virtual bool Update() = 0;
};

class IoStepBatch {
public:
    IoStepBatch(std::initializer_list<std::shared_ptr<IoStep>> initSteps, int controlId);
    void Start();
    bool Update();
    bool operator==(const IoStepBatch& other);

public:
    int                                 controlId;

private:
    std::shared_ptr<IoStep>             currentStep;
    std::queue<std::shared_ptr<IoStep>> steps;
};

class InputController {

public:

    bool    IsDown(HKey key);
    bool    IsDown(int key);

    bool    WasPressed(HKey key, float lastMillis = 250.f);

    Vector2 GetMouseCursor();

    void    SetMouseCursor(const Vector2& position);

    void UpdateIssuedOperations();

    void IssuePressKey(HKey key);

    void IssuePressKeyAt(HKey key, std::function<Vector2()> posGetter);

    void IssueClick(ClickType type, HKey withKeyHold = NO_KEY);

    void IssueClickAt(ClickType type, std::function<Vector2()> posGetter, HKey withKeyHold = NO_KEY);

    void IssueHoldKey(HKey key);

    void IssueUnholdKey(HKey key);

    void IssueUnholdKeyAt(HKey key, std::function<Vector2()> posGetter);

    void IssueDelay(float millis);

    static int ImGuiKeySelect(const char* label, int key);

    int GetVirtualKey(HKey key);

private:
    void PushIoBatch(std::shared_ptr<IoStepBatch> batch);

public:
    static const float                ScreenWidth;
    static const float                ScreenHeight;
    static const float                WidthRatio;
    static const float                HeightRatio;

private:
    std::shared_ptr<IoStepBatch>             ioCurrent;
    std::deque<std::shared_ptr<IoStepBatch>> ioQueue;

    duration<float, std::milli>       timeDiff;
    high_resolution_clock::time_point nowTime;
    high_resolution_clock::time_point lastTimePressed[300] = { high_resolution_clock::now() };
    bool                              pressed[300] = { 0 };
};

class IoDelay : public IoStep {

public:
    IoDelay(float delayMillis) {
        this->delayMillis = delayMillis;
    }

    void Start() {
        startTime = high_resolution_clock::now();
    }

    bool Update() {
        timeDiff = high_resolution_clock::now() - startTime;
        if (timeDiff.count() < delayMillis)
            return false;
        return true;
    }

    float                             delayMillis;
    duration<float, std::milli>       timeDiff;
    high_resolution_clock::time_point startTime;
};

class IoPressKey : public IoStep {

public:
    IoPressKey(HKey key) {
        this->key = key;
    }

    bool Update() {
        DirectInputHook::QueueKey(key, true);
        return true;
    }

    HKey key;
};

class IoReleaseKey : public IoStep {

public:
    IoReleaseKey(HKey key) {
        this->key = key;
    }

    bool Update() {
        DirectInputHook::QueueKey(key, false);
        return true;
    }

    HKey key;
};

class IoSpoofMouse : public IoStep {

public:
    IoSpoofMouse(Vector2 pos) {
        FakeMouse::FakePositionGetter = [pos] { return pos; };
    }

    IoSpoofMouse(std::function<Vector2()>& getter) {
        FakeMouse::FakePositionGetter = getter;
    }

    bool Update() {
        FakeMouse::Enabled = true;
        return true;
    }
};

class IoUnspoofMouse : public IoStep {

public:
    bool Update() {
        FakeMouse::Enabled = false;
        return true;
    }
};

class IoPressMouse : public IoStep {

public:
    IoPressMouse(ClickType type, std::function<bool()> condition = nullptr) {
        this->type = type;
        this->condition = condition;
    }

    bool Update() {
        if (condition && !condition())
            return true;

        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = (type == ClickType::CT_LEFT_CLICK ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);
        SendInput(1, &input, sizeof(INPUT));
        return true;
    }

    ClickType type;
    std::function<bool()> condition;
};

class IoReleaseMouse : public IoStep {

public:
    IoReleaseMouse(ClickType type, std::function<bool()> condition = nullptr) {
        this->type = type;
        this->condition = condition;
    }

    bool Update() {
        if (condition && !condition())
            return true;

        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = (type == ClickType::CT_LEFT_CLICK ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);
        SendInput(1, &input, sizeof(INPUT));

        return true;
    }

    ClickType type;
    std::function<bool()> condition;
};

class IoBlockInput : public IoStep {

public:

    bool Update() {
        BlockInput(TRUE);
        return true;
    }
};

class IoUnBlockInput : public IoStep {

public:

    bool Update() {
        BlockInput(FALSE);
        return true;
    }
};

#endif //ASYLLUM_CONTROLLER_H
