//
// Created by XaDanX on 3/16/2023.
//

#include "BetterEvade.h"
#include "../../Asyllum/Core/Data/GameKeybind.h"


void BetterEvade::OnTick() {
    spellDetector->Update();
    StartEvading();
    if (locator->GetEngine()->GetProcessorTime() > evadeTime) {
        auto pos = GetBestEvadePos();
        if (pos.x != 0) {
            evadePos = pos;
            evadeTime = locator->GetEngine()->GetProcessorTime() + 3000;
        }

    }

    if (evadePos.x != 0 && evadePos.z != 0) {
        input.IssueClickAt(CT_RIGHT_CLICK, [this] { return locator->GetEngine()->WorldToScreen(evadePos); },
                           GameKeybind::TargetChampionsOnly);
    }
    if (locator->GetEngine()->GetProcessorTime() > evadeTime) {
        evadePos = {0, 0, 0};
    }

    locator->GetRenderer()->DrawRiotCircle(evadePos, 80, ImColor(255, 0, 0, 255), true);




}


void BetterEvade::OnGui() {

}

Vector3 BetterEvade::GetMovePath() {
    if (!locator->GetObjectManager()->GetLocalPlayer()->GetAiManager()->isMoving)
        return locator->GetObjectManager()->GetLocalPlayer()->position;
    return locator->GetObjectManager()->GetLocalPlayer()->GetAiManager()->endPath.clone();
}

std::vector<Vector3> BetterEvade::FindIntersections(Geometry::Polygon poly, Vector3 p1, Vector3 p2)
{
    std::vector<Vector3>intersections;
    for (size_t i = 0; i < poly.points.size(); ++i)
    {
        auto startPos = poly.points[i];
        auto endPos = poly.points[(i == poly.points.size() - 1) ? 0 : i + 1];
        auto temp = startPos.intersection(endPos, p1, p2);
        if (temp.x != 0)
            intersections.emplace_back(temp);
    }
    return intersections;
}

void BetterEvade::StartEvading() {
    auto player = locator->GetObjectManager()->GetLocalPlayer();
    if (!spellDetector->detectedSpells.empty()) {
        auto movePath = GetMovePath();
        heroPos = player->position.clone();

        if (movePath.x != 0 && !evading) {
            std::vector<Vector3> ints;
            for (auto spell : spellDetector->detectedSpells) {

                auto poly = spell.path;
                //if (poly.IsInside(heroPos)) {
                //locator->GetConsole()->Print("")
                    ints = FindIntersections(poly, heroPos, movePath);
                //}
            }

            if (!ints.empty()) {
                std::sort(ints.begin(), ints.end(), [&](Vector3 const& a, Vector3 const& b)
                {
                    return heroPos.distance_squared(a) < heroPos.distance_squared(b);
                });

                for (auto i : ints) {
                    locator->GetRenderer()->DrawRiotCircle(i, 30, ImColor(255, 255, 0, 255), true);
                }

                auto movePos = PrependVector(heroPos, ints.front(), player->GetUnitInfo()->gameplayRadius * 2);
                locator->GetRenderer()->DrawRiotCircle(movePos, 30, ImColor(255, 0, 0, 255), true);
                input.IssueClickAt(CT_RIGHT_CLICK, [movePos] {return locator->GetEngine()->WorldToScreen(movePos);}, GameKeybind::TargetChampionsOnly);
            }
        }
    }
}

Vector3 BetterEvade::PrependVector(Vector3 pos1, Vector3 pos2, float dist) {
    auto norm = pos2.sub(pos1).normalize();
    return pos1.add(norm.mult(dist));
}

bool BetterEvade::IsDangerous(Vector3 pos) {
    for (auto spell : spellDetector->detectedSpells) {
        if (spell.path.IsInside(pos)) {
            return true;
        }
    }
    return false;
}

Vector3 BetterEvade::GetBestEvadePos() {
    std::list<Vector3> points;
    std::list<Geometry::Polygon> polygons;

    for (auto spell : spellDetector->detectedSpells) {
        polygons.push_back(spell.path);
    }

    std::list<Geometry::Polygon> dangerPolygons = polygons;

    for (Geometry::Polygon poly : dangerPolygons) {
        for (size_t i = 0; i < poly.points.size(); ++i) {
            auto startPos = poly.points[i];
            auto endPos = poly.points[(i == poly.points.size() - 1) ? 0 : i + 1];

            auto my_position = heroPos;
            auto original = my_position.segment_point(startPos, endPos);

            auto distSqr = original.distance_squared(my_position);
            if (distSqr > (float)360000) {
                auto side_distance = endPos.distance_squared(startPos);
                auto direction = endPos.sub(startPos).normalize();
                int step = (distSqr < 200 * 200 && side_distance > 90 * 90) ? 120 : 0;

                for (int j = -step; j <= step; j++) {
                    auto candidate = original.add(direction.mult(j * 20));
                    Vector3 extended = heroPos.append(heroPos, candidate, 80); // bounding radius
                    candidate = heroPos.append(heroPos, candidate, 5);

                    if (!IsDangerous(candidate)) {
                        points.push_back(candidate);
                    }
                }
            }

        }
    }

    for (auto i : points) {
        locator->GetRenderer()->DrawRiotCircle(i, 30, ImColor(255, 255, 0, 255), true);
    }

    if (points.size() > 0)
    {
        for (auto i : points) {
            locator->GetRenderer()->DrawRiotCircle(i, 30, ImColor(255, 255, 0, 255), true);
        }
        Vector3 tempMyHeroPos = heroPos;
        float tempRB = 190;
        Vector3 tempMPos = locator->GetEngine()->GetHudInstance()->mouseInstance->cursorWorldPos;

        try {

            points.sort([&tempMyHeroPos, &tempRB, &tempMPos, this](Vector3 const& a, Vector3 const& b)
                        {
                            Vector3 mPos = tempMyHeroPos.extend(tempMPos, tempRB);
                            return a.distance_squared(heroPos) < b.distance_squared(heroPos);
                        });
        } catch (...) {}
        //return points.front();
        auto p = heroPos.append(heroPos, points.front(), 80);
        return p;
    }
    return Vector3(0, 0, 0);
}
