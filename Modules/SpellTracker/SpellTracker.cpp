//
// Created by XaDanX on 2/2/2023.
//

#include "SpellTracker.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/Utils/Utils.h"

namespace SpellDrawing {
    void DrawSpell(Vector2 pos, SpellSlot* spellSlot) {
        auto info = spellSlot->GetSpellInfo();
        std::string iconName = XorStr("twitch_q");
        if (Utils::IsValid(info)) {
            if (info->icon.length() > 3) {
                iconName = info->icon;
            }
        }
        ImGui::GetBackgroundDrawList()->AddImageRounded(locator->GetTextureManager()->GetTexture(iconName),
                                                        ImVec2(pos.x, pos.y), ImVec2(pos.x + 24, pos.y + 24), ImVec2(0, 0),
                                                        ImVec2(1, 1), spellSlot->IsReady() ? ImColor(255, 255, 255, 255) : ImColor(50, 50, 20, 255), 10);
        if (!spellSlot->IsReady()) {
            locator->GetRenderer()->Text(Vector2(pos.x + 12, pos.y + 12),
                                         std::to_string(spellSlot->GetCooldown()).c_str(),
                                         ImVec4(255, 255, 255, 255));
        }
    }
}

void SpellTracker::OnTick() {
    auto localPlayer = locator->GetObjectManager()->GetLocalPlayer();
    for (auto& hero : locator->GetObjectManager()->GetHeroList()) {
        if (hero->IsDummy()) continue;
        if (!hero->visibility) continue;
        if (!hero->IsAlive()) continue;
        //if (hero->IsAllyTo<Hero*>(localPlayer)) continue;
        if (!hero->IsOnScreen()) continue;

        auto pos = hero->GetHealthBarPosition();
        pos.y += 4;
        pos.x += 24;

        auto q_spell = hero->GetSpellSlotById(0);
        auto w_spell = hero->GetSpellSlotById(1);
        auto e_spell = hero->GetSpellSlotById(2);
        auto r_spell = hero->GetSpellSlotById(3);
        auto d_spell = hero->GetSpellSlotById(4);
        auto f_spell = hero->GetSpellSlotById(5);
        if (Utils::IsValid(q_spell) && Utils::IsValid(w_spell) && Utils::IsValid(e_spell) && Utils::IsValid(r_spell)) {
            SpellDrawing::DrawSpell(pos, q_spell);
            pos.x += 25;
            SpellDrawing::DrawSpell(pos, w_spell);
            pos.x += 25;
            SpellDrawing::DrawSpell(pos, e_spell);
            pos.x += 25;
            SpellDrawing::DrawSpell(pos, r_spell);
        }


    }
}

void SpellTracker::OnLoad() {

}

void SpellTracker::OnGui() {

}
