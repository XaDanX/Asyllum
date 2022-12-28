//
// Created by XaDanX on 12/13/2022.
//

#include "SpellTracker.h"

void SpellTracker::DrawSpell(SpellSlot *spellSlot, ImVec2 pos) {
    if (!Utils::IsValid(spellSlot)) {
        return;
    }
    std::string iconName = XorStr("viegosoul_square").c_str();

    auto info = spellSlot->GetSpellInfo();
    if (Utils::IsValid(info)) {
        if (info->icon.length() > 3) {
            iconName = info->icon;
        }
    }

    ImGui::GetBackgroundDrawList()->AddImageRounded(locator->GetTextureManager()->GetTexture(iconName),
                                                    ImVec2(pos.x, pos.y), ImVec2(pos.x + 24, pos.y + 24), ImVec2(0, 0),
                                                    ImVec2(1, 1), (spellSlot->IsReady() && spellSlot->level > 0) ? ImColor(255, 255, 255, 255) : ImColor(55, 50, 50, 255), 10);
    if (!spellSlot->IsReady()) {
        locator->GetRenderer()->Text(Vector2(pos.x + 12, pos.y + 12),
                                     std::to_string(spellSlot->GetCooldown()).c_str(),
                                     ImVec4(255, 255, 255, 255));
    }
    pos.y += 28;
    pos.x += 5;
    for (int level = 0; level < spellSlot->level; level++) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(pos, 2, ImColor(240, 171, 10, 255));
        pos.x += 4;
    }
}

void SpellTracker::DrawSpells(Hero *hero) {
    if (hero->IsDummy()) return;
    if (!hero->visibility) return;
    if (!hero->IsAlive()) return;
    if (hero->IsAllyTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer())) return;
    if (!hero->IsOnScreen()) return;

    auto pos = hero->GetHealthBarPosition();
    pos.x += 24;
    pos.y -= 2.0;
    auto q_spell = hero->GetSpellSlotById(0);
    auto w_spell = hero->GetSpellSlotById(1);
    auto e_spell = hero->GetSpellSlotById(2);
    auto r_spell = hero->GetSpellSlotById(3);
    if (Utils::IsValid(q_spell) && Utils::IsValid(w_spell) && Utils::IsValid(e_spell) && Utils::IsValid(r_spell)) {
        DrawSpell(q_spell, ImVec2(pos.x, pos.y));
        pos.x += 25;
        DrawSpell(w_spell, ImVec2(pos.x, pos.y));
        pos.x += 25;
        DrawSpell(e_spell, ImVec2(pos.x, pos.y));
        pos.x += 25;
        DrawSpell(r_spell, ImVec2(pos.x, pos.y));
    }
}
