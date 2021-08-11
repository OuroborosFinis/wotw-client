#include <Il2CppModLoader/common.h>
#include <Il2CppModLoader/console.h>
#include <Il2CppModLoader/interception_macros.h>
#include <Il2CppModLoader/il2cpp_helpers.h>

#include <uber_states/uber_state_manager.h>

#include <unordered_set>

namespace
{
    const bool log_switch = true;

    const std::unordered_set<std::string> damage_overrides {
                "winterForestBreakableIceA",
                "winterForestBreakableIceB",
                "winterForestBreakableIceC",
                "winterForestBreakableIceD",
                "winterForestBreakableIceE",
                "orbBulb",
    };

    const std::unordered_map<app::DamageType__Enum, int> damage_override_states{
        { app::DamageType__Enum_Bow, 70 },
        { app::DamageType__Enum_Blaze, 71 },
        { app::DamageType__Enum_Sword, 72 },
        { app::DamageType__Enum_Hammer, 73 },
        { app::DamageType__Enum_SpiritSpear, 74 },
        { app::DamageType__Enum_Chakram, 75 },
    };

    bool is_overridden(const app::DamageType__Enum damage_type)
    {
        const auto it = damage_override_states.find(damage_type);
        return it != damage_override_states.end() &&
            (uber_states::get_uber_state_value(uber_states::constants::RANDO_UPGRADE_GROUP_ID, it->second) > 0.5f);
    }

    IL2CPP_INTERCEPT(, AttackableSwitch, bool, DoesReactTo, (app::AttackableSwitch* this_ptr, app::DamageType__Enum damage_type)) {
        if (log_switch)
        {
            auto* parent = il2cpp::unity::get_parent(il2cpp::unity::get_transform(il2cpp::unity::get_game_object(this_ptr)));
            const auto parent_name = il2cpp::unity::get_object_name(parent);
            const auto name = il2cpp::unity::get_object_name(this_ptr);
            modloader::console::console_send("parent: " + parent_name + ", switch: " + name + ", react to: " + std::to_string(damage_type));
        }

        if (is_overridden(damage_type))
        {
            auto* parent = il2cpp::unity::get_parent(il2cpp::unity::get_transform(il2cpp::unity::get_game_object(this_ptr)));
            const auto parent_name = il2cpp::unity::get_object_name(parent);
            if (damage_overrides.find(parent_name) != damage_overrides.end())
                return true;
        }

        return AttackableSwitch::DoesReactTo(this_ptr, damage_type);
    }
}
