//
// Created by XaDanX on 4/30/2023.
//

#include "Awareness.h"
#include "../../Asyllum/Core/Managers/EventManager/Event.h"


struct LastPositionInfo {
    Vector3 lastPos;
    float time;
};


namespace AwarenessEvents {

    std::map<BYTE, LastPositionInfo> lastPos;


    void OnSpellCasted(Event::OnSpellCast args) {
        if (!args.caster->visibility) {
            LastPositionInfo info;
            info.time = locator->GetEngine()->GameTime();
            info.lastPos = args.spell.startPos;
            lastPos[args.caster->index] = info;
        }

    }
}


void Awareness::OnTick() {

    auto bg = ImGui::GetBackgroundDrawList();
    auto player = locator->GetObjectManager()->GetLocalPlayer();

    auto time = locator->GetEngine()->GameTime();


    for (auto camp : locator->GetObjectManager()->GetMinionList()) {
        if (!camp->IsMinion() || camp->IsWard())
            continue;
        if (camp->team != 100 && camp->team != 200) {
            if (!camp->visibility) {
                camp->visibility = false;
                camp->visibility = true;
            }

            auto pos = locator->GetEngine()->WorldToMinimap(camp->position);


            if (camp->IsAlive()) {
                bg->AddCircle({pos.x, pos.y}, 4, ImColor(0, 255, 0, 100), 12, 1);
            } else {
                bg->AddCircle({pos.x, pos.y}, 4, ImColor(255, 0, 0, 100), 12, 1);
            }

        }


    }


    for (auto hero : locator->GetObjectManager()->GetHeroList()) {

        if (hero->team == player->team)
            continue;

        LastPositionInfo info;

        auto it = AwarenessEvents::lastPos.find(hero->index);


        if (hero->visibility) {
            info.lastPos = hero->position;
            info.time = time;
            AwarenessEvents::lastPos[hero->index] = info;
        } else {
            if (hero->position.x != it->second.lastPos.x || hero->position.z != it->second.lastPos.z) {
                info.lastPos = hero->position;
                info.time = time;
                AwarenessEvents::lastPos[it->first] = info;
            }
        }


        if (!hero->visibility) {
            auto pos = locator->GetEngine()->WorldToMinimap(it->second.lastPos);

            if (hero->IsOnScreen()) {
                auto pos2d = locator->GetEngine()->WorldToScreen(it->second.lastPos);
                locator->GetRenderer()->DrawCircleAt(it->second.lastPos, 60, true, 50, ImColor(255, 255, 0, 180), 2);
                locator->GetRenderer()->Text({pos2d.x, pos2d.y + 40}, hero->name.c_str(), ImColor(255, 255, 0, 255));
                locator->GetRenderer()->Text({pos2d.x, pos2d.y + 55}, std::string(
                                                     XorStr("Last Visible: ").str() + std::to_string(time - it->second.time)).c_str(),
                                             ImColor(255, 255, 0, 255));
            }
            bg->AddCircle({pos.x, pos.y}, 10, ImColor(255, 255, 0, 190), 12, 2);
            locator->GetRenderer()->Text({pos.x, pos.y + 17}, hero->name.c_str(), ImColor(255, 255, 0, 190));
        }
    }




}

void Awareness::OnGui() {

}

void Awareness::OnLoad() {
    locator->GetEventManager()->Subscribe<Event::OnSpellCast>(&AwarenessEvents::OnSpellCasted);

    auto player = locator->GetObjectManager()->GetLocalPlayer();

    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        if (hero->team != player->team) {
            if (!AwarenessEvents::lastPos.contains(hero->index)) {
                LastPositionInfo info;
                info.lastPos = hero->position;
                info.time = locator->GetEngine()->GameTime();

                AwarenessEvents::lastPos[hero->index] = info;
            }
        }
    }
}
