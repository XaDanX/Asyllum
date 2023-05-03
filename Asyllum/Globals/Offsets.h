#ifndef ASYLLUM_OFFSETS_H
#define ASYLLUM_OFFSETS_H

#include <iostream>
#include <cstdint>

namespace Offsets {

    namespace Functions {
        constexpr std::uint64_t IsNotWall{0x18d4d88};/*compare flags*/
    }

    namespace SpellBook {  /*always the same*/
        constexpr std::uint64_t Level{0x28};
        constexpr std::uint64_t ReadyTime{0x30};
        constexpr std::uint64_t SpellInfo{0x130};
        constexpr std::uint64_t SpellData{0x60};
        constexpr std::uint64_t SpellName{0x80};
    }

    namespace Game {
        constexpr std::uint64_t HudInstance{0x20DD7D8}; //UPDATED
        constexpr std::uint64_t ViewProjMatrices{0x51D4000}; //UPDATED
        constexpr std::uint64_t LocalPlayer{0x51945B8}; //UPDATED
        constexpr std::uint64_t GameTime{0x5188500}; //UPDATED
        constexpr std::uint64_t ObjectManager{0x20DD7C8}; //UPDATED
        constexpr std::uint64_t Renderer{0x51DC418}; //UPDATED
    }

    namespace MiniMap {
        constexpr std::uint64_t MiniMapObject {0x5188568}; //UPDATED
        constexpr std::uint64_t MiniMapHud {0x320}; //UPDATED
        constexpr std::uint64_t MiniMapHudPos {0x60}; //UPDATED
        constexpr std::uint64_t MiniMapHudSize {0x68}; //UPDATED
    }

    namespace HudInstance {
        constexpr std::uint64_t CameraInstance{0x18};
        constexpr std::uint64_t MouseInstance{0x28};
        constexpr std::uint64_t Focus{0xB8};
    }

    namespace CameraInstance {
        constexpr std::uint64_t CameraPosition{0x188};
        constexpr std::uint64_t ZoomVelocity{0x2B4};
        constexpr std::uint64_t ZoomSmoothing{0x2B8};
        constexpr std::uint64_t Zoom{0x2BC};
    }
    namespace MouseInstance {
        constexpr std::uint64_t CursorWorldPos{0x2C};
        constexpr std::uint64_t CursorWorldPosHoveredObj{0x20};
    }

    namespace Templates {
        constexpr std::uint64_t HeroTemplate{0x20d0fa0}; 
        constexpr std::uint64_t MinionTemplate{0x392b8a0}; 
        constexpr std::uint64_t TurretTemplate{0x5179250};
        constexpr std::uint64_t MissileTemplate{0x518aba0};
    }

    namespace Renderer {
        constexpr std::uint64_t Width{0xC}; 
        constexpr std::uint64_t Height{0x10}; 
    }

    namespace GameObject {

        constexpr std::uint64_t CharacterIntermediate {0x19C0};

        constexpr std::uint64_t Index{0x10};
        constexpr std::uint64_t Team{0x3C};
        constexpr std::uint64_t PlayerName{0xB8};
        constexpr std::uint64_t NetworkId{0xC8};
        constexpr std::uint64_t Position{0x220};
        constexpr std::uint64_t Visibility{0x310};
        constexpr std::uint64_t SpawnCount{0x288};
        constexpr std::uint64_t Mana{0x29C};
        constexpr std::uint64_t MaxMana{0x2AC};
        constexpr std::uint64_t Dead{0x274};
        constexpr std::uint64_t Health{0x1058};
        constexpr std::uint64_t MaxHealth{0x1058}; 
        constexpr std::uint64_t Name{0x3898}; 
        constexpr std::uint64_t AttackRange{CharacterIntermediate + 0x390}; 
        constexpr std::uint64_t Targetable{0xEB4};
        constexpr std::uint64_t SpellCast{0x2A00};
        constexpr std::uint64_t SpellBook{0x2718};
        constexpr std::uint64_t BuffManager{0x2820};
        constexpr std::uint64_t AttackSpeedMultiplier{CharacterIntermediate + 0x198};
        constexpr std::uint64_t Scale{0x1838}; 
        constexpr std::uint64_t ActionState{0x111C};
        constexpr std::uint64_t CharacterData{0x2B6C};
        constexpr std::uint64_t MovementSpeed{CharacterIntermediate + 0x360}; 

    }

    namespace SpellCast {
        constexpr std::uint64_t SpellData{0x8}; 
        constexpr std::uint64_t SpellName{0x28};  
        constexpr std::uint64_t SpellSlot{0x10}; 
        constexpr std::uint64_t CastTime{0x188}; 
        constexpr std::uint64_t StartPos{0xAC}; 
        constexpr std::uint64_t EndPos{0xB4}; 
        constexpr std::uint64_t EndPosAlt{0xB4};
        constexpr std::uint64_t StartTime{0x14}; 
        constexpr std::uint64_t EndTime{0x170}; 
    }

    namespace BuffManager {
        constexpr std::uint64_t BuffStart{0x10};
        constexpr std::uint64_t BuffEnd{0x14};
        constexpr std::uint64_t BuffType{0x04};
        constexpr std::uint64_t BaseBuffEntry{0x8};
        constexpr std::uint64_t StartTime{0xC};
        constexpr std::uint64_t EndTime{0x10};
        constexpr std::uint64_t Stacks{0x74};
        constexpr std::uint64_t Name{0x4};

    }

    namespace AiManager {
        constexpr std::uint64_t ServerPosition{0x2EC};
        constexpr std::uint64_t NavigationArray{0x2E8}; 
        constexpr std::uint64_t NavigationArrayLength{NavigationArray + 8}; 
        constexpr std::uint64_t StartPath{0x2D0};
        constexpr std::uint64_t EndPath{0x2DC};
        constexpr std::uint64_t CurrentSegment{0x2C0};
        constexpr std::uint64_t IsDashing{0x320};
        constexpr std::uint64_t DashSpeed{0x1F8};
        constexpr std::uint64_t IsMoving{0x2BC};

    }

    namespace Missile {
        constexpr std::uint64_t ObjectEntry {0x28};
        constexpr std::uint64_t SrcIndex {0x0370}; 
        constexpr std::uint64_t DestIndex {0x31C};
        constexpr std::uint64_t StartPos {0x038C}; 
        constexpr std::uint64_t CurrentPos {0x510}; 
        constexpr std::uint64_t EndPos {0x0398}; 
        constexpr std::uint64_t MissileInfo {0x02E8}; 
        constexpr std::uint64_t Slot {0x4908};
        constexpr std::uint64_t Name {0x28}; 
    }

    namespace CharacterData {
        constexpr std::uint64_t Hash{0x10};
    }
}
#endif ASYLLUM_OFFSETS_H
