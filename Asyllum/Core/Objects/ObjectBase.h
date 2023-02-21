//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_OBJECTBASE_H
#define ASYLLUM_OBJECTBASE_H
#include "../../Globals/Globals.h"
#include "../../Globals/Offsets.h"
#include "../../Math/Vector.h"
#include "../Types/Definitions.h"
#include "../Data/UnitInfo.h"
#include "../../Protection/XorStr.h"
#include "Hero/AiManager/AiManager.h"

enum [[maybe_unused]] HashName {
    Aatrox = 0x71097207,
    Ahri = 0xD4BD813E,
    Akali = 0x5F193A14,
    Alistar = 0x7D004170,
    Amumu = 0xC60111F1,
    Anivia = 0xE6318952,
    Annie = 0xF111751D,
    Aphelios = 0x1FC9370D,
    Ashe = 0xDA1E294F,
    AurelionSol = 0x60C9D8ED,
    Azir = 0xDD919622,
    Bard = 0xFFD1E571,
    Blitzcrank = 0x9D92842A,
    Brand = 0xE8B74EC7,
    Braum = 0xE8BE5089,
    Caitlyn = 0x601C4B58,
    Camille = 0x6FF5CBEB,
    Cassiopeia = 0x205BB971,
    Chogath = 0x3094E898,
    Corki = 0xA96B4264,
    Darius = 0x52186A32,
    Diana = 0xCDD2B60F,
    Draven = 0xC42DA22C,
    DrMundo = 0xEE5915A3,
    Ekko = 0x904BF10A,
    Elise = 0xA1490494,
    Evelynn = 0x6089E761,
    Ezreal = 0x84DCF93,
    Fiddlesticks = 0x5783643F,
    Fiora = 0x5C944E1B,
    Fizz = 0xBDE5A683,
    Galio = 0x2AC6F678,
    Gangplank = 0x33D903EF,
    Garen = 0x2DB75281,
    Gnar = 0xEEC9BE98,
    Gragas = 0xFF4BDC63,
    Graves = 0x6B2C5EE,
    Gwen = 0xF33C4B19,
    Hecarim = 0xDEFD19BB,
    Heimerdinger = 0xD77595D9,
    Illaoi = 0x90FF0372,
    Irelia = 0xE83E3148,
    Ivern = 0x804569D4,
    Janna = 0xF78D33AA,
    JarvanIV = 0xB1F7EC95,
    Jax = 0x349383C1,
    Jayce = 0xFCECDB84,
    Jhin = 0x7771D5C3,
    Jinx = 0x77F4E689,
    Kaisa = 0x39084661,
    Kalista = 0xE0DB4F6D,
    Karma = 0x3D70D070,
    Karthus = 0x72C6D76E,
    Kassadin = 0x9A84477E,
    Katarina = 0x381260D,
    Kayle = 0x40E23CBC,
    Kayn = 0xA2963DEB,
    Kennen = 0x454B9583,
    Khazix = 0xBA24D3E5,
    Kindred = 0x30E7F07D,
    Kled = 0xA7ECE380,
    KogMaw = 0xA65585E0,
    Leblanc = 0xEB2D6693,
    LeeSin = 0xBB34EE8C,
    Leona = 0x39FF4429,
    Lillia = 0xD23B335,
    Lissandra = 0x884BF49,
    Lucian = 0x97F8A01C,
    Lulu = 0xDAE94192,
    Lux = 0x35A3A7AF,
    Malphite = 0xC1DCEAAA,
    Malzahar = 0x22D7D75A,
    Maokai = 0x8EFB7D38,
    MasterYi = 0xE5A429F2,
    MissFortune = 0x1E5A725,
    MonkeyKing = 0x205D23CA,
    Mordekaiser = 0x166C307E,
    Morgana = 0xF537FDDD,
    Nami = 0x2E1EAD2F,
    Nasus = 0x9BBFEFE,
    Nautilus = 0x6C318333,
    Neeko = 0xBCE86672,
    Nidalee = 0x7DA436B4,
    Nocturne = 0xC4AADC06,
    Nunu = 0x37F8E38E,
    Olaf = 0x62042582,
    Orianna = 0x70018CA6,
    Ornn = 0x650585C3,
    Pantheon = 0xE51EFF33,
    Poppy = 0x1B74F7BA,
    Pyke = 0x96FBC243,
    Qiyana = 0xD37489D3,
    Quinn = 0x7315CE25,
    Rakan = 0x1568FA09,
    Rammus = 0xA1DBE5ED,
    RekSai = 0x57601883,
    Rell = 0xEA312DF3,
    Renekton = 0x1C0BE672,
    Rengar = 0xDD0BD0BD,
    Riven = 0x8F0E2B88,
    Rumble = 0xEADFA531,
    Ryze = 0xF4186772,
    Samira = 0xB60D0859,
    Sejuani = 0x887A3ADF,
    Senna = 0x14F7CDAF,
    Seraphine = 0xC2CB5E87,
    Sett = 0x18C000B2,
    Shaco = 0x9A1A73B8,
    Shen = 0x1A2B2B7E,
    Shyvana = 0xF45FC062,
    Singed = 0x2EDAEEE,
    Sion = 0x1AB33D75,
    Sivir = 0xD2FE8B89,
    Skarner = 0x24FE8072,
    Sona = 0x1DA69A2F,
    Soraka = 0x51A4D061,
    Swain = 0x5406B062,
    Sylas = 0xB676FA78,
    Syndra = 0x404673AB,
    TahmKench = 0xD93E9107,
    Taliyah = 0x6B3F0A56,
    Talon = 0x9DCDCAFE,
    Taric = 0xA0BC267F,
    Teemo = 0x5474A0F6,
    Thresh = 0x8E5AD89C,
    Tristana = 0x23CDE228,
    Trundle = 0x25D6A766,
    Tryndamere = 0xDE11375B,
    TwistedFate = 0xD04DE692,
    Twitch = 0xEDC9F793,
    Udyr = 0x755493E8,
    Urgot = 0xF637B92F,
    Varus = 0x28A0E785,
    Vayne = 0x2C0C5245,
    Veigar = 0x4D1B41FE,
    Velkoz = 0xDAB5F5B9,
    Vi = 0x761D73,
    Viego = 0x9662A07A,
    Viktor = 0xC04F2C7F,
    Vladimir = 0xBECBD446,
    Volibear = 0x3F2A754A,
    Warwick = 0x8CA82C2,
    Xayah = 0xB3D80D17,
    Xerath = 0x195002D0,
    XinZhao = 0xBBB6179,
    Yasuo = 0xF4E41405,
    Yone = 0x34CF7EAD,
    Yorick = 0xDA9791F5,
    Yuumi = 0x98607FF5,
    Zac = 0x3C747BBC,
    Zed = 0x3C787CB9,
    Ziggs = 0xA7103B84,
    Zilean = 0x40169635,
    Zoe = 0x3C827F30,
    Zyra = 0x6846EB6E,

    SRU_Plant_Vision = 0x4D61E805,
    SRU_Plant_Satchel = 0xE8814FF5,
    SRU_Plant_Health = 0xC3479CD9,

    SRU_Gromp = 0xD1C19B7E,
    SRU_Krug = 0xA20205E2,
    SRU_KrugMini = 0xF8123C99,
    SRU_KrugMiniMini = 0xA8245C50,
    SRU_Murkwolf = 0x621947DC,
    SRU_MurkwolfMini = 0x9A1D4493,
    SRU_Razorbeak = 0x244E9932,
    SRU_RazorbeakMini = 0xA2C97FE9,
    SRU_Blue = 0xFC505223,
    SRU_Red = 0x9CA35508,
    SRU_Dragon_Air = 0x11D34E07,
    SRU_Dragon_Earth = 0x606DCD87,
    SRU_Dragon_Elder = 0x5944E907,
    SRU_Dragon_Fire = 0x99A947D9,
    SRU_Dragon_Water = 0x27F996F4,
    SRU_RiftHerald = 0xDDAF53D2,
    SRU_Baron = 0x68AC12C9,
    Sru_Crab = 0x2DB77AF9,

    SRU_ChaosMinionMelee = 0xB87BB4C7,
    SRU_ChaosMinionRanged = 0xD86EA814,
    SRU_ChaosMinionSiege = 0x6B0C5C0,
    SRU_ChaosMinionSuper = 0x3A6B38CE,
    SRU_OrderMinionMelee = 0xD11193B9,
    SRU_OrderMinionRanged = 0xC44285A2,
    SRU_OrderMinionSiege = 0x1F46A4B2,
    SRU_OrderMinionSuper = 0x530117C0,
    HA_ChaosMinionMelee = 0xD1BBDB04,
    HA_ChaosMinionRanged = 0x35751117,
    HA_ChaosMinionSiege = 0x1FF0EBFD,
    HA_ChaosMinionSuper = 0x53AB5F0B,
    HA_OrderMinionMelee = 0xEA51B9F6,
    HA_OrderMinionRanged = 0x2148EEA5,
    HA_OrderMinionSiege = 0x3886CAEF,
    HA_OrderMinionSuper = 0x6C413DFD,
    TT_NGolem = 0x42D14DDD,
    TT_NWolf = 0x31416281,
    TT_NWraith = 0xF01EA246,
    TT_SpiderBoss = 0x469FC571,

    SRUAP_Turret_Order1 = 0xC57B1D38,
    SRUAP_Turret_Order2 = 0xC57B1D39,
    SRUAP_Turret_Order3 = 0xC57B1D3A,
    SRUAP_Turret_Order4 = 0xC57B1D3B,
    SRUAP_Turret_Chaos1 = 0x8D840146,
    SRUAP_Turret_Chaos2 = 0x8D840147,
    SRUAP_Turret_Chaos3 = 0x8D840148,
    SRUAP_Turret_Chaos4 = 0x8D840149,

    VoidSpawn = 0x91E07467,
    VoidSpawnTracer = 0x7ED0F974,
    AnnieTibbers = 0x51DAE4D4,
    ApheliosTurret = 0x369455D,
    AzirSoldier = 0x71B0E7E0,
    AzirSunDisc = 0x7EA1F0BF,
    EliseSpiderling = 0xD2607B4F,
    FizzShark = 0x3A4914A2,
    HeimerTYellow = 0xEA00055A,
    HeimerTBlue = 0xD473C020,
    IllaoiMinion = 0x81524168,
    IvernMinion = 0x3F0EF4CA,
    LissandraPassive = 0x9A74E5E,
    lulufaerie = 0x1E6EE216,
    MalzaharVoidling = 0x6C78284,
    oriannaball = 0x1E070AA5,
    shenspirit = 0xC40CEE4F,
    SyndraSphere = 0x95638AD8,
    ViegoSoul = 0x2C15826D,
    YorickGhoulMelee = 0x5783A104,
    YorickBigGhoul = 0x2B12437A,
    zedshadow = 0xF9BD6179,
    ZyraSeed = 0xA5BDBA5F,
    ZyraThornPlant = 0x34B09A22,
    ZyraGraspingPlant = 0x71DC5EAE,
    testcuberender = 0xCB00303D,
    testcuberender10vision = 0x794D3BE4,

    AniviaIceblock = 0xF5E52714,
    azirultsoldier = 0xC64FBD67,
    jarvanivwall = 0x9BFA3B3F,
    testcuberenderwcollision = 0xD661D918,
    taliyahwallchunk = 0x1DF6C46D,
    TrundleWall = 0xA2D88510,
    YorickWGhoul = 0x90E263E3,
    YorickWInvisible = 0x7D5D7FAB,

    JhinTrap = 0x1C23C910,
    NidaleeTrap = 0x135AE185,
    ShacoBox = 0x4AC2E173,
    TeemoMushroom = 0x2B2FF5AE,
    CaitlynTrap = 0xAACC89A5,
    jinxmine = 0xBE57163C,
    MaokaiSproutling = 0x5760EB27,

    GangplankBarrel = 0x7B575CB5,
    JarvanIVStandard = 0xDCC3A012,
    KalistaSpawn = 0x8231D76E,
    RekSaiTunnel = 0x315514CB,
    ThreshLantern = 0xF3AA930A,

    JammerDevice = 0x8223B6BA,
    SightWard = 0x7C1BCAD9,
    YellowTrinket = 0x40D7E043,
    BlueTrinket = 0xE20532FD,
    DominationScout = 0x97648C10,
    PerksZombieWard = 0x55814507,
    FiddleSticksEffigy = 0xEA40EFD5,
};

enum class [[maybe_unused]] ObjectTypeFlags {
    GameObject = (1 << 0),  //0x1
    NeutralCamp = (1 << 1),  //0x2
    DeadObject = (1 << 4),  //0x10
    InvalidObject = (1 << 5),  //0x20
    AIBaseCommon = (1 << 7),  //0x80
    AttackableUnit = (1 << 9),  //0x200
    AI = (1 << 10), //0x400
    Minion = (1 << 11), //0x800
    Hero = (1 << 12), //0x1000
    Turret = (1 << 13), //0x2000
    Unknown0 = (1 << 14), //0x4000
    Missile = (1 << 15), //0x8000
    Unknown1 = (1 << 16), //0x10000
    Building = (1 << 17), //0x20000
    Unknown2 = (1 << 18), //0x40000
};

enum [[maybe_unused]] CharacterState {
    CanAttack = 1,
    CanCast = 2,
    CanMove = 4,
    Immovable = 8,
    Unknownz = 16,
    IsStealth = 32,
    Taunted = 64,
    Feared = 128,
    Fleeing = 256,
    Supressed = 512,
    Asleep = 1024,
    NearSight = 2048,
    Ghosted = 4096,
    HasGhost = 8192,
    Charmed = 16384,
    NoRender = 32768,
    DodgePiercing = 131072,
    DisableAmbientGold = 262144,
    DisableAmbientXP = 524288,
    ForceRenderParticles = 65536,
    IsCombatEnchanced = 1048576,
    IsSelectable = 16777216
};

class CharacterData {
public:
    union {
        DEFINE_MEMBER_N(HashName, hash, (unsigned int)Offsets::CharacterData::Hash);
    };
};

class ObjectBase {
public:
    union {
        DEFINE_MEMBER_N(BYTE, index, (unsigned int)Offsets::GameObject::Index);
        DEFINE_MEMBER_N(short, team, (unsigned int)Offsets::GameObject::Team);
        DEFINE_MEMBER_N(int, networkId, (unsigned int)Offsets::GameObject::NetworkId);
        DEFINE_MEMBER_N(Vector3, position, (unsigned int)Offsets::GameObject::Position);
        DEFINE_MEMBER_N(bool, visibility, (unsigned int)Offsets::GameObject::Visibility);
        DEFINE_MEMBER_N(int, spawnCount, (unsigned int)Offsets::GameObject::SpawnCount);
        DEFINE_MEMBER_N(float, mana, (unsigned int)Offsets::GameObject::Mana);
        DEFINE_MEMBER_N(float, maxMana, (unsigned int)Offsets::GameObject::MaxMana);
        DEFINE_MEMBER_N(bool, dead, (unsigned int)Offsets::GameObject::Dead);
        DEFINE_MEMBER_N(float, health, (unsigned int)Offsets::GameObject::Health);
        DEFINE_MEMBER_N(float, maxHealth, (unsigned int)Offsets::GameObject::MaxHealth);
        DEFINE_MEMBER_N(LolString, name, (unsigned int)Offsets::GameObject::Name);
        DEFINE_MEMBER_N(float, attackRange, (unsigned int)Offsets::GameObject::AttackRange);
        DEFINE_MEMBER_N(float, scale, (unsigned int)Offsets::GameObject::Scale);
        DEFINE_MEMBER_N(bool, targetable, (unsigned int)Offsets::GameObject::Targetable);
        DEFINE_MEMBER_N(float, attackSpeedMultiplier, Offsets::GameObject::AttackSpeedMultiplier);
        DEFINE_MEMBER_N(LolString, playerName, (unsigned int)Offsets::GameObject::PlayerName);
        DEFINE_MEMBER_N(int, actionState, Offsets::GameObject::ActionState);
        DEFINE_MEMBER_N(CharacterData*, characterData, Offsets::GameObject::CharacterData);
        DEFINE_MEMBER_N(float, movementSpeed, Offsets::GameObject::MovementSpeed);
    };

private:
    bool __thiscall CompareObjectFlags(int a2);

public:

    bool IsMinion() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Minion)) && maxHealth > 20;
    }

    bool IsHero() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Hero));
    }

    bool IsTurret() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Turret));
    }

    bool IsBuilding() {
        return reinterpret_cast<unsigned __int8*>(this) && CompareObjectFlags(static_cast<int>(ObjectTypeFlags::Building));
    }

    bool IsDummy() {
        return name.str().contains(XorStr("PracticeTool").c_str());
    }

    bool IsAlive() {
        return (*(unsigned __int8 (__thiscall **)(DWORD *))(*reinterpret_cast<DWORD*>(this) + 140))(reinterpret_cast<DWORD*>(this))
               && !(*(unsigned __int8 (__thiscall **)(DWORD *))(reinterpret_cast<DWORD*>(this)[148] + 8))(reinterpret_cast<DWORD*>(this) + 148);
    }

    bool IsLocalPlayer() {
        return reinterpret_cast<int>(this) == *reinterpret_cast<int*>(Globals::baseAddress + Offsets::Game::LocalPlayer);
    }

    bool IsWard() { // TODO: Checking by hash
        return this->maxHealth < 6 && this->maxMana < 150 && (this->name.str().contains(XorStr("BlueTrinket").c_str())
        || this->name.str().contains(XorStr("YellowTrinket").c_str()) || this->name.str().contains(XorStr("JammerDevice").c_str()));
    }

    bool CheckActionState(CharacterState state) {
        return this->actionState & state;
    }

    template <class T>
    bool IsAllyTo(T obj) {
        return this->team == obj->team;
    }

    template <class T>
    bool IsEnemyTo(T obj) {
        return this->team != obj->team;
    }

    template <class T>
    float DistanceTo(T obj) {
        return sqrt(powf((this->position.x - obj->position.x), 2) + powf((this->position.y - obj->position.y), 2) + powf((this->position.z - obj->position.z), 2));
    }

    bool IsOnScreen(float offsetX=0, float offsetY=0);

    AiManager* GetAiManager();
    Vector3 PredictPosition(float futureTime);





};


#endif //ASYLLUM_OBJECTBASE_H
