/*
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SPELLSTORE_H
#define __SPELLSTORE_H

#include "Common.h"
#include "DataStore.h"
#include "Timer.h"

#pragma pack(push,1)

struct WorldMapOverlay
{
	uint32 ID;           // 0
//	uint32 worldMapID;   // 1
	uint32 areaID;       // 2 - index to AreaTable
	uint32 areaID_2;     // 3 - index to AreaTable
	uint32 areaID_3;     // 4 - index to AreaTable
	uint32 areaID_4;     // 5 - index to AreaTable
// any of the four above indexes is enough to uncover the fragment
};

struct AchievementEntry
{
	uint32    ID;                                           // 0
	int32     factionFlag;                                  // 1 -1=all, 0=horde, 1=alliance
	int32     mapID;                                        // 2 -1=none
	uint32    unknown1;                                     // 20
	char*     name;                                         // 3-18
	uint32    name_flags;                                   // 19
	char*     description;                                  // 21-36
	uint32    desc_flags;                                   // 37
	uint32    categoryId;                                   // 38
	uint32    points;                                       // 39 reward points
	uint32    orderInCategory;                              // 40
	uint32    flags;                                        // 41
	uint32    unknown2;                                     // 42
	char*     rewardName;                                   // 43-58 title/item reward name
	uint32    rewardName_flags;                             // 59
	uint32    count;                                        // 60
	uint32    refAchievement;                               // 61
};

struct AchievementCategoryEntry
{
	uint32    ID;                                           // 0
	uint32    parentCategory;                               // 1 -1 for main category
	char*     name;                                         // 2-17
	uint32    name_flags;                                   // 18
	uint32    sortOrder;                                    // 19
};

struct AchievementCriteriaEntry
{
	uint32  ID;                                             // 0
	uint32  referredAchievement;                            // 1
	uint32  requiredType;                                   // 2
	union
	{
		// ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE = 0
		// TODO: also used for player deaths..
		struct
		{
			uint32  creatureID;                             // 3
			uint32  creatureCount;                          // 4
		} kill_creature;

		// ACHIEVEMENT_CRITERIA_TYPE_WIN_BG = 1
		// TODO: there are further criterias instead just winning
		struct
		{
			uint32  bgMapID;                                // 3
			uint32  winCount;                               // 4
		} win_bg;

		// ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL = 5
		struct
		{
			uint32  unused;                                 // 3
			uint32  level;                                  // 4
		} reach_level;

		// ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL = 7
		struct
		{
			uint32  skillID;                                // 3
			uint32  skillLevel;                             // 4
		} reach_skill_level;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT = 8
		struct
		{
			uint32  linkedAchievement;                      // 3
		} complete_achievement;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT = 9
		struct
		{
			uint32  unused;                                 // 3
			uint32  totalQuestCount;                        // 4
		} complete_quest_count;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY = 10
		struct
		{
			uint32  unused;                                 // 3
			uint32  numberOfDays;                           // 4
		} complete_daily_quest_daily;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11
		struct
		{
			uint32  zoneID;                                 // 3
			uint32  questCount;                             // 4
		} complete_quests_in_zone;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST = 14
		struct
		{
			uint32  unused;                                 // 3
			uint32  questCount;                             // 4
		} complete_daily_quest;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND= 15
		struct
		{
			uint32  mapID;                                  // 3
		} complete_battleground;

		// ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP= 16
		struct
		{
			uint32  mapID;                                  // 3
		} death_at_map;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID = 19
		struct
		{
			uint32  groupSize;                              // 3 can be 5, 10 or 25
		} complete_raid;

		// ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE = 20
		struct
		{
			uint32  creatureEntry;                          // 3
		} killed_by_creature;

		// ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING = 24
		struct
		{
			uint32  unused;                                 // 3
			uint32  fallHeight;                             // 4
		} fall_without_dying;

		// ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST = 27
		struct
		{
			uint32  questID;                                // 3
			uint32  questCount;                             // 4
		} complete_quest;

		// ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET = 28
		// ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2= 69
		struct
		{
			uint32  spellID;                                // 3
			uint32  spellCount;                             // 4
		} be_spell_target;

		// ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL= 29
		struct
		{
			uint32  spellID;                                // 3
			uint32  castCount;                              // 4
		} cast_spell;

		// ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31
		struct
		{
			uint32  areaID;                                 // 3 Reference to AreaTable.dbc
			uint32  killCount;                              // 4
		} honorable_kill_at_area;

		// ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA = 32
		struct
		{
			uint32  mapID;                                  // 3 Reference to Map.dbc
		} win_arena;

		// ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA = 33
		struct
		{
			uint32  mapID;                                  // 3 Reference to Map.dbc
		} play_arena;

		// ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL = 34
		struct
		{
			uint32  spellID;                                // 3 Reference to Map.dbc
		} learn_spell;

		// ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM = 36
		struct
		{
			uint32  itemID;                                 // 3
			uint32  itemCount;                              // 4
		} own_item;

		// ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA = 37
		struct
		{
			uint32  unused;                                 // 3
			uint32  count;                                  // 4
			uint32  flag;                                   // 5 4=in a row
		} win_rated_arena;

		// ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING = 38
		struct
		{
			uint32  teamtype;                               // 3 {2,3,5}
		} highest_team_rating;

		// ACHIEVEMENT_CRITERIA_TYPE_REACH_TEAM_RATING = 39
		struct
		{
			uint32  teamtype;                               // 3 {2,3,5}
			uint32  teamrating;                             // 4
		} reach_team_rating;

		// ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL = 40
		struct
		{
			uint32  skillID;                                // 3
			uint32  skillLevel;                             // 4 apprentice=1, journeyman=2, expert=3, artisan=4, master=5, grand master=6
		} learn_skill_level;

		// ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM = 41
		struct
		{
			uint32  itemID;                                 // 3
			uint32  itemCount;                              // 4
		} use_item;

		// ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM = 42
		struct
		{
			uint32  itemID;                                 // 3
			uint32  itemCount;                              // 4
		} loot_item;

		// ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA = 43
		struct
		{
			uint32  areaReference;                          // 3 - this is an index to WorldMapOverlay
		} explore_area;

		// ACHIEVEMENT_CRITERIA_TYPE_OWN_RANK= 44
		struct
		{
			// TODO: This rank is _NOT_ the index from CharTitles.dbc
			uint32  rank;                                   // 3
		} own_rank;

		// ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT= 45
		struct
		{
			uint32  unused;                                 // 3
			uint32  numberOfSlots;                          // 4
		} buy_bank_slot;

		// ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION= 46
		struct
		{
			uint32  factionID;                              // 3
			uint32  reputationAmount;                       // 4 Total reputation amount, so 42000 = exalted
		} gain_reputation;

		// ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION= 47
		struct
		{
			uint32  unused;                                 // 3
			uint32  numberOfExaltedFactions;                // 4
		} gain_exalted_reputation;

		// ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM = 49
		// TODO: where is the required itemlevel stored?
		struct
		{
			uint32  itemSlot;                               // 3
		} equip_epic_item;

		// ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT= 50
		struct
		{
			uint32  rollValue;                              // 3
			uint32  count;                                  // 4
		} roll_need_on_loot;

		// ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS = 52
		struct
		{
			uint32  classID;                                // 3
			uint32  count;                                  // 4
		} hk_class;

		// ACHIEVEMENT_CRITERIA_TYPE_HK_RACE = 53
		struct
		{
			uint32  raceID;                                 // 3
			uint32  count;                                  // 4
		} hk_race;

		// ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE = 54
		// TODO: where is the information about the target stored?
		struct
		{
			uint32  emoteID;                                // 3
		} do_emote;

		// ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE = 55
		struct
		{
			uint32  unused;                                 // 3
			uint32  count;                                  // 4
			uint32  flag;                                   // 5 =3 for battleground healing
			uint32  mapid;                                  // 6
		} healing_done;

		// ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM = 57
		struct
		{
			uint32  itemID;                                 // 3
		} equip_item;

		// ACHIEVEMENT_CRITERIA_TYPE_QUEST_REWARD_GOLD = 62
		struct
		{
			uint32 unknown;                                 // 3
			uint32 goldInCopper;                            // 4
		} quest_reward_money;

		// ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY = 67
		struct
		{
			uint32  unused;                                 // 3
			uint32  goldInCopper;                           // 4
		} loot_money;

		// ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT = 68
		struct
		{
			uint32  goEntry;                                // 3
			uint32  useCount;                               // 4
		} use_gameobject;

		// ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL= 70
		// TODO: are those special criteria stored in the dbc or do we have to add another sql table?
		struct
		{
			uint32  unused;                                 // 3
			uint32  killCount;                              // 4
		} special_pvp_kill;

		// ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT = 72
		struct
		{
			uint32  goEntry;                                // 3
			uint32  lootCount;                              // 4
		} fish_in_gameobject;

		// ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_MOUNTS= 75
		struct
		{
			uint32  unknown;                                // 3 777=?
			uint32  mountCount;                             // 4
		} number_of_mounts;

		// ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL = 76
		struct
		{
			uint32  unused;                                 // 3
			uint32  duelCount;                              // 4
		} win_duel;

		// ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER = 96
		struct
		{
			uint32  powerType;                              // 3 mana=0, 1=rage, 3=energy, 6=runic power
		} highest_power;

		// ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT = 97
		struct
		{
			uint32  statType;                               // 3 4=spirit, 3=int, 2=stamina, 1=agi, 0=strength
		} highest_stat;

		// ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER = 98
		struct
		{
			uint32  spellSchool;                            // 3
		} highest_spellpower;

		// ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING = 100
		struct
		{
			uint32  ratingType;                             // 3
		} highest_rating;

		// ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE = 109
		struct
		{
			uint32  lootType;                               // 3 3=fishing, 2=pickpocket, 4=disentchant
			uint32  lootTypeCount;                          // 4
		} loot_type;

		// ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2 = 110
		struct
		{
			uint32  skillLine;                              // 3
			uint32  spellCount;                             // 4
		} cast_spell2;

		// ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE= 112
		struct
		{
			uint32  skillLine;                              // 3
			uint32  spellCount;                             // 4
		} learn_skill_line;

		// ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL = 113
		struct
		{
			uint32  unused;                                 // 3
			uint32  killCount;                              // 4
		} honorable_kill;

		struct
		{
			uint32  field3;                                 // 3 main requirement
			uint32  field4;                                 // 4 main requirement count
			uint32  additionalRequirement1_type;            // 5 additional requirement 1 type
			uint32  additionalRequirement1_value;           // 6 additional requirement 1 value
			uint32  additionalRequirement2_type;            // 7 additional requirement 2 type
			uint32  additionalRequirement2_value;           // 8 additional requirement 1 value
		} raw;
	};
	char*   name;                                         // 9-24
	uint32  name_flags;                                   // 25
	uint32  completionFlag;                               // 26
	uint32  groupFlag;                                    // 27
	uint32  unk1;                                         // 28
	uint32  timeLimit;                                    // 29 time limit in seconds
	uint32  index;                                        // 30
};

struct BattlemasterListEntry
{
	uint32	bg_index;
	int32	maps[8];
	uint32	instance_type;
	uint32	max_players_per_faction;
	uint32	min_players_per_faction;
	uint32	flag; // EOTS AND SOTA have this set to nine, otherwise it's zero
	uint32  always_true;
	uint32	some_id;
	int32	zeros[15];
	uint32	unk[2];
	uint32	always_same; // Always 16712190
	uint32	minimum_payer_level; // ??? Is it, 3.0.8 doesn't match 3.0.3 numbers
								 // Do not use for now (NAQUADA)
	//char*	name;
};

struct BankSlotPrice
{
	uint32 Id;
	uint32 Price;
};

struct CharTitlesEntry
{
	uint32  ID;                                           // 0, title ids
	uint32  unk1;                                         // 1 flags?
	char*   name;                                         // 2-17, unused
	uint32  name_flag;                                    // 18 string flag, unused
	char*   name2;                                        // 19-34, unused
	char*   name2_flag;                                   // 35 string flag, unused
	uint32  bit_index;                                    // 36 used in PLAYER_CHOSEN_TITLE and 1<<index in PLAYER__FIELD_KNOWN_TITLES
};

struct ItemSetEntry
{
	uint32 id;                  //1
	char*  name;                //2
//	uint32 unused_shit[15];     //3 - 9
//	uint32 localeflag;          //10 constant
	uint32 itemid[8];           //11 - 18
//	uint32 more_unused_shit[9]; //19 - 27
	uint32 SpellID[8];          //28 - 35
	uint32 itemscount[8];       //36 - 43
	uint32 RequiredSkillID;     //44
	uint32 RequiredSkillAmt;    //45
};

struct ItemLimitCategoryEntry
{
	uint32 Id;					// 0	- Id
	char * name;				// 1	- Displayed name
	uint32 maxAmount;			// 18	- Max amount of items
	uint32 equippedFlag;		// 19	- equipped (bool?)
};

struct Lock
{
	uint32 Id;
	uint32 locktype[5]; // 0 - no lock, 1 - item needed for lock, 2 - min lockping skill needed
//	uint32 unk1[3];
	uint32 lockmisc[5]; // if type is 1 here is a item to unlock, else is unknow for now
//	uint32 unk2[3];
	uint32 minlockskill[5]; // min skill in lockpiking to unlock.
//	uint32 unk3[11];

	/* Actually it is:
	uint32 Id;
	uint32 locktype[8];
	uint32 lockindex[8];
	uint32 minlockskill[8];
	uint32 action[8];
	*/
};

struct emoteentry
{
	uint32 Id;
//	uint32 name;
	uint32 textid;
	uint32 textid2;
	uint32 textid3;
	uint32 textid4;
//	uint32 unk1;
	uint32 textid5;
//	uint32 unk2;
	uint32 textid6;
//	uint32 unk3;
//	uint32 unk4;
//	uint32 unk5;
//	uint32 unk6;
//	uint32 unk7;
//	uint32 unk8;
//	uint32 unk9;
//	uint32 unk10;
//	uint32 unk11;
};

struct skilllinespell //SkillLineAbility.dbc
{
	uint32 Id;
	uint32 skilline;
	uint32 spell;
//	uint32 raceMask;
//	uint32 classMask;
//	uint32 excludeRace;
//	uint32 excludeClass;
	uint32 minSkillLineRank;
	uint32 next;
	uint32 acquireMethod;
	uint32 grey;
	uint32 green;
//	uint32 abandonable;
	uint32 reqTP;
};

struct EnchantEntry
{
	uint32 Id;
	uint32 type[3];
	int32  min[3];//for compat, in practice min==max
	int32  max[3];
	uint32 spell[3];
	char*  Name;
//	uint32 NameAlt1;
//	uint32 NameAlt2;
//	uint32 NameAlt3;
//	uint32 NameAlt4;
//	uint32 NameAlt5;
//	uint32 NameAlt6;
//	uint32 NameAlt7;
//	uint32 NameAlt8;
//	uint32 NameAlt9;
//	uint32 NameAlt10;
//	uint32 NameAlt11;
//	uint32 NameAlt12;
//	uint32 NameAlt13;
//	uint32 NameAlt14;
//	uint32 NameAlt15;
//	uint32 NameFlags;
	uint32 visual;
	uint32 EnchantGroups;
	uint32 GemEntry;
	uint32 unk7;//Gem Related

};

struct GemPropertyEntry{
	uint32 Entry;
	uint32 EnchantmentID;
	uint32 unk1;//bool
	uint32 unk2;//bool
	uint32 SocketMask;
};

struct GlyphPropertyEntry	//GlyphProperties.dbc
{
	uint32 Entry;
	uint32 SpellID;
	uint32 Type; // 0 = Major, 1 = Minor
	uint32 unk; // some flag
};

struct GlyphSlotEntry
{
        uint32 Id;
        uint32 Type;
        uint32 Slot;
};

struct skilllineentry //SkillLine.dbc
{
	uint32 id;
	uint32 type;
	uint32 skillCostsID;
	char*  Name;
//	int32  NameAlt[15];
//	uint32 NameFlags;
//	uint32 Description;
//	uint32 DescriptionAlt[15];
//	uint32 DescriptionFlags;
//	uint32 spellIconID;
};

/*struct SkillRaceClassInfoEntry
{
	m_ID;
	m_skillID;
	m_raceMask;
	m_classMask;
	m_flags;
	m_minLevel;
	m_skillTierID;
	m_skillCostIndex;
}

struct SkillTiersEntry
{
	m_ID;
	m_cost[16];
	m_value[16];
}*/

// Struct for the entry in Spell.dbc
struct SpellEntry
{
	uint32 Id;                              //1
	uint32 Category;                        //2
	uint32 DispelType;                      //3
	uint32 MechanicsType;                   //4
	uint32 Attributes;                      //5
	uint32 AttributesEx;                    //6
	uint32 AttributesExB;                   //7
	uint32 AttributesExC;                   //8 // Flags to
	uint32 AttributesExD;                   //9  // Flags....
	uint32 AttributesExE;                   //10 // Flags 2.0.1 unknown one
	uint32 AttributesExF;                   //11
	uint32 RequiredShapeShift;              //12 // Flags BitMask for shapeshift spells
	uint32 ShapeshiftExclude;               //13-> this is wrong // Flags BitMask for which shapeshift forms this spell can NOT be used in.
	uint32 Targets;                         //14 - N / M
	uint32 TargetCreatureType;              //15
	uint32 RequiresSpellFocus;              //16
	uint32 FacingCasterFlags;               //17
	uint32 CasterAuraState;                 //18
	uint32 TargetAuraState;                 //19
	uint32 CasterAuraStateNot;              //20
	uint32 TargetAuraStateNot;              //21
	uint32 casterAuraSpell;                 //22
	uint32 targetAuraSpell;                 //23
	uint32 casterAuraSpellNot;              //24
	uint32 targetAuraSpellNot;              //25
	uint32 CastingTimeIndex;                //26
	uint32 RecoveryTime;                    //27
	uint32 CategoryRecoveryTime;            //28 recoverytime
	uint32 InterruptFlags;                  //29
	uint32 AuraInterruptFlags;              //30
	uint32 ChannelInterruptFlags;           //31
	uint32 procFlags;                       //32
	uint32 procChance;                      //33
	int32  procCharges;                     //34
	uint32 maxLevel;                        //35
	uint32 baseLevel;                       //36
	uint32 spellLevel;                      //37
	uint32 DurationIndex;                   //38
	uint32 powerType;                       //39
	uint32 manaCost;                        //40
	uint32 manaCostPerlevel;                //41
	uint32 manaPerSecond;                   //42
	uint32 manaPerSecondPerLevel;           //43
	uint32 rangeIndex;                      //44
	float  speed;                           //45
	uint32 modalNextSpell;                  //46
	uint32 maxstack;                        //47
	uint32 Totem[2];                        //48 - 49
	uint32 Reagent[8];                      //50 - 57
	uint32 ReagentCount[8];                 //58 - 65
	int32  EquippedItemClass;               //66
	uint32 EquippedItemSubClass;            //67
	uint32 RequiredItemFlags;               //68
	uint32 Effect[3];                       //69 - 71
	uint32 EffectDieSides[3];               //72 - 74
	uint32 EffectBaseDice[3];               //75 - 77
	float  EffectDicePerLevel[3];           //78 - 80
	float  EffectRealPointsPerLevel[3];     //81 - 83
	int32  EffectBasePoints[3];             //84 - 86
	int32  EffectMechanic[3];               //87 - 89       Related to SpellMechanic.dbc
	uint32 EffectImplicitTargetA[3];        //90 - 92
	uint32 EffectImplicitTargetB[3];        //93 - 95
	uint32 EffectRadiusIndex[3];            //96 - 98
	uint32 EffectApplyAuraName[3];          //99 - 101
	uint32 EffectAmplitude[3];              //102 - 104
	float  Effectunknown[3];                //105 - 107     This value is the $ value from description
	uint32 EffectChainTarget[3];            //108 - 110
	uint32 EffectItemType[3];               //111 - 113     Not sure maybe we should rename it. its the relation to field: SpellGroupType
	uint32 EffectMiscValue[3];              //114 - 116
	uint32 EffectMiscValueB[3];             //117 - 119  2.4.3
	uint32 EffectTriggerSpell[3];           //120 - 122
	float  EffectPointsPerComboPoint[3];    //123 - 125
	uint32 EffectSpellClassMask[3][3];      //126 - 134
	uint32 SpellVisual;                     //135
	uint32 field114;                        //136
	uint32 spellIconID;                     //137
	uint32 activeIconID;                    //138   activeIconID;
	uint32 spellPriority;                   //139
	char*  Name;                            //140
//	char*  NameAlt[15];                     //141-155 not used
//	uint32 NameFlags;                       //156 not used
	char*  Rank;                            //157
//	char*  RankAlt[15];                     //158-172 not used
//	uint32 RankFlags;                       //173 not used
	char*  Description;                     //174
//	char*  DescriptionAlt[15];              //175-189 not used
//	uint32 DescriptionFlags;                //190 not used
	char*  BuffDescription;                 //191
//	char*  BuffDescription[15];             //192-206 not used
//	uint32 buffdescflags;                   //207 not used
	uint32 ManaCostPercentage;              //208
	uint32 StartRecoveryTime;               //209
	uint32 StartRecoveryCategory;           //210
	uint32 MaxTargetLevel;                  //211
	uint32 SpellFamilyName;                 //212
	uint32 SpellGroupType[3];               //213-215
	uint32 MaxTargets;                      //216
	uint32 Spell_Dmg_Type;                  //217   dmg_class Integer      0=None, 1=Magic, 2=Melee, 3=Ranged
	uint32 PreventionType;                  //218   0,1,2 related to Spell_Dmg_Type I think
	int32  StanceBarOrder;                  //219   related to paladin aura's
	float  dmg_multiplier[3];               //220 - 222   if the name is correct I dono
	uint32 MinFactionID;                    //223   only one spellid:6994 has this value = 369 UNUSED
	uint32 MinReputation;                   //224   only one spellid:6994 has this value = 4 UNUSED
	uint32 RequiredAuraVision;              //225  3 spells 1 or 2
	uint32 TotemCategory[2];                //226-227
	int32  RequiresAreaId;                  //228
	uint32 School;                          //229
	uint32 RuneCostID;                      //230 from 3.0.1
//	uint32 SpellMissileID;                  //231 from 3.0.1

	/// CUSTOM: these fields are used for the modifications made in the world.cpp
	uint32 DiminishStatus;                  //
	uint32 proc_interval;                   //!!! CUSTOM, <Fill description for variable>
	//Buff Groupin Rule -> caster can cast this spell only on 1 target. Value represents the group spell is part of. Can be part of only 1 group
	//caster can only cast on 1 target these spells
	uint32 BGR_one_buff_from_caster_on_1target; //!!! CUSTOM, <Fill description for variable>
	//target can have only buff of this type on self. Value represents the group spell is part of. Can be part of only 1 group
	uint32 BGR_one_buff_on_target;          //!!! CUSTOM, these are related to creating a item through a spell
	//caster can have only 1 Aura per spell group, ex pal auras
	uint32 BGR_one_buff_from_caster_on_self;//!!! CUSTOM, these are related to creating a item through a spell
//	uint32 buffIndexType;                   //!!! CUSTOM, <Fill description for variable>
	uint32 c_is_flags;                      //!!! CUSTOM, store spell checks in a static way : isdamageind,ishealing
//	uint32 buffType;                        //!!! CUSTOM, these are related to creating a item through a spell
	uint32 RankNumber;                      //!!! CUSTOM, this protects players from having >1 rank of a spell
	uint32 NameHash;                        //!!! CUSTOM, related to custom spells, summon spell quest related spells
	uint32 talent_tree;                     //!!! CUSTOM,
	uint32 in_front_status;                 //!!! CUSTOM,
	uint32 EffectSpellGroupRelation_high[3];     //!!! this is not contained in client dbc but server must have it
	uint32 ThreatForSpell;
	float  ThreatForSpellCoef;
	uint32 ProcOnNameHash[3];
	uint32 spell_coef_flags;                //!!! CUSTOM, store flags for spell coefficient calculations

	float  base_range_or_radius_sqr;        //!!! CUSTOM, needed for aoe spells most of the time
	// love me or hate me, all "In a cone in front of the caster" spells don't necessarily mean "in front"
	float  cone_width;
	//Spell Coefficient
	float  casttime_coef;                   //!!! CUSTOM, faster spell bonus calculation
	float  fixed_dddhcoef;                  //!!! CUSTOM, fixed DD-DH coefficient for some spells
	float  fixed_hotdotcoef;                //!!! CUSTOM, fixed HOT-DOT coefficient for some spells
	float  Dspell_coef_override;            //!!! CUSTOM, overrides any spell coefficient calculation and use this value in DD&DH
	float  OTspell_coef_override;           //!!! CUSTOM, overrides any spell coefficient calculation and use this value in HOT&DOT
	int    ai_target_type;

	bool   self_cast_only;
	bool   apply_on_shapeshift_change;
	bool   always_apply;
	bool   is_melee_spell;                  //!!! CUSTOM,
	bool   is_ranged_spell;                 //!!! CUSTOM,
	bool   spell_can_crit;                  //!!! CUSTOM,
	bool   noproc;

	uint32 SchoolMask;                      // Custom
/*
//3.0.1 client column namings
m_id
m_category
m_castUI
m_dispelType
m_mechanic
m_attributes
m_attributesEx
m_attributesExB
m_attributesExC
m_attributesExD
m_attributesExE
m_attributesExF
m_shapeshiftMask
m_shapeshiftExclude
m_targets
m_targetCreatureType
m_requiresSpellFocus
m_facingCasterFlags
m_casterAuraState
m_targetAuraState
m_excludeCasterAuraState
m_excludeTargetAuraState
m_castingTimeIndex
m_recoveryTime
m_categoryRecoveryTime
m_interruptFlags
m_auraInterruptFlags
m_channelInterruptFlags
m_procTypeMask
m_procChance
m_procCharges
m_maxLevel
m_baseLevel
m_spellLevel
m_durationIndex
m_powerType
m_manaCost
m_manaCostPerLevel
m_manaPerSecond
m_manaPerSecondPerLevel
m_rangeIndex
m_speed
m_modalNextSpell
m_cumulativeAura
m_totem
m_reagent
m_reagentCount
m_equippedItemClass
m_equippedItemSubclass
m_equippedItemInvTypes
m_effect
m_effectDieSides
m_effectBaseDice
m_effectDicePerLevel
m_effectRealPointsPerLevel
m_effectBasePoints
m_effectMechanic
m_implicitTargetA
m_implicitTargetB
m_effectRadiusIndex
m_effectAura
m_effectAuraPeriod
m_effectAmplitude
m_effectChainTargets
m_effectItemType
m_effectMiscValue
m_effectMiscValueB
m_effectTriggerSpell
m_effectPointsPerCombo
m_spellVisualID
m_spellIconID
m_activeIconID
m_spellPriority
m_name_lang
m_nameSubtext_lang
m_description_lang
m_auraDescription_lang
m_manaCostPct
m_startRecoveryCategory
m_startRecoveryTime
m_maxTargetLevel
m_spellClassSet
m_spellClassMask
m_maxTargets
m_defenseType
m_preventionType
m_stanceBarOrder
m_effectChainAmplitude
m_minFactionID
m_minReputation
m_requiredAuraVision
m_requiredTotemCategoryID
m_requiredAreaID
m_schoolMask
m_RuneCostID
m_spellMissileID
*/
};

struct SpellRuneCostEntry
{
	uint32  ID;
	uint32  bloodRuneCost;
	uint32  frostRuneCost;
	uint32  unholyRuneCost;
	uint32  runePowerGain;
};

struct ItemExtendedCostEntry
{
	uint32 costid;
	uint32 honor;
	uint32 arena;
	uint32 item[5];
	uint32 count[5];
	uint32 personalrating;
};

struct TalentEntry
{
	uint32  TalentID;
	uint32  TalentTree;
	uint32  Row;
	uint32  Col;
	uint32  RankID[5];
//	uint32  unk[4];
	uint32  DependsOn;
//	uint32  unk1[2];
	uint32  DependsOnRank;
//	uint32  unk2[4];
};

struct TalentTabEntry
{
	uint32 TalentTabID;
//	char*  Name;
//	uint32 unk3;
//	uint32 unk4;
//	uint32 unk5;
//	uint32 unk6;
//	uint32 unk7;
//	uint32 unk8;
//	uint32 unk9;
//	uint32 unk10;
//	uint32 unk11;
//	uint32 unk12;
//	uint32 unk13;
//	uint32 unk14;
//	uint32 unk15;
//	uint32 unk16;
//	uint32 unk17;
//	uint32 unk18;
//	uint32 unk19;
//	uint32 unk20;
	uint32 ClassMask;
//	uint32 unk21;
	uint32 TabPage;
//	char*  InternalName;
};

struct Trainerspell
{
	uint32 Id;
	uint32 skilline1;
	uint32 skilline2;
	uint32 skilline3;
	uint32 maxlvl;
	uint32 charclass;
};

struct SpellCastTime
{
	uint32 ID;
	uint32 CastTime;
//	uint32 unk1;
//	uint32 unk2;
};

struct SpellRadius
{
	uint32 ID;
	float  Radius;
//	float  unk1;
	float  Radius2;
};

struct SpellRange
{
	uint32 ID;
	float  minRange;
	float  minRange2;
	float  maxRange;
	float  maxRange2;
//	uint32 unks[35];
};

struct SpellDuration
{
	uint32 ID;
	uint32 Duration1;
	uint32 Duration2;
	uint32 Duration3;
};

struct RandomProps
{
	uint32 ID;
//	uint32 name1;
	uint32 spells[3];
//	uint32 unk1;
//	uint32 unk2;
//	uint32 name2;
//	uint32 RankAlt1;
//	uint32 RankAlt2;
//	uint32 RankAlt3;
//	uint32 RankAlt4;
//	uint32 RankAlt5;
//	uint32 RankAlt6;
//	uint32 RankAlt7;
//	uint32 RankAlt8;
//	uint32 RankAlt9;
//	uint32 RankAlt10;
//	uint32 RankAlt11;
//	uint32 RankAlt12;
//	uint32 RankAlt13;
//	uint32 RankAlt14;
//	uint32 RankAlt15;
//	uint32 RankFlags;

};

struct AreaGroup
{
	uint32 AreaGroupId;
	uint32 AreaId[7];
};

struct AreaTable
{
	uint32 AreaId;
	uint32 mapId;
	uint32 ZoneId;
	uint32 explorationFlag;
	uint32 AreaFlags;
//	uint32 unk2;
//	uint32 unk3;
//	uint32 unk4;
	uint32 EXP;//not XP
//	uint32 unk5;
	uint32 level;
	char*  name;
//	uint32 nameAlt1;
//	uint32 nameAlt2;
//	uint32 nameAlt3;
//	uint32 nameAlt4;
//	uint32 nameAlt5;
//	uint32 nameAlt6;
//	uint32 nameAlt7;
//	uint32 nameAlt8;
//	uint32 nameAlt9;
//	uint32 nameAlt10;
//	uint32 nameAlt11;
//	uint32 nameAlt12;
//	uint32 nameAlt13;
//	uint32 nameAlt14;
//	uint32 nameAlt15;
//	uint32 nameFlags;
	uint32 category;
//	uint32 unk7;
//	uint32 unk8;
//	uint32 unk9;
//	uint32 unk10;
//	uint32 unk11;
//	uint32 unk12;
};

struct FactionTemplateDBC
{
	uint32 ID;
	uint32 Faction;
	uint32 FactionGroup;
	uint32 Mask;
	uint32 FriendlyMask;
	uint32 HostileMask;
	uint32 EnemyFactions[4];
	uint32 FriendlyFactions[4];
};

struct AuctionHouseDBC
{
	uint32 id;
	uint32 unk;
	uint32 fee;
	uint32 tax;
//	char*  name;
//	char*  nameAlt1;
//	char*  nameAlt2;
//	char*  nameAlt3;
//	char*  nameAlt4;
//	char*  nameAlt5;
//	char*  nameAlt6;
//	char*  nameAlt7;
//	char*  nameAlt8;
//	char*  nameAlt9;
//	char*  nameAlt10;
//	char*  nameAlt11;
//	char*  nameAlt12;
//	char*  nameAlt13;
//	char*  nameAlt14;
//	char*  nameAlt15;
//	char*  nameFlags;
};

struct FactionDBC
{
	uint32 ID;
	int32  RepListId;
	uint32 RaceMask[4];
	uint32 ClassMask[4];
	int32  baseRepValue[4];
	uint32 repFlags[4];
	uint32 parentFaction;
	char*  Name;
//	uint32 poo[16];
//	uint32 Description;
//	uint32 poo2[16];
};

struct DBCTaxiNode
{
	uint32 id;
	uint32 mapid;
	float  x;
	float  y;
	float  z;
//	uint32 name;
//	uint32 namealt1;
//	uint32 namealt2;
//	uint32 namealt3;
//	uint32 namealt4;
//	uint32 namealt5;
//	uint32 namealt6;
//	uint32 namealt7;
//	uint32 namealt8;
//	uint32 namealt9;
//	uint32 namealt10;
//	uint32 namealt11;
//	uint32 namealt12;
//	uint32 namealt13;
//	uint32 namealt14;
//	uint32 namealt15;
//	uint32 nameflags;
	uint32 horde_mount;
	uint32 alliance_mount;
};

struct DBCTaxiPath
{
	uint32 id;
	uint32 from;
	uint32 to;
	uint32 price;
};

struct DBCTaxiPathNode
{
	uint32 id;
	uint32 path;
	uint32 seq;			// nodeIndex
	uint32 mapid;
	float  x;
	float  y;
	float  z;
	uint32 flags;
	uint32 waittime;
//	uint32 arivalEventID;
//	uint32 departureEventID;
};

struct CreatureSpellDataEntry
{
	uint32 id;
	uint32 Spells[3];
	uint32 PHSpell;
	uint32 Cooldowns[3];
	uint32 PH;
};

struct CharRaceEntry
{
	uint32 race_id;
	uint32 team_id;
	uint32 cinematic_id;
	char*  name1;
};

struct CharClassEntry
{
	uint32 class_id;
//	uint32 unk1;
	uint32 power_type;
//	uint32 unk2;
	char*  name;
//	uint32 namealt1;
//	uint32 namealt2;
//	uint32 namealt3;
//	uint32 namealt4;
//	uint32 namealt5;
//	uint32 namealt6;
//	uint32 namealt7;
//	uint32 namealt8;
//	uint32 namealt9;
//	uint32 namealt10;
//	uint32 namealt11;
//	uint32 namealt12;
//	uint32 namealt13;
//	uint32 namealt14;
//	uint32 namealt15;
//	uint32 nameflags;
//	uint32 unk3;
//	uint32 unk4;
//	uint32 unk5;
};

struct CreatureFamilyEntry
{
	uint32 ID;
	float  minsize;
	uint32 minlevel;
	float  maxsize;
	uint32 maxlevel;
	uint32 skilline;
	uint32 tameable;     //second skill line - 270 Generic
	uint32 petdietflags;
	uint32 talenttree;   // -1 = none, 0 = ferocity(410), 1 = tenacity(409), 2 = cunning(411)
//	uint32 unk;        // some index 0 - 63
	char*  name;
//	uint32 namealt[15];
//	uint32 nameflags;
//	uint32 iconFile;
};

struct MapEntry
{
	uint32 id;
	char*  name_internal;
	uint32 map_type;
	uint32 is_pvp_zone;
	char*  real_name;
	uint32 linked_zone;  // common zone for instance and continent map
	char*  hordeIntro;   // text for PvP Zones
	char*  allianceIntro;// text for PvP Zones
	uint32 multimap_id;
	char*  normalReqText;// normal mode requirement text
	char*  heroicReqText;// heroic mode requirement text
	int32  parent_map;   // map_id of parent map
	float  start_x;      // enter x coordinate (if exist single entry)
	float  start_y;      // enter y coordinate (if exist single entry)
	uint32 resetTimeRaid;
	uint32 resetTimeHeroic;
	uint32 addon;        // 0-original maps, 1-tbc addon, 2-wotlk addon
};

struct ItemRandomSuffixEntry
{
	uint32 id;
	uint32 enchantments[3];
	uint32 prefixes[3];
};

struct BarberShopStyleEntry
{
	uint32  id;           // 0
	uint32  type;         // 1 value 0 -> hair, value 2 -> facialhair
//	char*   name;         // 2 string hairstyle name
//	char*   name[15];     // 3-17 name of hair style
//	uint32  name_flags;   // 18
//	uint32  unk_name[16]; // 19-34, all empty
//	uint32  unk_flags;    // 35
//	float   unk3;         // 36 values 1 and 0,75
	uint32  race;         // 37 race
	uint32  gender;       // 38 0 male, 1 female
	uint32  hair_id;      // 39 Hair ID
};

struct gtFloat
{
	float val;
};

struct CombatRatingDBC
{
	float val;
};

struct ChatChannelDBC
{
	uint32 id;
	uint32 flags;
	char * name_pattern[16];
};

struct DurabilityQualityEntry
{
	uint32 id;
	float quality_modifier;
};

struct DurabilityCostsEntry
{
	uint32 itemlevel;
	uint32 modifier[29];
};

struct AreaTriggerEntry
{
	uint32    id;           // 0
	uint32    mapid;        // 1
	float     x;            // 2
	float     y;            // 3
	float     z;            // 4
	float     o;            // 5 radius?
	float     box_x;        // 6 extent x edge
	float     box_y;        // 7 extent y edge
	float     box_z;        // 8 extent z edge
	float     box_o;        // 9 extent rotation by about z axis
};

/*struct VehicleEntry
{
	m_ID;
	m_flags;
	m_turnSpeed;
	m_pitchSpeed;
	m_pitchMin;
	m_pitchMax;
	m_seatID[8];
}

struct VehicleSeatEntry
{
	m_ID;
	m_flags;
	m_attachmentID;
	m_attachmentOffsetX;
	m_attachmentOffsetY;
	m_attachmentOffsetZ;
	m_enterPreDelay;
	m_enterSpeed;
	m_enterGravity;
	m_enterMinDuration;
	m_enterMaxDuration;
	m_enterMinArcHeight;
	m_enterMaxArcHeight;
	m_enterAnimStart;
	m_enterAnimLoop;
	m_rideAnimStart;
	m_rideAnimLoop;
	m_rideUpperAnimStart;
	m_rideUpperAnimLoop;
	m_exitPreDelay;
	m_exitSpeed;
	m_exitGravity;
	m_exitMinDuration;
	m_exitMaxDuration;
	m_exitMinArcHeight;
	m_exitMaxArcHeight;
	m_exitAnimStart;
	m_exitAnimLoop;
	m_exitAnimEnd;
}

struct WeatherEntry
{
	m_ID;
	m_ambienceID;
	m_effectType;
	m_effectColor[3];
	m_effectTexture;
}
*/

struct ScalingStatDistributionEntry{
	uint32 id;
	int32 stat[10];
	uint32 statmodifier[10];
	uint32 maxlevel;
};

struct ScalingStatValuesEntry{
	uint32 id;
	uint32 level;
	uint32 multiplier[17];
};

#pragma pack(pop)

WoWICE_INLINE float GetRadius(SpellRadius *radius)
{
	return radius->Radius;
}
WoWICE_INLINE uint32 GetCastTime(SpellCastTime *time)
{
	return time->CastTime;
}
WoWICE_INLINE float GetMaxRange(SpellRange *range)
{
	return range->maxRange;
}
WoWICE_INLINE float GetMinRange(SpellRange *range)
{
	return range->minRange;
}
WoWICE_INLINE uint32 GetDuration(SpellDuration *dur)
{
	return dur->Duration1;
}

#define SAFE_DBC_CODE_RETURNS        /* undefine this to make out of range/nulls return null. */

template<class T>
class SERVER_DECL DBCStorage
{
	T * m_heapBlock;
	T * m_firstEntry;

	T ** m_entries;
	uint32 m_max;
	uint32 m_numrows;
	uint32 m_stringlength;
	char * m_stringData;

	uint32 rows;
	uint32 cols;
	uint32 useless_shit;
	uint32 header;

public:

	DBCStorage()
	{
		m_heapBlock = NULL;
		m_entries = NULL;
		m_firstEntry = NULL;
		m_max = 0;
		m_numrows = 0;
		m_stringlength=0;
		m_stringData = NULL;
	}

	~DBCStorage()
	{
		Cleanup();
	}

	void Cleanup()
	{
		if(m_heapBlock)
		{
			free(m_heapBlock);
			m_heapBlock = NULL;
		}
		if(m_entries)
		{
			free(m_entries);
			m_entries = NULL;
		}
		if( m_stringData != NULL )
		{
			free(m_stringData);
			m_stringData = NULL;
		}
	}

	bool Load(const char * filename, const char * format, bool load_indexed, bool load_strings)
	{
		uint32 i;
		uint32 string_length;
		long pos;

		FILE * f = fopen(filename, "rb");
		if(f == NULL)
			return false;

		/* read the number of rows, and allocate our block on the heap */
		fread(&header,4,1,f);
		fread(&rows, 4, 1, f);
		fread(&cols, 4, 1, f);
		fread(&useless_shit, 4, 1, f);
		fread(&string_length, 4, 1, f);
		pos = ftell(f);

#ifdef USING_BIG_ENDIAN
		swap32(&rows); swap32(&cols); swap32(&useless_shit); swap32(&string_length);
#endif

		if( load_strings )
		{
			fseek( f, 20 + ( rows * cols * 4 ), SEEK_SET );
			m_stringData = (char*)malloc(string_length);
			m_stringlength = string_length;
			if (m_stringData)
				fread( m_stringData, string_length, 1, f );
		}

		fseek(f, pos, SEEK_SET);

		m_heapBlock = (T*)malloc(rows * sizeof(T));
		ASSERT(m_heapBlock);

		/* read the data for each row */
		for(i = 0; i < rows; ++i)
		{
			memset(&m_heapBlock[i], 0, sizeof(T));
			ReadEntry(f, &m_heapBlock[i], format, cols, filename);

			if(load_indexed)
			{
				/* all the time the first field in the dbc is our unique entry */
				if(*(uint32*)&m_heapBlock[i] > m_max)
					m_max = *(uint32*)&m_heapBlock[i];
			}
		}

		if(load_indexed)
		{
			m_entries = (T**)malloc(sizeof(T*) * (m_max+1));
			ASSERT(m_entries);

			memset(m_entries, 0, (sizeof(T*) * (m_max+1)));
			for(i = 0; i < rows; ++i)
			{
				if(m_firstEntry == NULL)
					m_firstEntry = &m_heapBlock[i];

				m_entries[*(uint32*)&m_heapBlock[i]] = &m_heapBlock[i];
			}
		}

		m_numrows = rows;

		fclose(f);
		return true;
	}

	void ReadEntry(FILE * f, T * dest, const char * format, uint32 cols, const char * filename)
	{
		const char * t = format;
		uint32 * dest_ptr = (uint32*)dest;
		uint32 c = 0;
		uint32 val;
		size_t len = strlen(format);
		if(len!= cols)
			printf("!!! possible invalid format in file %s (us: %u, them: %u)\n", filename, len, cols);

		while(*t != 0)
		{
			if((++c) > cols)
			{
				++t;
				printf("!!! Read buffer overflow in DBC reading of file %s\n", filename);
				continue;
			}

			fread(&val, 4, 1, f);
			if(*t == 'x')
			{
				++t;
				continue;		// skip!
			}
#ifdef USING_BIG_ENDIAN
			swap32(&val);
#endif
			if(( *t == 's' ) || ( *t=='l' ))
			{
				char ** new_ptr = (char**)dest_ptr;
				static const char * null_str = "";
				char * ptr;
				// if t == 'lxxxxxxxxxxxxxxxx' use localized strings in case
				// the english one is empty. *t ends at most on the locale flag
				for(int count = (*t == 'l') ? 16 : 0 ;
					val == 0 && count > 0 && *(t+1) == 'x'; t++, count--)
				{
					fread(&val, 4, 1, f);
#ifdef USING_BIG_ENDIAN
					swap32(&val);
#endif
				}
				if( val < m_stringlength )
					ptr = m_stringData + val;
				else
					ptr = (char*)null_str;

				*new_ptr = ptr;
				new_ptr++;
				dest_ptr = (uint32*)new_ptr;
			}
			else
			{
				*dest_ptr = val;
				dest_ptr++;
			}

			++t;
		}
	}

	WoWICE_INLINE uint32 GetNumRows()
	{
		return m_numrows;
	}

	T * LookupEntryForced(uint32 i)
	{
#if 0
		if(m_entries)
		{
			if(i > m_max || m_entries[i] == NULL)
			{
				printf("LookupEntryForced failed for entry %u\n", i);
				return NULL;
			}
			else
				return m_entries[i];
		}
		else
		{
			if(i >= m_numrows)
				return NULL;
			else
				return &m_heapBlock[i];
		}
#else
		if(m_entries)
		{
			if(i > m_max || m_entries[i] == NULL)
				return NULL;
			else
				return m_entries[i];
		}
		else
		{
			if(i >= m_numrows)
				return NULL;
			else
				return &m_heapBlock[i];
		}
#endif
	}

	T * CreateCopy(T * obj)
	{
		T * oCopy = (T*)malloc(sizeof(T));
		ASSERT(oCopy);
		memcpy(oCopy,obj,sizeof(T));
		return oCopy;
	}
	void SetRow(uint32 i, T * t)
	{
		if(i < m_max && m_entries)
			m_entries[i] = t;
	}

#ifdef SAFE_DBC_CODE_RETURNS
	T * LookupEntry(uint32 i)
	{
		if(m_entries)
		{
			if(i > m_max || m_entries[i] == NULL)
				return m_firstEntry;
			else
				return m_entries[i];
		}
		else
		{
			if(i >= m_numrows)
				return &m_heapBlock[0];
			else
				return &m_heapBlock[i];
		}
	}

	T * LookupRow(uint32 i)
	{
		if(i >= m_numrows)
			return &m_heapBlock[0];
		else
			return &m_heapBlock[i];
	}

#else

	T * LookupEntry(uint32 i)
	{
		if(m_entries)
		{
			if(i > m_max || m_entries[i] == NULL)
				return NULL;
			else
				return m_entries[i];
		}
		else
		{
			if(i >= m_numrows)
				return NULL;
			else
				return m_heapBlock[i];
		}
	}

	T * LookupRow(uint32 i)
	{
		if(i >= m_numrows)
			return NULL;
		else
			return m_heapBlock[i];
	}

#endif
};

extern SERVER_DECL DBCStorage<WorldMapOverlay> dbcWorldMapOverlayStore;
extern SERVER_DECL DBCStorage<AchievementEntry> dbcAchievementStore;
extern SERVER_DECL DBCStorage<AchievementCriteriaEntry> dbcAchievementCriteriaStore;
extern SERVER_DECL DBCStorage<AchievementCategoryEntry> dbcAchievementCategoryStore;
extern SERVER_DECL DBCStorage<BattlemasterListEntry> dbcBattlemasterListStore;
extern SERVER_DECL DBCStorage<CharTitlesEntry> dbcCharTitlesEntry;
extern SERVER_DECL DBCStorage<BarberShopStyleEntry> dbcBarberShopStyleStore;
extern SERVER_DECL DBCStorage<GemPropertyEntry> dbcGemProperty;
extern SERVER_DECL DBCStorage<GlyphPropertyEntry> dbcGlyphProperty;
extern SERVER_DECL DBCStorage<GlyphSlotEntry> dbcGlyphSlot;
extern SERVER_DECL DBCStorage<ItemSetEntry> dbcItemSet;
extern SERVER_DECL DBCStorage<Lock> dbcLock;
extern SERVER_DECL DBCStorage<SpellEntry> dbcSpell;
extern SERVER_DECL DBCStorage<SpellDuration> dbcSpellDuration;
extern SERVER_DECL DBCStorage<SpellRange> dbcSpellRange;
extern SERVER_DECL DBCStorage<emoteentry> dbcEmoteEntry;
extern SERVER_DECL DBCStorage<SpellRadius> dbcSpellRadius;
extern SERVER_DECL DBCStorage<SpellCastTime> dbcSpellCastTime;
extern SERVER_DECL DBCStorage<AreaGroup> dbcAreaGroup;
extern SERVER_DECL DBCStorage<AreaTable> dbcArea;
extern SERVER_DECL DBCStorage<FactionTemplateDBC> dbcFactionTemplate;
extern SERVER_DECL DBCStorage<FactionDBC> dbcFaction;
extern SERVER_DECL DBCStorage<EnchantEntry> dbcEnchant;
extern SERVER_DECL DBCStorage<RandomProps> dbcRandomProps;
extern SERVER_DECL DBCStorage<skilllinespell> dbcSkillLineSpell;
extern SERVER_DECL DBCStorage<skilllineentry> dbcSkillLine;
extern SERVER_DECL DBCStorage<DBCTaxiNode> dbcTaxiNode;
extern SERVER_DECL DBCStorage<DBCTaxiPath> dbcTaxiPath;
extern SERVER_DECL DBCStorage<DBCTaxiPathNode> dbcTaxiPathNode;
extern SERVER_DECL DBCStorage<AuctionHouseDBC> dbcAuctionHouse;
extern SERVER_DECL DBCStorage<TalentEntry> dbcTalent;
extern SERVER_DECL DBCStorage<TalentTabEntry> dbcTalentTab;
extern SERVER_DECL DBCStorage<CreatureSpellDataEntry> dbcCreatureSpellData;
extern SERVER_DECL DBCStorage<CreatureFamilyEntry> dbcCreatureFamily;
extern SERVER_DECL DBCStorage<CharClassEntry> dbcCharClass;
extern SERVER_DECL DBCStorage<CharRaceEntry> dbcCharRace;
extern SERVER_DECL DBCStorage<MapEntry> dbcMap;
extern SERVER_DECL DBCStorage<SpellRuneCostEntry> dbcSpellRuneCost;
extern SERVER_DECL DBCStorage<ItemExtendedCostEntry> dbcItemExtendedCost;
extern SERVER_DECL DBCStorage<ItemRandomSuffixEntry> dbcItemRandomSuffix;
extern SERVER_DECL DBCStorage<CombatRatingDBC> dbcCombatRating;
extern SERVER_DECL DBCStorage<ChatChannelDBC> dbcChatChannels;
extern SERVER_DECL DBCStorage<DurabilityCostsEntry> dbcDurabilityCosts;
extern SERVER_DECL DBCStorage<DurabilityQualityEntry> dbcDurabilityQuality;
extern SERVER_DECL DBCStorage<BankSlotPrice> dbcBankSlotPrices;
extern SERVER_DECL DBCStorage<BankSlotPrice> dbcStableSlotPrices; //uses same structure as Bank
extern SERVER_DECL DBCStorage<gtFloat> dbcBarberShopPrices;
extern SERVER_DECL DBCStorage<gtFloat> dbcMeleeCrit;
extern SERVER_DECL DBCStorage<gtFloat> dbcMeleeCritBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcSpellCrit;
extern SERVER_DECL DBCStorage<gtFloat> dbcSpellCritBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcManaRegen;
extern SERVER_DECL DBCStorage<gtFloat> dbcManaRegenBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcHPRegen;
extern SERVER_DECL DBCStorage<gtFloat> dbcHPRegenBase;
extern SERVER_DECL DBCStorage<AreaTriggerEntry> dbcAreaTrigger;
extern SERVER_DECL DBCStorage<ScalingStatDistributionEntry> dbcScalingStatDistribution;
extern SERVER_DECL DBCStorage<ScalingStatValuesEntry> dbcScalingStatValues;
extern SERVER_DECL DBCStorage<ItemLimitCategoryEntry> dbcItemLimitCategory;

bool LoadDBCs();

#endif