//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_OFFSETS_H
#define ASYLLUM_OFFSETS_H
namespace Offsets {

    enum class Game : unsigned  int {
        HudInstance = 0x18a6fa4,
        ViewProjMatrices = 0x31696A0,
        LocalPlayer = 0x3143DA0,
        GameTime = 0x313D244,
        ObjectManager = 0x18A6ED8,
        Renderer = 0x316EE68
    };

    enum class Templates : unsigned int {
        HeroTemplate = 0x18A6F70
    };

    enum class Renderer : unsigned int {
        Width = 0x8,
        Height = 0xC
    };

    enum class GameObject : unsigned int {
        Index = 0x8,
        Team = 0x34,
        NetworkId = 0xB4,
        Position = 0x1DC,
        Visibility = 0x274,
        SpawnCount = 0x288,
        Mana = 0x29C,
        MaxMana = 0x2AC,
        Dead = 0x021C,
        Health = 0xE74,
        MaxHealth = 0xE84,
        Name = 0x2DAC,
        AttackRange = 0x139C,
        Targetable = 0xD04,
    };
}
#endif //ASYLLUM_OFFSETS_H
