#pragma once
#include <cstdint>

#pragma pack(1)

const int DIM = 8;
const int NUM_PLAYERS = 6;


enum class SiteSpecial : short
{
  DEFAULT    = 0x0,
  RESEARCH8  = 0x1, // Research Lab
  RESEARCH10 = 0x2, // Science Center
  DISCOUNT   = 0x3, // Factory
};

struct Site
{
  char name[20];
  int16_t id;
  int16_t resistance;
  int16_t support;
  int16_t frequency;
  int16_t tolerance;
  int16_t cash;
  int16_t combat;
  int16_t defense;
  int16_t stealth;
  int16_t detect;
  int16_t chaos;
  int16_t control;
  int16_t heal;
  int16_t influence;
  int16_t research;
  int16_t strength;
  int16_t blade;
  int16_t range;
  int16_t fighting;
  int16_t martial_arts;
  SiteSpecial special;
};

enum class Action : int8_t
{
  NONE      = 0x0,
  ATTACK    = 0x1,
  BRIBE     = 0x2,
  CHAOS     = 0x3,
  CONTROL   = 0x4,
  EQUIP     = 0x5,
  GIVE      = 0x6,
  HEAL      = 0x7,
  HIDE      = 0x8,
  INFLUENCE = 0x9,
  MOVE      = 0xA,
  RESEARCH  = 0xB,
  SELL      = 0xC,
  SNITCH    = 0xD,
  TERMINATE = 0xE,
};

struct GangInstance
{
  char player_id;
  char gang_id;
  char position;
  char force;
  char equipped_weapon;
  char equipped_armor;
  char equipped_tool;
  Action action;
  char target;
  char target_gang;
  Action action_repeat;
  char target_qq;
  char unknown_flag[6];
  char combat;
  char defense;
  char stealth;
  char detect;
  char chaos;
  char control;
  char heal;
  char influence;
  char research;
  char strength;
  char blade;
  char range;
  char fighting;
  char martial_arts;
};


struct SiteInfo2
{
  char id;
  char progress;
};

struct SectorData36
{
  char owner;
  char income;
  char tolerance_base;
  char sum_site_cash;
  char income_qq;
  char sum_tolerance;
  char sum_support;
  SiteInfo2 sites[3];
  char has_special_research;
  char has_special_discount;
  char police;
  char tax_qq;
  char anonymous_12;
  char field_12;
  char field_13;
  char field_14;
  char field_15;
  char sum_combat;
  char sum_defense;
  char sum_stealth;
  char sum_detect;
  char sum_chaos;
  char sum_control;
  char sum_heal;
  char sum_influence;
  char sum_research;
  char sum_strength;
  char sum_blade;
  char sum_range;
  char sum_fighting;
  char sum_martial_arts;
};

enum class Objective : int
{
  GREED       = 0x0,
  POWER       = 0x1,
  ACCEPTANCE  = 0x2,
  DOMINANCE   = 0x3,
  KILLEMALL   = 0x4,
  THEBIG40    = 0x5,
  SIEGE       = 0x6,
  ELIMINATE   = 0x7,
  BIGMAN      = 0x8,
  ARMAGEDDON  = 0x9,
};


enum class SiteType : int8_t {
    GYM                = 0,
    ARBORETUM          = 1,
    MUSEUM             = 2,
    CORPORATE_TOWERS   = 3,
    RESEARCH_LAB       = 4,
    HOSPITAL           = 5,
    CONDOS             = 6,
    OFFICES            = 7,
    SCIENCE_CENTER     = 8,
    HOUSING            = 9,
    MASS_MEDIA_STATION = 10,
    TEMPLE             = 11,
    CLINIC             = 12,
    ARENA              = 13,
    CASINO             = 14,
    FACTORY            = 15,
    BAR_DANCE_CLUB     = 16,
    BACK_ALLEY_NETWORK = 17,
    VACANT_LOT         = 18,
    PARKING_LOT        = 19,
    WASTE_INCINERATOR  = 20,
    HEADQUARTERS       = 21
};


struct Gang
{
  char name[30];
  int16_t id;
  char description[90];
  int16_t force;
  int16_t upkeep;
  int16_t combat;
  int16_t defense;
  int16_t tech_level;
  int16_t stealth;
  int16_t detect;
  int16_t chaos;
  int16_t control;
  int16_t heal;
  int16_t influence;
  int16_t research;
  int16_t strength;
  int16_t blade;
  int16_t range;
  int16_t fighting;
  int16_t martial_arts;
};



enum class ItemType : int16_t
{
  MELEE = 0x0,
  BLADE = 0x1,
  RANGE = 0x2,
  ARMOR = 0x3,
  MISC = 0x4,
  UNDEFINED = 0x63,
};

struct Item
{
  char name[30];
  int16_t id;
  char description[90];
  ItemType type;
  int16_t research_difficulty;
  int16_t cost;
  int16_t tech_level;
  int16_t combat;
  int16_t defense;
  int16_t stealth;
  int16_t detect;
  int16_t chaos;
  int16_t control;
  int16_t heal;
  int16_t influence;
  int16_t research;
  int16_t strength;
  int16_t blade;
  int16_t range;
  int16_t fighting;
  int16_t martial_arts;
  int16_t weapon_attack_animation;
  int16_t weapon_hit_animation;
  int16_t weapon_sound;
  int16_t unknown_item_value;
};


enum class NotificationType : short
{
  NO_EVENTS                  = 0,
  POLICE_CRACKDOWN           = 1,
  CONTROL_ATTAINED           = 2,
  CONTROL_LOST               = 3,
  COOPERATION_ACHIEVED       = 4,
  RESEARCH_COMPLETED         = 5,
  INSUFFICIENT_CASH          = 6,
  UNABLE_TO_HIRE_CAPACITY    = 7,
  UNABLE_TO_HIRE_MAX_GANGS   = 8,
  PLAYER_HAS_BEEN_ELIMINATED = 9,
  DEMO_COMPLETE              = 13
};

enum class IncomeClass : int8_t
{
    LM = 1,
    MI = 2,
    UM = 3,
    UP = 4,
};

#pragma pack()
