//
// Created by XaDanX on 1/28/2023.
//
#include "Controller.h"
#include <windows.h>

const float InputController::ScreenHeight = (float)::GetSystemMetrics(SM_CYSCREEN) - 1;
const float InputController::ScreenWidth  = (float)::GetSystemMetrics(SM_CXSCREEN) - 1;

const float InputController::HeightRatio = 65535.0f / ScreenHeight;
const float InputController::WidthRatio  = 65535.0f / ScreenWidth;

bool InputController::IsDown(HKey key)
{
    int virtualKey = GetVirtualKey(key);
    if (virtualKey == 0)
        return false;

    return GetAsyncKeyState(virtualKey);
}

bool InputController::WasPressed(HKey key, float lastMillis)
{
    int virtualKey = GetVirtualKey(key);
    if (virtualKey == 0)
        return false;

    nowTime = high_resolution_clock::now();
    timeDiff = nowTime - lastTimePressed[virtualKey];
    if (pressed[virtualKey]) {

        if (timeDiff.count() > lastMillis)
            pressed[virtualKey] = false;
        return false;
    }

    bool keyDown = GetAsyncKeyState(virtualKey) & 0x8000;
    if (keyDown) {
        lastTimePressed[virtualKey] = high_resolution_clock::now();
        pressed[virtualKey] = true;
        return true;
    }

    return false;
}

Vector2 InputController::GetMouseCursor()
{
    POINT pos;
    GetCursorPos(&pos);
    return { (float)pos.x, (float)pos.y };
}

void InputController::SetMouseCursor(const Vector2 & position)
{
    float fScreenWidth  = (float)(GetSystemMetrics(SM_CXSCREEN) - 1);
    float fScreenHeight = (float)(GetSystemMetrics(SM_CYSCREEN) - 1);
    float fx = position.x * (65535.0f / fScreenWidth);
    float fy = position.y * (65535.0f / fScreenHeight);

    INPUT    Input = { 0 };
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void InputController::UpdateIssuedOperations()
{
    if (ioCurrent == nullptr) {
        if (ioQueue.empty())
            return;

        ioCurrent = ioQueue.front();
        ioCurrent->Start();
        ioQueue.pop_front();
    }

    if (ioCurrent->Update()) {
        ioCurrent = nullptr;
    }
}

void InputController::IssuePressKey(HKey key)
{
    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch(
                    {
                            std::shared_ptr<IoStep>(new IoPressKey(key)),
                            std::shared_ptr<IoStep>(new IoDelay(5.f)),
                            std::shared_ptr<IoStep>(new IoReleaseKey(key))
                    }, IO_PRESS_KEY
            ))
    );
}

void InputController::IssuePressKeyAt(HKey key, std::function<Vector2()> posGetter) {

    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoSpoofMouse(posGetter)),
                                                                 std::shared_ptr<IoStep>(new IoPressKey(key)),
                                                                 std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                 std::shared_ptr<IoStep>(new IoReleaseKey(key)),
                                                                 std::shared_ptr<IoStep>(new IoDelay(15.f)),
                                                                 std::shared_ptr<IoStep>(new IoUnspoofMouse())
                                                         }, IO_PRESS_KEY_AT))
    );
}

void InputController::IssueClick(ClickType type, HKey withKeyHold)
{
    std::shared_ptr<IoStepBatch> batch;
    if (withKeyHold != NO_KEY) {
        batch = std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                     std::shared_ptr<IoStep>(new IoPressKey(withKeyHold)),
                                                                     std::shared_ptr<IoStep>(new IoPressMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoReleaseMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoReleaseKey(withKeyHold)),
                                                             }, IO_CLICK));
    }
    else {
        batch = std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                     std::shared_ptr<IoStep>(new IoPressMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoReleaseMouse(type))
                                                             }, IO_CLICK));
    }

    PushIoBatch(batch);
}

void InputController::IssueClickAt(ClickType type, std::function<Vector2()> posGetter, HKey withKeyHold)
{
    std::shared_ptr<IoStepBatch> batch;
    if (withKeyHold != NO_KEY) {
        batch = std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                     std::shared_ptr<IoStep>(new IoPressKey(withKeyHold)),
                                                                     std::shared_ptr<IoStep>(new IoSpoofMouse(posGetter)),
                                                                     std::shared_ptr<IoStep>(new IoPressMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoReleaseMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoUnspoofMouse()),
                                                                     std::shared_ptr<IoStep>(new IoReleaseKey(withKeyHold)),
                                                             }, IO_CLICK_AT));
    }
    else {
        batch = std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                     std::shared_ptr<IoStep>(new IoSpoofMouse(posGetter)),
                                                                     std::shared_ptr<IoStep>(new IoPressMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoReleaseMouse(type)),
                                                                     std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                     std::shared_ptr<IoStep>(new IoUnspoofMouse())
                                                             }, IO_CLICK_AT));
    }

    PushIoBatch(batch);
}

/*
void InputController::IssueClickUnit(ClickType type, const GameUnit& unit)
{
    int unitNetId = unit.networkId;

    std::function<Vector2()> posGetter = [unitNetId]() {
        auto find = Valkyrie::CurrentGameState->objectCache.find(unitNetId);
        if (find == Valkyrie::CurrentGameState->objectCache.end())
            return Vector2(0.f, 0.f);
        auto& unit = find->second;

        return Valkyrie::CurrentGameState->renderer.WorldToScreen(unit->pos);
    };

    std::function<bool()> clickCondition = [unitNetId]() {
        auto find = Valkyrie::CurrentGameState->objectCache.find(unitNetId);
        if (find == Valkyrie::CurrentGameState->objectCache.end())
            return false;
        auto unit = std::dynamic_pointer_cast<GameUnit>(find->second);
        return unit != nullptr && unit->targetable && !unit->isDead && unit->isVisible;
    };

    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoSpoofMouse(posGetter)),
                                                                 std::shared_ptr<IoStep>(new IoPressMouse(type, clickCondition)),
                                                                 std::shared_ptr<IoStep>(new IoReleaseMouse(type, clickCondition)),
                                                                 std::shared_ptr<IoStep>(new IoDelay(5.f)),
                                                                 std::shared_ptr<IoStep>(new IoUnspoofMouse())
                                                         }, IO_CLICK_UNIT))
    );
}*/

void InputController::IssueHoldKey(HKey key)
{
    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoPressKey(key))
                                                         }, IO_HOLD_KEY))
    );
}

void InputController::IssueUnholdKey(HKey key)
{
    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoReleaseKey(key))
                                                         }, IO_UNHOLD_KEY))
    );
}

void InputController::IssueUnholdKeyAt(HKey key, std::function<Vector2()> posGetter)
{
    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoSpoofMouse(posGetter)),
                                                                 std::shared_ptr<IoStep>(new IoReleaseKey(key)),
                                                                 std::shared_ptr<IoStep>(new IoDelay(10.f)),
                                                                 std::shared_ptr<IoStep>(new IoUnspoofMouse())
                                                         }, IO_UNHOLD_KEY_AT))
    );
}

void InputController::IssueDelay(float millis)
{
    PushIoBatch(
            std::shared_ptr<IoStepBatch>(new IoStepBatch({
                                                                 std::shared_ptr<IoStep>(new IoDelay(N))
                                                         }, IO_DELAY))
    );
}


int InputController::GetVirtualKey(HKey key) {
    return MapVirtualKeyA(key, MAPVK_VSC_TO_VK);

}

void InputController::PushIoBatch(std::shared_ptr<IoStepBatch> batch)
{
    /// Override if equals
    if (!ioQueue.empty() && batch->controlId == ioQueue.back()->controlId) {
        ioQueue.pop_back();
    }
    ioQueue.push_back(batch);
}

IoStepBatch::IoStepBatch(std::initializer_list<std::shared_ptr<IoStep>> initSteps, int id)
        :steps(initSteps), controlId(id), currentStep(nullptr)
{
}

void IoStepBatch::Start()
{
}

bool IoStepBatch::Update()
{
    if (currentStep == nullptr) {
        currentStep = steps.front();
        currentStep->Start();
        steps.pop();
    }

    if (currentStep->Update()) {
        currentStep = nullptr;
        return steps.empty();
    }

    return false;
}

bool IoStepBatch::operator==(const IoStepBatch & other)
{
    return this->controlId == other.controlId;
}
