//
// Created by XaDanX on 12/1/2022.
//

#include "ObjectBase.h"
#include "../Locator/Locator.h"
#include "../Helpers/StringUtils.h"

UnitInfo* ObjectBase::GetUnitInfo() {
    std::string fixedName(StringUtils::ToLower(this->name));
    auto unitInfo = locator->GetGameData()->GetUnitInfoByName(fixedName);
    return unitInfo;
}
