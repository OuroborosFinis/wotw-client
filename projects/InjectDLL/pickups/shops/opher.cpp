#include <dll_main.h>
#include <Common/ext.h>
#include <csharp_bridge.h>
#include <pickups/shops/general.h>
#include <system/textures.h>
#include <system/text_database.h>
#include <uber_states/uber_state_helper.h>
#include <uber_states/uber_state_manager.h>
#include <utils/messaging.h>

#include <Il2CppModLoader/common.h>
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/interception_macros.h>

#include <functional>
#include <set>
#include <map>

using namespace modloader;

namespace
{
    IL2CPP_BINDING(, SeinCharacter, bool, get_Active, (app::SeinCharacter*));

    bool weaponmaster_purchase_in_progress = false;
    uint16_t opher_key(int acq, int req) {
        return static_cast<uint16_t>(acq & 0xFF) | (static_cast<uint16_t>(req & 0xFF) << 8);
    }

    struct OpherData
    {
        int id;
        static_text_entries entry;
        std::shared_ptr<textures::TextureData> texture;
    };

    constexpr int COST_ID = 10000;
    constexpr int LOCKED_ID = 20000;
    constexpr int VISIBLE_ID = 30000;
    constexpr int USES_ENERGY_ID = 40000;

    std::unordered_map<uint16_t, OpherData> opher_slots{
        { opher_key(app::AbilityType__Enum_WaterBreath, 255), { 23, static_text_entries::OpherShopWaterBreath } },       // Water breath
        { opher_key(app::AbilityType__Enum_SpiritSpearSpell, 255), { 74, static_text_entries::OpherShopSpear } },        // Spike
        { opher_key(app::AbilityType__Enum_Hammer, 255), { 98, static_text_entries::OpherShopHammer } },                 // Hammer
        { opher_key(255, 255), { 105, static_text_entries::OpherShopTeleport } },                                         // Fast Travel
        { opher_key(app::AbilityType__Enum_ChakramSpell, 255), { 106, static_text_entries::OpherShopShuriken } },         // Shuriken
        { opher_key(app::AbilityType__Enum_Blaze, 255), { 115, static_text_entries::OpherShopBlaze } },                   // Blaze
        { opher_key(app::AbilityType__Enum_TurretSpell, 255), { 116, static_text_entries::OpherShopSentry } },            // Sentry
        { opher_key(255, app::AbilityType__Enum_SpiritSpearSpell), { 1074, static_text_entries::OpherShopSpearUpgrade } }, // Exploding Spike
        { opher_key(255, app::AbilityType__Enum_Hammer), { 1098, static_text_entries::OpherShopHammerUpgrade } },          // Shock Smash
        { opher_key(255, app::AbilityType__Enum_ChakramSpell), { 1106, static_text_entries::OpherShopShurikenUpgrade } },  // Static Shuriken
        { opher_key(255, app::AbilityType__Enum_Blaze), { 1115, static_text_entries::OpherShopBlazeUpgrade } },            // Charged Blaze
        { opher_key(255, app::AbilityType__Enum_TurretSpell), { 1116, static_text_entries::OpherShopSentryUpgrade } },     // Rapid Sentry
    };

    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, get_IsOwned, (app::WeaponmasterItem* item))
    {
        if (shops::is_in_shop(shops::ShopType::Opher))
        {
            const app::AbilityType__Enum granted_type = item->fields.Upgrade->fields.AcquiredAbilityType;
            const app::AbilityType__Enum required_type = item->fields.Upgrade->fields.RequiredAbility;
            if (granted_type != app::AbilityType__Enum_None)
                return csharp_bridge::opher_bought_weapon(granted_type);

            if (required_type == app::AbilityType__Enum_None) // fast travel; 255, 255 -> 105, 0
                return csharp_bridge::opher_bought_weapon(app::AbilityType__Enum_TeleportSpell);

            return csharp_bridge::opher_bought_upgrade(required_type);
        }

        return WeaponmasterItem::get_IsOwned(item);
    }

    IL2CPP_INTERCEPT(, WeaponmasterItem, int, GetCostForLevel, (app::WeaponmasterItem* item, int level))
    {
        if (shops::is_in_shop(shops::ShopType::Opher))
        {
            const auto acq = static_cast<int>(item->fields.Upgrade->fields.AcquiredAbilityType);
            const auto req = static_cast<int>(item->fields.Upgrade->fields.RequiredAbility);
            const auto key = opher_key(acq, req);
            if (opher_slots.find(key) != opher_slots.end())
                return uber_states::get_uber_state_value(uber_states::constants::OPHER_WEAPON_GROUP_ID, opher_slots[opher_key(acq, req)].id + COST_ID);

            return 300; // todo; maybe a bit smarter than this?
        }

        return WeaponmasterItem::GetCostForLevel(item, level);
    }

    IL2CPP_INTERCEPT(, SpellInventory, app::PlayerUberStateInventory_InventoryItem*, AddNewSpellToInventory, (app::SpellInventory* this_ptr, unsigned int equipmentType, bool add))
    {
        if (weaponmaster_purchase_in_progress)
            return nullptr;

        const auto result = SpellInventory::AddNewSpellToInventory(this_ptr, equipmentType, add);
        return result;
    }

    IL2CPP_INTERCEPT(Moon, SerializedByteUberState, void, set_Value, (app::SerializedByteUberState* this_ptr, uint8_t value))
    {
        if (weaponmaster_purchase_in_progress)
            return;

        SerializedByteUberState::set_Value(this_ptr, value);
    }

    // TODO: Maybe rewrite to do it ourselves.
    IL2CPP_INTERCEPT(, WeaponmasterItem, void, DoPurchase, (app::WeaponmasterItem* item, int64_t context))
    {
        weaponmaster_purchase_in_progress = true;
        WeaponmasterItem::DoPurchase(item, context); // purchase first for keystone purposes
        weaponmaster_purchase_in_progress = false;
        //Weaponmasteritem$$DoPurchase
        const auto ability_type = item->fields.Upgrade->fields.AcquiredAbilityType;
        if (ability_type != app::AbilityType__Enum_None) {
            csharp_bridge::opher_buy_weapon(ability_type);
        }
        else {
            const auto required_type = item->fields.Upgrade->fields.RequiredAbility;
            if (required_type == app::AbilityType__Enum_None) // fast travel; 255, 255 -> 105, 0
                csharp_bridge::opher_buy_weapon(app::AbilityType__Enum_TeleportSpell);
            else
                csharp_bridge::opher_buy_upgrade(required_type);
        }
    }

    uint16_t get_key(app::WeaponmasterItem* item)
    {
        const auto acquired = static_cast<uint16_t>(item->fields.Upgrade->fields.AcquiredAbilityType);
        const auto required = static_cast<uint16_t>(item->fields.Upgrade->fields.RequiredAbility) << 8;
        return acquired | required;
    }

    IL2CPP_INTERCEPT(, UpgradableShardItem, bool, get_IsVisible, (app::UpgradableShardItem* z)) {
        return true;
    }

    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, get_IsVisible, (app::WeaponmasterItem* this_ptr))
    {
        if (il2cpp::is_assignable(this_ptr, "", "WeaponmasterItem") && this_ptr->fields.Upgrade != nullptr)
        {
            const auto key = get_key(this_ptr);
            const auto it = opher_slots.find(key);
            if (it != opher_slots.end())
                return uber_states::get_uber_state_value(uber_states::constants::OPHER_WEAPON_GROUP_ID, it->second.id + VISIBLE_ID);

            return false;
        }

        return true; //get_IsVisible(this_ptr);
    }

    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, get_IsLocked, (app::WeaponmasterItem* this_ptr))
    {
        if (il2cpp::is_assignable(this_ptr, "", "WeaponmasterItem") && this_ptr->fields.Upgrade != nullptr)
        {
            const auto key = get_key(this_ptr);
            const auto it = opher_slots.find(key);
            if (it != opher_slots.end())
                return uber_states::get_uber_state_value(uber_states::constants::OPHER_WEAPON_GROUP_ID, it->second.id + LOCKED_ID);
            
            return true;
        }

        return false; // get_IsLocked(this_ptr);
    }

    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, get_UsesEnergy, (app::WeaponmasterItem* this_ptr))
    {
        const auto key = get_key(this_ptr);
        const auto it = opher_slots.find(key);
        if (it != opher_slots.end())
            return uber_states::get_uber_state_value(uber_states::constants::OPHER_WEAPON_GROUP_ID, it->second.id + USES_ENERGY_ID);

        return false;
    }

    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, get_IsAffordable, (app::WeaponmasterItem* this_ptr)) {
        const auto key = get_key(this_ptr);
        const auto it = opher_slots.find(key);
        if (it != opher_slots.end())
        {
            auto cost = uber_states::get_uber_state_value(uber_states::constants::OPHER_WEAPON_GROUP_ID, it->second.id + COST_ID);
            return get_experience() >= cost;
        }

        return WeaponmasterItem::get_IsAffordable(this_ptr);
    }

    IL2CPP_BINDING(, UISoundSettingsAsset, bool, PlaySoundEvent, (app::UISoundSettingsAsset* this_ptr, app::Event_1* sound_event));
    IL2CPP_INTERCEPT(, WeaponmasterItem, bool, TryPurchase, (app::WeaponmasterItem* this_ptr, app::Action_1_MessageProvider_* show_hint, app::UISoundSettingsAsset* sounds, app::ShopKeeperHints* hints)) {
        app::MessageProvider* selected_hint;
        if (!get_IsVisible_intercept(this_ptr))
            selected_hint = hints->fields.ShardNotDiscovered;
        else if (get_IsLocked_intercept(this_ptr))
            selected_hint = hints->fields.ShardNotDiscovered;
        else if (get_IsOwned_intercept(this_ptr))
            selected_hint = hints->fields.AlreadyOwned;
        else if (!get_IsAffordable_intercept(this_ptr))
            selected_hint = hints->fields.NotEnoughSpiritLight;
        else
            return true;

        il2cpp::invoke(show_hint, "Invoke", selected_hint);
        if (sounds != nullptr)
            UISoundSettingsAsset::PlaySoundEvent(sounds, sounds->fields.InvalidItem);

        return false;
    }
}

namespace shops
{
    void set_opher_providers(app::WeaponmasterItem* item, app::MessageProvider*& name_provider, app::MessageProvider*& description_provider)
    {
        const auto key = get_key(item);
        const auto it = opher_slots.find(key);
        if (it != opher_slots.end())
        {
            name_provider = text_database::get_provider(*it->second.entry);
            description_provider = text_database::get_provider(*it->second.entry + 1);
        }
    }

    std::shared_ptr<textures::TextureData> get_opher_icon(app::WeaponmasterItem* shop_item)
    {
        const auto key = get_key(shop_item);
        const auto it = opher_slots.find(key);
        if (it != opher_slots.end())
            return it->second.texture;

        return nullptr;
    }
}

INJECT_C_DLLEXPORT void set_opher_icon(int acquired, int required, const wchar_t* texture) {
    const auto key = opher_key(acquired, required);
    auto& item = opher_slots[key];
    item.texture = textures::get_texture(texture);
}
