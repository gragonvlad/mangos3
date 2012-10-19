/*
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_DBCSTORES_H
#define MANGOS_DBCSTORES_H

#include "Common.h"
#include "Database/DBCStore.h"
#include "DBCStructure.h"

#include <list>

bool IsAcceptableClientBuild(uint32 build);
std::string AcceptableClientBuildsListStr();

typedef std::list<uint32> SimpleFactionsList;

SimpleFactionsList const* GetFactionTeamList(uint32 faction);
char const* GetPetName(uint32 petfamily, uint32 dbclang);
uint32 GetTalentSpellCost(uint32 spellId);
uint32 GetTalentSpellCost(TalentSpellPos const* pos);
TalentSpellPos const* GetTalentSpellPos(uint32 spellId);
SpellEffectEntry const* GetSpellEffectEntry(uint32 spellId, SpellEffectIndex effect);

SpellEffectEntry const* GetSpellEffectEntry(uint32 spellId, SpellEffectIndex effect);

int32 GetAreaFlagByAreaID(uint32 area_id);                  // -1 if not found
uint32 GetAreaFlagByMapId(uint32 mapid);

WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid);

MANGOS_DLL_SPEC AreaTableEntry const* GetAreaEntryByAreaID(uint32 area_id);
MANGOS_DLL_SPEC AreaTableEntry const* GetAreaEntryByAreaFlagAndMap(uint32 area_flag,uint32 map_id);

uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);

enum ContentLevels
{
    CONTENT_1_60 = 0,
    CONTENT_61_70,
    CONTENT_71_80,
    CONTENT_81_85,
    MAX_CONTENT,
};
ContentLevels GetContentLevelsForMap(uint32 mapid);

ChatChannelsEntry const* GetChannelEntryFor(uint32 channel_id);

bool IsTotemCategoryCompatiableWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId);

bool Zone2MapCoordinates(float& x, float& y, uint32 zone);
bool Map2ZoneCoordinates(float& x, float& y, uint32 zone);

typedef UNORDERED_MAP<uint32/* pair32(dungeonId,expansion) */,LFGDungeonExpansionEntry const*> LFGDungeonExpansionMap;
LFGDungeonExpansionEntry const* GetLFGExpansionEntry(uint32 dungeonId, uint32 expansion);

typedef UNORDERED_MAP<uint32/*pair32(map,diff)*/,MapDifficultyEntry const*> MapDifficultyMap;
MapDifficultyEntry const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);

typedef UNORDERED_MAP<uint32 /*zone_id*/, WorldMapAreaEntry const*> WorldMapAreaMap;
WorldMapAreaEntry const* GetWorldMapAreaByAreaId(uint32 area_id);

// returns main WorldMapArea for all maps, overall WorldMapArea (zone_id = 0) for continents
WorldMapAreaEntry const* GetWorldMapAreaByMapID(uint32 map_id);

// returns set of all zones in given map (1 zone mostly)
std::vector<uint32> GetWorldMapAreaSetByMapID(uint32 map_id);

// natural order for difficulties up-down iteration
// difficulties for dungeons/battleground ordered in normal way
// and if more high version not exist must be used lesser version
// for raid order different:
// 10 man normal version must be used instead nonexistent 10 man heroic version
// 25 man normal version must be used instead nonexistent 25 man heroic version
inline Difficulty GetPrevDifficulty(Difficulty diff, bool isRaid)
{
    switch (diff)
    {
        default:
        case RAID_DIFFICULTY_10MAN_NORMAL:                  // == DUNGEON_DIFFICULTY_NORMAL == REGULAR_DIFFICULTY
            return REGULAR_DIFFICULTY;                      // return itself, caller code must properly check and not call for this case
        case RAID_DIFFICULTY_25MAN_NORMAL:                  // == DUNGEON_DIFFICULTY_HEROIC
            return RAID_DIFFICULTY_10MAN_NORMAL;
        case RAID_DIFFICULTY_10MAN_HEROIC:
            return isRaid ? RAID_DIFFICULTY_10MAN_NORMAL : DUNGEON_DIFFICULTY_HEROIC;
        case RAID_DIFFICULTY_25MAN_HEROIC:
            return isRaid ? RAID_DIFFICULTY_25MAN_NORMAL : RAID_DIFFICULTY_10MAN_HEROIC;
    }
}

uint32 const* /*[3]*/ GetTalentTabPages(uint32 cls);
std::vector<uint32> const* GetTalentTreeMasterySpells(uint32 talentTree);
std::vector<uint32> const* GetTalentTreePrimarySpells(uint32 talentTree);
uint32 GetTalentTreeRolesMask(uint32 talentTree);

bool IsPointInAreaTriggerZone(AreaTriggerEntry const* atEntry, uint32 mapid, float x, float y, float z, float delta = 0.0f);

PvPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level);
PvPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapid, BattleGroundBracketId id);

MANGOS_DLL_SPEC uint32 GetCreatureModelRace(uint32 model_id);

float GetCurrencyPrecision(uint32 currencyId);
ResearchSiteEntry const* GetResearchSiteEntryById(uint32 id);

extern DBCStorage <AchievementEntry>             sAchievementStore;
extern DBCStorage <AchievementCriteriaEntry>     sAchievementCriteriaStore;
extern DBCStorage <AreaTableEntry>               sAreaStore;// recommend access using functions
extern DBCStorage <AreaGroupEntry>               sAreaGroupStore;
extern DBCStorage <AreaTriggerEntry>             sAreaTriggerStore;
extern DBCStorage <ArmorLocationEntry>           sArmorLocationStore;
extern DBCStorage <AuctionHouseEntry>            sAuctionHouseStore;
extern DBCStorage <BankBagSlotPricesEntry>       sBankBagSlotPricesStore;
extern DBCStorage <BarberShopStyleEntry>         sBarberShopStyleStore;
extern DBCStorage <BattlemasterListEntry>        sBattlemasterListStore;
// extern DBCStorage <ChatChannelsEntry>           sChatChannelsStore; -- accessed using function, no usable index
extern DBCStorage <CharStartOutfitEntry>         sCharStartOutfitStore;
extern DBCStorage <CharTitlesEntry>              sCharTitlesStore;
extern DBCStorage <ChrClassesEntry>              sChrClassesStore;
extern DBCStorage <ChrPowerTypesEntry>           sChrPowerTypesStore;
extern uint32 sChrClassXPowerTypesStore[MAX_CLASSES][MAX_POWERS];
extern uint32 sChrClassXPowerIndexStore[MAX_CLASSES][MAX_STORED_POWERS];
extern DBCStorage <ChrRacesEntry>                sChrRacesStore;
extern DBCStorage <CinematicSequencesEntry>      sCinematicSequencesStore;
extern DBCStorage <CreatureDisplayInfoEntry>     sCreatureDisplayInfoStore;
extern DBCStorage <CreatureDisplayInfoExtraEntry>sCreatureDisplayInfoExtraStore;
extern DBCStorage <CreatureFamilyEntry>          sCreatureFamilyStore;
extern DBCStorage <CreatureModelDataEntry>       sCreatureModelDataStore;
extern DBCStorage <CreatureSpellDataEntry>       sCreatureSpellDataStore;
extern DBCStorage <CreatureTypeEntry>            sCreatureTypeStore;
extern DBCStorage <CurrencyTypesEntry>           sCurrencyTypesStore;
extern DBCStorage <DestructibleModelDataEntry>   sDestructibleModelDataStore;
extern DBCStorage <DungeonEncounterEntry>        sDungeonEncounterStore;
extern DBCStorage <DurabilityCostsEntry>         sDurabilityCostsStore;
extern DBCStorage <DurabilityQualityEntry>       sDurabilityQualityStore;
extern DBCStorage <EmotesEntry>                  sEmotesStore;
extern DBCStorage <EmotesTextEntry>              sEmotesTextStore;
extern DBCStorage <FactionEntry>                 sFactionStore;
extern DBCStorage <FactionTemplateEntry>         sFactionTemplateStore;
extern DBCStorage <GameObjectDisplayInfoEntry>   sGameObjectDisplayInfoStore;
extern DBCStorage <GemPropertiesEntry>           sGemPropertiesStore;
extern DBCStorage <GlyphPropertiesEntry>         sGlyphPropertiesStore;
extern DBCStorage <GlyphSlotEntry>               sGlyphSlotStore;

extern DBCStorage <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore;
extern DBCStorage <GtCombatRatingsEntry>         sGtCombatRatingsStore;
extern DBCStorage <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore;
extern DBCStorage <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore;
extern DBCStorage <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore;
extern DBCStorage <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore;
extern DBCStorage <GtOCTClassCombatRatingScalarEntry> sGtOCTClassCombatRatingScalarStore;
// extern DBCStorage <GtOCTRegenMPEntry>            sGtOCTRegenMPStore; -- not used currently
extern DBCStorage <GtOCTHpPerStaminaEntry>       sGtOCTHpPerStaminaStore;
extern DBCStorage <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore;
extern DBCStorage <GtSpellScalingEntry>          sGtSpellScalingStore;
extern DBCStorage <GtOCTBaseHPByClassEntry>      sGtOCTBaseHPByClassStore;
extern DBCStorage <GtOCTBaseMPByClassEntry>      sGtOCTBaseMPByClassStore;
extern DBCStorage <GuildPerkSpellsEntry>         sGuildPerkSpellsStore;
extern DBCStorage <HolidaysEntry>                sHolidaysStore;
extern DBCStorage <ItemArmorQualityEntry>        sItemArmorQualityStore;
extern DBCStorage <ItemArmorShieldEntry>         sItemArmorShieldStore;
extern DBCStorage <ItemArmorTotalEntry>          sItemArmorTotalStore;
extern DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore;
extern DBCStorage <ItemClassEntry>               sItemClassStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageAmmoStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandCasterStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageRangedStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageThrownStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandCasterStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageWandStore;
// extern DBCStorage <ItemExtendedCostEntry>        sItemExtendedCostStore;
// extern DBCStorage <ItemDisplayInfoEntry>      sItemDisplayInfoStore; -- not used currently
extern DBCStorage <ItemLimitCategoryEntry>       sItemLimitCategoryStore;
extern DBCStorage <ItemRandomPropertiesEntry>    sItemRandomPropertiesStore;
extern DBCStorage <ItemRandomSuffixEntry>        sItemRandomSuffixStore;
extern DBCStorage <ItemReforgeEntry>             sItemReforgeStore;
extern DBCStorage <ItemSetEntry>                 sItemSetStore;
extern DBCStorage <LFGDungeonEntry>              sLFGDungeonStore;
extern DBCStorage <LFGDungeonExpansionEntry>     sLFGDungeonExpansionStore;
extern DBCStorage <LiquidTypeEntry>              sLiquidTypeStore;
extern DBCStorage <LockEntry>                    sLockStore;
extern DBCStorage <MailTemplateEntry>            sMailTemplateStore;
extern DBCStorage <MapEntry>                     sMapStore;
// extern DBCStorage <MapDifficultyEntry>           sMapDifficultyStore; -- use GetMapDifficultyData insteed
extern MapDifficultyMap                          sMapDifficultyMap;
extern DBCStorage <MovieEntry>                   sMovieStore;
extern DBCStorage <MountCapabilityEntry>         sMountCapabilityStore;
extern DBCStorage <MountTypeEntry>               sMountTypeStore;
extern DBCStorage <NumTalentsAtLevelEntry>       sNumTalentsAtLevelStore;
extern DBCStorage <OverrideSpellDataEntry>       sOverrideSpellDataStore;
extern DBCStorage <QuestFactionRewardEntry>      sQuestFactionRewardStore;
extern DBCStorage <QuestPOIPointEntry>           sQuestPOIPointStore;
extern DBCStorage <QuestSortEntry>               sQuestSortStore;
extern DBCStorage <QuestXPLevel>                 sQuestXPLevelStore;
extern DBCStorage <PhaseEntry>                   sPhaseStore;
// extern DBCStorage <PvPDifficultyEntry>           sPvPDifficultyStore; -- use GetBattlegroundSlotByLevel for access
extern DBCStorage <RandomPropertiesPointsEntry>  sRandomPropertiesPointsStore;
extern DBCStorage <ResearchBranchEntry>          sResearchBranchStore;
extern DBCStorage <ResearchSiteEntry>            sResearchSiteStore;
extern DBCStorage <ResearchProjectEntry>         sResearchProjectStore;
extern std::set<ResearchProjectEntry const*>     sResearchProjectSet;
extern ResearchSiteDataMap                       sResearchSiteDataMap;
extern DBCStorage <ScalingStatDistributionEntry> sScalingStatDistributionStore;
extern DBCStorage <ScalingStatValuesEntry>       sScalingStatValuesStore;
extern DBCStorage <SkillLineEntry>               sSkillLineStore;
extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
extern DBCStorage <SkillRaceClassInfoEntry>      sSkillRaceClassInfoStore;
extern DBCStorage <SoundEntriesEntry>            sSoundEntriesStore;
extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
extern DBCStorage <SpellDifficultyEntry>         sSpellDifficultyStore;
extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
extern DBCStorage <SpellFocusObjectEntry>        sSpellFocusObjectStore;
extern DBCStorage <SpellItemEnchantmentEntry>    sSpellItemEnchantmentStore;
extern DBCStorage <SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore;
extern SpellCategoryStore                        sSpellCategoryStore;
extern PetFamilySpellsStore                      sPetFamilySpellsStore;
extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
extern DBCStorage <SpellRuneCostEntry>           sSpellRuneCostStore;
extern DBCStorage <SpellShapeshiftFormEntry>     sSpellShapeshiftFormStore;
extern DBCStorage <SpellEntry>                   sSpellStore;
extern DBCStorage <SpellAuraOptionsEntry>        sSpellAuraOptionsStore;
extern DBCStorage <SpellAuraRestrictionsEntry>   sSpellAuraRestrictionsStore;
extern DBCStorage <SpellCastingRequirementsEntry> sSpellCastingRequirementsStore;
extern DBCStorage <SpellCategoriesEntry>         sSpellCategoriesStore;
extern DBCStorage <SpellClassOptionsEntry>       sSpellClassOptionsStore;
extern DBCStorage <SpellCooldownsEntry>          sSpellCooldownsStore;
extern DBCStorage <SpellEffectEntry>             sSpellEffectStore;
extern DBCStorage <SpellEquippedItemsEntry>      sSpellEquippedItemsStore;
extern DBCStorage <SpellInterruptsEntry>         sSpellInterruptsStore;
extern DBCStorage <SpellLevelsEntry>             sSpellLevelsStore;
extern DBCStorage <SpellPowerEntry>              sSpellPowerStore;
extern DBCStorage <SpellReagentsEntry>           sSpellReagentsStore;
extern DBCStorage <SpellScalingEntry>            sSpellScalingStore;
extern DBCStorage <SpellShapeshiftEntry>         sSpellShapeshiftStore;
extern DBCStorage <SpellTargetRestrictionsEntry> sSpellTargetRestrictionsStore;
extern DBCStorage <SpellTotemsEntry>             sSpellTotemsStore;
// extern DBCStorage <StableSlotPricesEntry>        sStableSlotPricesStore;
extern DBCStorage <SummonPropertiesEntry>        sSummonPropertiesStore;
extern DBCStorage <TalentEntry>                  sTalentStore;
extern DBCStorage <TalentTabEntry>               sTalentTabStore;
extern DBCStorage <TaxiNodesEntry>               sTaxiNodesStore;
extern DBCStorage <TaxiPathEntry>                sTaxiPathStore;
extern TaxiMask                                  sTaxiNodesMask;
extern TaxiMask                                  sOldContinentsNodesMask;
extern TaxiMask                                  sHordeTaxiNodesMask;
extern TaxiMask                                  sAllianceTaxiNodesMask;
extern TaxiMask                                  sDeathKnightTaxiNodesMask;
extern TaxiPathSetBySource                       sTaxiPathSetBySource;
extern TaxiPathNodesByPath                       sTaxiPathNodesByPath;
extern DBCStorage <TotemCategoryEntry>           sTotemCategoryStore;
extern TransportAnimationsByEntry                sTransportAnimationsByEntry;
extern DBCStorage <TransportAnimationEntry>      sTransportAnimationStore;
extern DBCStorage <VehicleEntry>                 sVehicleStore;
extern DBCStorage <VehicleSeatEntry>             sVehicleSeatStore;
extern DBCStorage <WMOAreaTableEntry>            sWMOAreaTableStore;
extern DBCStorage <WorldMapAreaEntry>            sWorldMapAreaStore;
extern DBCStorage <WorldMapOverlayEntry>         sWorldMapOverlayStore;
extern DBCStorage <WorldSafeLocsEntry>           sWorldSafeLocsStore;
extern DBCStorage <WorldStateEntry>              sWorldStateStore;
extern DBCStorage <WorldPvPAreaEntry>            sWorldPvPAreaStore;

void LoadDBCStores(const std::string& dataPath);

// script support functions
MANGOS_DLL_SPEC DBCStorage <SoundEntriesEntry>          const* GetSoundEntriesStore();
MANGOS_DLL_SPEC DBCStorage <SpellEntry>                 const* GetSpellStore();
MANGOS_DLL_SPEC DBCStorage <SpellRangeEntry>            const* GetSpellRangeStore();
MANGOS_DLL_SPEC DBCStorage <FactionEntry>               const* GetFactionStore();
MANGOS_DLL_SPEC DBCStorage <CreatureDisplayInfoEntry>   const* GetCreatureDisplayStore();
MANGOS_DLL_SPEC DBCStorage <EmotesEntry>                const* GetEmotesStore();
MANGOS_DLL_SPEC DBCStorage <AchievementEntry>           const* GetAchievementStore();
MANGOS_DLL_SPEC DBCStorage <EmotesTextEntry>            const* GetEmotesTextStore();
#endif
