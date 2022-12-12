//
// Created by XaDanX on 12/1/2022};
//

#ifndef ASYLLUM_OFFSETS_H
#define ASYLLUM_OFFSETS_H
#include<iostream>
#include <cstdint>
namespace Offsets {

    namespace Functions {

    }

    namespace SpellBook {
        constexpr std::uint32_t Level {0x1C};
        constexpr std::uint32_t ReadyTime {0x24};
        constexpr std::uint32_t SpellInfo {0x120};
        constexpr std::uint32_t SpellData {0x40};
        constexpr std::uint32_t SpellName {0x6C};
    }

    namespace Game {
        constexpr std::uint32_t HudInstance {0x18ADAE0}; //
        constexpr std::uint32_t ViewProjMatrices {0x3170CF8 }; //
        constexpr std::uint32_t LocalPlayer{0x314A404}; //
        constexpr std::uint32_t GameTime {0x3143C44}; //
        constexpr std::uint32_t ObjectManager {0x18A6ED8};
        constexpr std::uint32_t Renderer {0x31765C0}; //
    }

    namespace HudInstance {
        constexpr std::uint32_t ZoomInstance {0xC};
    }

    namespace ZoomInstance {
        constexpr std::uint32_t TempZoom {0x260};
        constexpr std::uint32_t VisibleZoom {0x264};
        constexpr std::uint32_t InternalZoom {0x268};
    }

    namespace Templates {
        constexpr std::uint32_t HeroTemplate {0x18ADB74}; //
        constexpr std::uint32_t MinionTemplate {0x24FB1E4}; //
        constexpr std::uint32_t TurretTemplate {0x3142824}; //
    }

    namespace Renderer {
        constexpr std::uint32_t Width {0x8};
        constexpr std::uint32_t Height {0xC};
    }

    namespace GameObject {
        constexpr std::uint32_t Index {0x8};
        constexpr std::uint32_t Team {0x34};
        constexpr std::uint32_t NetworkId {0xB4};
        constexpr std::uint32_t Position {0x1DC};
        constexpr std::uint32_t Visibility {0x274};
        constexpr std::uint32_t SpawnCount {0x288};
        constexpr std::uint32_t Mana {0x29C};
        constexpr std::uint32_t MaxMana {0x2AC};
        constexpr std::uint32_t Dead {0x021C};
        constexpr std::uint32_t Health {0xE7C};
        constexpr std::uint32_t MaxHealth {0xE8C};
        constexpr std::uint32_t Name {0x2DB4};
        constexpr std::uint32_t AttackRange {0x13A4};
        constexpr std::uint32_t Targetable {0xD04};
        constexpr std::uint32_t AiManager {0x2E8C}; //
        constexpr std::uint32_t SpellBook {0x29C8}; //
    }

    namespace AiManager {
        constexpr std::uint32_t ServerPosition {0x2EC};
        constexpr std::uint32_t NavigationArray {0x1E4};
        constexpr std::uint32_t NavigationArrayLength {NavigationArray + 4};
        constexpr std::uint32_t CurrentSegment {0x1C4};




    }
}
#endif //ASYLLUM_OFFSETS_H
