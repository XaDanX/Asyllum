//
// Created by XaDanX on 12/10/2022.
//

#include "SpellTracker.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "../../Asyllum/Utils/Utils.h"

void SpellTracker::OnTick() {
    for (auto& hero : locator->GetObjectManager()->GetHeroList()) {
        if (hero->IsDummy()) continue;
        if (hero->IsAllyTo<Hero*>(locator->GetObjectManager()->GetLocalPlayer())) continue;

        auto pos = hero->GetHealthBarPosition();
        pos.x += 24;
        pos.y -= 2.5;
        auto q_spell = hero->GetSpellSlotById(0);
        auto w_spell = hero->GetSpellSlotById(1);
        auto e_spell = hero->GetSpellSlotById(2);
        auto r_spell = hero->GetSpellSlotById(3);
        if (Utils::IsValid(q_spell) && Utils::IsValid(w_spell) && Utils::IsValid(e_spell) && Utils::IsValid(r_spell)) {
            DrawSpell(std::cref(q_spell), ImVec2(pos.x, pos.y));
            pos.x += 24;
            DrawSpell(std::cref(w_spell), ImVec2(pos.x, pos.y));
            pos.x += 24;
            DrawSpell(std::cref(e_spell), ImVec2(pos.x, pos.y));
            pos.x += 24;
            DrawSpell(std::cref(r_spell), ImVec2(pos.x, pos.y));
        }
    }


}

void SpellTracker::OnLoad() {

}

void SpellTracker::OnGui() {

}

void SpellTracker::DrawSpell(SpellSlot* spellSlot, ImVec2 pos) {
        if (!Utils::IsValid(spellSlot)) {
            locator->GetConsole()->Print(XorStr("SpellSlot").c_str());
            return;
        }
        auto info = spellSlot->GetSpellInfo();
        if (!Utils::IsValid(info)) {
            locator->GetConsole()->Print(XorStr("SpellInfo | %s").c_str(), spellSlot->GetName().c_str());
            return;
        }
        std::string iconName = "twitch_q";
        if (info->icon.length() > 3) {
            iconName = info->icon;
        }
        ImGui::GetBackgroundDrawList()->AddImage(locator->GetTextureManager()->GetTexture(iconName),
        ImVec2(pos.x, pos.y), ImVec2(pos.x + 24, pos.y + 24), ImVec2(0, 0),
        ImVec2(1, 1), spellSlot->IsReady() ? ImColor(255, 255, 255, 255) : ImColor(50, 50, 20, 255));
        if (!spellSlot->IsReady()) {
            locator->GetRenderer()->Text(Vector2(pos.x + 12, pos.y + 12),
                                         std::to_string(spellSlot->GetCooldown()).c_str(),
                                         ImVec4(255, 255, 255, 255));
        }
}
