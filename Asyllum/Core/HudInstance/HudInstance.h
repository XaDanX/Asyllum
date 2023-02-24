//
// Created by XaDanX on 12/12/2022.
//

#ifndef ASYLLUM_HUDINSTANCE_H
#define ASYLLUM_HUDINSTANCE_H
#include "../../Globals/Globals.h"
#include "../../Globals/Offsets.h"
#include "../../Math/Vector.h"

class ZoomInstance {
public:
    union {
        DEFINE_MEMBER_N(float, tempZoom, Offsets::ZoomInstance::TempZoom);
        DEFINE_MEMBER_N(float, visibleZoom, Offsets::ZoomInstance::VisibleZoom);
        DEFINE_MEMBER_N(float, internalZoom, Offsets::ZoomInstance::InternalZoom);
    };
};

class HudInstance {
public:
    union {
        DEFINE_MEMBER_N(ZoomInstance*, zoomInstance, Offsets::HudInstance::ZoomInstance);
        DEFINE_MEMBER_N(Vector3, cursorWorldPos, Offsets::HudInstance::CursorWorldPos);
        DEFINE_MEMBER_N(int, focus, Offsets::HudInstance::Focus);
    };

    bool IsFocused() const {
        return focus == 0x1;
    }
};



#endif //ASYLLUM_HUDINSTANCE_H
