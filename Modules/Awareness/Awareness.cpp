//
// Created by XaDanX on 12/10/2022.
//

#include "Awareness.h"
#include "../../Asyllum/Core/Locator/Locator.h"
#include "SpellTracker/SpellTracker.h"

void Awareness::OnTick() {
    for (auto hero : locator->GetObjectManager()->GetHeroList()) {
        spellTracker->DrawSpells(hero);

        if (lastSeen && !hero->IsLocalPlayer() && !hero->IsAllyTo<Hero *>(locator->GetObjectManager()->GetLocalPlayer()) && !(hero->dead % 2) && !hero->visibility) {
            auto hero2d = locator->GetEngine()->WorldToScreen(hero->position);
            std::string iconName(StringUtils::ToLower(hero->name.str()));
            iconName.append(XorStr("_square"));
            auto icon = locator->GetTextureManager()->GetTexture(iconName);

            if (icon == nullptr) {
                iconName.append(XorStr("_0"));
            }
            if (icon) {
                ImGui::GetBackgroundDrawList()->AddImageRounded(locator->GetTextureManager()->GetTexture(iconName),
                                                                ImVec2(hero2d.x, hero2d.y),
                                                                ImVec2(hero2d.x + 64, hero2d.y + 64), ImVec2(0, 0),
                                                                ImVec2(1, 1), ImColor(255, 255, 255, 100), 60);

            }
            locator->GetRenderer()->Text({hero2d.x + 32, hero2d.y + 32}, hero->name.c_str(), ImColor(255, 255, 255, 255));
        }

        if (!hero->IsLocalPlayer() && !hero->IsAllyTo<Hero *>(locator->GetObjectManager()->GetLocalPlayer()) && !(hero->dead % 2)) {
            auto target2d = locator->GetEngine()->WorldToScreen(hero->position);
            if (this->traceLines &&  locator->GetObjectManager()->GetLocalPlayer()->DistanceTo<Hero*>(hero) < 7000 && locator->GetObjectManager()->GetLocalPlayer()->DistanceTo<Hero*>(hero) > 650) {

                auto scaledPointStart = hero->position.clone().sub(locator->GetObjectManager()->GetLocalPlayer()->position);
                auto scaledPointNorm = scaledPointStart.normalize();

                auto scaledPoint = scaledPointNorm.clone().add(scaledPointNorm.clone().scale(10 * 58));
                auto scaledPointText = scaledPointNorm.clone().add(scaledPointNorm.clone().scale(10 * 54));
                scaledPoint = locator->GetObjectManager()->GetLocalPlayer()->position.clone().add(scaledPoint);
                scaledPointText = locator->GetObjectManager()->GetLocalPlayer()->position.clone().add(scaledPointText);
                auto scaledPoint2d = locator->GetEngine()->WorldToScreen(scaledPoint);
                auto scaledPointText2d = locator->GetEngine()->WorldToScreen(scaledPointText);


                if (hero->visibility) {

                    locator->GetRenderer()->Text({scaledPointText2d.x, scaledPointText2d.y}, std::to_string((int)locator->GetObjectManager()->GetLocalPlayer()->DistanceTo<Hero*>(hero)).c_str(), ImColor(3, 252, 252, 255));
                    locator->GetRenderer()->Text({scaledPointText2d.x, scaledPointText2d.y + 12}, hero->name.c_str(), ImColor(3, 252, 252, 255));

                    ImGui::GetBackgroundDrawList()->AddLine({scaledPoint2d.x, scaledPoint2d.y},
                                                            ImVec2(target2d.x, target2d.y), ImColor(255, 255, 255, 255),
                                                            1);

                } else {

                    locator->GetRenderer()->Text({scaledPointText2d.x, scaledPointText2d.y}, std::to_string((int)locator->GetObjectManager()->GetLocalPlayer()->DistanceTo<Hero*>(hero)).c_str(), ImColor(3, 252, 252, 255));
                    locator->GetRenderer()->Text({scaledPointText2d.x, scaledPointText2d.y + 12}, hero->name.c_str(), ImColor(3, 252, 252, 255));


                    ImGui::GetBackgroundDrawList()->AddLine({scaledPoint2d.x, scaledPoint2d.y},
                                                            ImVec2(target2d.x, target2d.y), ImColor(255, 150, 150, 255),
                                                            1);
                }
            }
        }


        if (enemyRanges && hero->IsAlive() && hero->visibility && hero->IsOnScreen(300, 300) && !hero->IsLocalPlayer() && !hero->IsAllyTo<Hero *>(locator->GetObjectManager()->GetLocalPlayer())) {
            locator->GetRenderer()->DrawCircleAt(hero->position, hero->attackRange + hero->GetUnitInfo()->gameplayRadius,
                                                 false, 100, ImColor(255, 255, 255, 255), 1);
        }

        if (playerRanges && hero->IsLocalPlayer() && hero->IsAlive() && hero->IsOnScreen(300, 300)) {
            locator->GetRenderer()->DrawCircleAt(hero->position, hero->attackRange + hero->GetUnitInfo()->gameplayRadius,
                                                 false, 100, ImColor(255, 255, 255, 255), 1);
        }



    }
    wardTracker->DrawWards();

}

void Awareness::OnLoad() {

}

void Awareness::OnGui() {
    ImGui::BeginTabBar(XorStr("AwarenessSettings").c_str());

    if (ImGui::BeginTabItem(XorStr("Ranges").c_str())) {
        ImGui::Checkbox(XorStr("Draw player ranges").c_str(), &this->playerRanges);
        ImGui::Checkbox(XorStr("Draw enemy ranges").c_str(), &this->enemyRanges);
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(XorStr("Trackers").c_str())) {
        ImGui::Checkbox(XorStr("Trace lines").c_str(), &this->traceLines);
        ImGui::Checkbox(XorStr("Last seen position").c_str(), &this->lastSeen);
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem(XorStr("SpellTracker").c_str())) {
        spellTracker->DrawGui();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem(XorStr("VisionTracker").c_str())) {
        wardTracker->DrawGui();
        ImGui::EndTabItem();
    }


    ImGui::EndTabBar();


}
