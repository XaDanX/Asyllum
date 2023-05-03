//
// Created by XaDanX on 12/12/2022.
//

#ifndef ASYLLUM_HUDINSTANCE_H
#define ASYLLUM_HUDINSTANCE_H

#include "../../Globals/Globals.h"
#include "../../Globals/Offsets.h"
#include "../../Math/Vector.h"

class CameraInstance {
public:
    union {
        DEFINE_MEMBER_N(Vector3, cameraPosition, Offsets::CameraInstance::CameraPosition);
        DEFINE_MEMBER_N(float, zoomVelocity, Offsets::CameraInstance::ZoomVelocity);
        DEFINE_MEMBER_N(float, zoomSmoothing, Offsets::CameraInstance::ZoomSmoothing);
        DEFINE_MEMBER_N(float, zoom, Offsets::CameraInstance::Zoom);
    };
};

class MouseInstance {
public:
    union {
        DEFINE_MEMBER_N(Vector3, cursorWorldPos, Offsets::MouseInstance::CursorWorldPos);
        DEFINE_MEMBER_N(Vector3, CursorWorldPosHoveredObj, Offsets::MouseInstance::CursorWorldPosHoveredObj);
    };

};

class HudInstance {
public:
    union {
        DEFINE_MEMBER_N(CameraInstance*, cameraInstance, Offsets::HudInstance::CameraInstance);
        DEFINE_MEMBER_N(MouseInstance*, mouseInstance, Offsets::HudInstance::MouseInstance);
        DEFINE_MEMBER_N(uint16_t, focus, Offsets::HudInstance::Focus);
    };

    bool IsFocused() const {
        return focus == (uint16_t)1;
    }
};


#endif //ASYLLUM_HUDINSTANCE_H
