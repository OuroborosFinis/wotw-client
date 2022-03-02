#pragma once

namespace text_database
{
    enum class StaticTextEntries
    {
        Empty,
        EmptyName,

        // Shops
        Locked,
        Undiscovered,
        UndiscoveredDescription,

        // Opher Shop
        OpherShopSentry,
        OpherShopSentryDescription,
        OpherShopShuriken,
        OpherShopShurikenDescription,
        OpherShopHammer,
        OpherShopHammerDescription,
        OpherShopSpear,
        OpherShopSpearDescription,
        OpherShopBlaze,
        OpherShopBlazeDescription,
        OpherShopSentryUpgrade,
        OpherShopSentryUpgradeDescription,
        OpherShopShurikenUpgrade,
        OpherShopShurikenUpgradeDescription,
        OpherShopHammerUpgrade,
        OpherShopHammerUpgradeDescription,
        OpherShopSpearUpgrade,
        OpherShopSpearUpgradeDescription,
        OpherShopBlazeUpgrade,
        OpherShopBlazeUpgradeDescription,
        OpherShopTeleport,
        OpherShopTeleportDescription,
        OpherShopWaterBreath,
        OpherShopWaterBreathDescription,

        // Twillen Shop
        TwillenShopOvercharge,
        TwillenShopOverchargeDescription,
        TwillenShopEnergy,
        TwillenShopEnergyDescription,
        TwillenShopVitality,
        TwillenShopVitalityDescription,
        TwillenShopWingclip,
        TwillenShopWingclipDescription,
        TwillenShopTripleJump,
        TwillenShopTripleJumpDescription,
        TwillenShopFinesse,
        TwillenShopFinesseDescription,
        TwillenShopSwap,
        TwillenShopSwapDescription,
        TwillenShopLightHarvest,
        TwillenShopLightHarvestDescription,

        // Lupo Shop
        HealthIcons,
        HealthIconsDescription,
        EnergyIcons,
        EnergyIconsDescription,
        ShardIcons,
        ShardIconsDescription,

        // Lupo
        LupoMarshIntroduction,
        LupoMarshSalesPitch,
        LupoMarshNoSale,
        LupoMarshBroke,
        LupoMarshThanks,

        LupoHollowIntroduction,
        LupoHollowSalesPitch,
        LupoHollowNoSale,
        LupoHollowBroke,
        LupoHollowThanks,

        LupoWellspringIntroduction,
        LupoWellspringSalesPitch,
        LupoWellspringNoSale,
        LupoWellspringBroke,
        LupoWellspringThanks,

        LupoBurrowIntroduction,
        LupoBurrowSalesPitch,
        LupoBurrowNoSale,
        LupoBurrowBroke,
        LupoBurrowThanks,

        LupoReachIntroduction,
        LupoReachSalesPitch,
        LupoReachNoSale,
        LupoReachBroke,
        LupoReachThanks,

        LupoPoolsIntroduction,
        LupoPoolsSalesPitch,
        LupoPoolsNoSale,
        LupoPoolsBroke,
        LupoPoolsThanks,

        LupoDepthsIntroduction,
        LupoDepthsSalesPitch,
        LupoDepthsNoSale,
        LupoDepthsBroke,
        LupoDepthsThanks,

        LupoWastesIntroduction,
        LupoWastesSalesPitch,
        LupoWastesNoSale,
        LupoWastesBroke,
        LupoWastesThanks,

        LupoWillowIntroduction,
        LupoWillowSalesPitch,
        LupoWillowNoSale,
        LupoWillowBroke,
        LupoWillowThanks,

        TOTAL
    };
}

using static_text_entries = text_database::StaticTextEntries;
inline int operator *(static_text_entries entry) { return static_cast<int>(entry); }
