#include <macros.h>
#include <csharp_bridge.h>
#include <dev/object_visualizer.h>
#include <input/rando_bindings.h>
#include <system/textures.h>
#include <system/text_database.h>
#include <uber_states/uber_state_manager.h>
#include <utils/messaging.h>
#include <utils/shaders.h>

#include <Common/ext.cpp>
#include <Il2CppModLoader/common.h>
#include <Il2CppModLoader/console.h>
#include <Il2CppModLoader/interception_macros.h>
#include <Il2CppModLoader/il2cpp_helpers.h>

#include <unordered_map>
#include <unordered_set>
#include <dll_main.h>

using namespace modloader;

enum class WheelBehavior
{
    Standalone,
    Toggle
};

WheelBehavior wheel_behavior = WheelBehavior::Standalone;

INJECT_C_DLLEXPORT void refresh_wheel();

extern bool disable_has_ability_overwrite;
extern bool is_in_trial;

namespace
{
    struct CustomWheelEntry
    {
        using binding_action = void(*)(CustomWheelEntry const& entry, app::SpellUIItem* item, int binding);
        using csharp_callback = void(*)(int wheel, int item, int binding);

        std::wstring name = L"";
        std::wstring description = L"";
        std::shared_ptr<textures::TextureData> texture_data = nullptr;
        app::Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        binding_action action = nullptr;
        csharp_callback callback = nullptr;
        bool enabled = true;
    };

    struct CustomWheel
    {
        std::unordered_map<int, CustomWheelEntry> entries;
        bool sticky = false;
    };

    app::EquipmentRadialSelection* radial_selection = nullptr;
    app::CleverMenuItemSelectionManager* wheel_selection_manager = nullptr;

    bool is_wheel_visible = false;
    bool custom_wheel_input = false;
    bool custom_wheel_on = false;
    int wheel_index = 0;
    std::unordered_map<int, CustomWheel> wheels;

    IL2CPP_BINDING(, CleverMenuItemSelectionManager, int, get_MenuItemsCount, (app::CleverMenuItemSelectionManager* this_ptr));
    IL2CPP_BINDING(, CleverMenuItemSelectionManager, app::CleverMenuItem*, GetMenuItem, (app::CleverMenuItemSelectionManager* this_ptr, int index));
    STATIC_IL2CPP_BINDING(, EquipmentRadialSelection, int, GetWheelIndex, (app::EquipmentType__Enum type));

    CustomWheelEntry* get_wheel_entry(int index)
    {
        auto it = wheels.find(wheel_index);
        if (it == wheels.end())
            return nullptr;

        auto entry = it->second.entries.find(index);
        if (entry == it->second.entries.end())
            return nullptr;

        return &entry->second;
    }
    
    CustomWheelEntry* get_wheel_entry(app::EquipmentType__Enum type)
    {
        auto index = EquipmentRadialSelection::GetWheelIndex(type);
        return get_wheel_entry(index);
    }

    bool dont_fade = false;
    IL2CPP_INTERCEPT(, MoonTimelineUiFader, void, FadeIn, (app::MoonTimelineUiFader* this_ptr)) {
        if (!dont_fade)
            MoonTimelineUiFader::FadeIn(this_ptr);
    }

    void update_wheel_position();
    IL2CPP_INTERCEPT(, EquipmentWheel, void, Show, (app::EquipmentWheel* this_ptr)) {
        is_wheel_visible = true;
        EquipmentWheel::Show(this_ptr);
        update_wheel_position();
    }

    IL2CPP_INTERCEPT(, EquipmentWheel, void, ShowImmediate, (app::EquipmentWheel* this_ptr)) {
        is_wheel_visible = true;
        EquipmentWheel::ShowImmediate(this_ptr);
        update_wheel_position();
    }

    IL2CPP_INTERCEPT(, EquipmentWheel, void, Hide, (app::EquipmentWheel* this_ptr, bool change)) {
        EquipmentWheel::Hide(this_ptr, change);
        is_wheel_visible = false;
        custom_wheel_on = false;
    }

    IL2CPP_INTERCEPT(, EquipmentWheel, void, HideImmediate, (app::EquipmentWheel* this_ptr)) {
        EquipmentWheel::HideImmediate(this_ptr);
        is_wheel_visible = false;
        custom_wheel_on = false;
    }

    IL2CPP_BINDING(, MenuScreenManager, void, ShowEquipmentWheel, (app::MenuScreenManager* this_ptr));
    IL2CPP_INTERCEPT(, MenuScreenManager, void, HideEquipmentWhell, (app::MenuScreenManager* this_ptr)) {
        if (wheel_behavior == WheelBehavior::Standalone && custom_wheel_input)
            return;

        return MenuScreenManager::HideEquipmentWhell(this_ptr);
    }

    STATIC_IL2CPP_BINDING(Game, UI, bool, get_MainMenuVisible, ());
    STATIC_IL2CPP_BINDING(Game, UI, bool, get_WorldMapVisible, ());
    STATIC_IL2CPP_BINDING(Game, UI, bool, get_ShardShopVisible, ());
    STATIC_IL2CPP_BINDING(Game, UI, bool, IsInventoryVisible, ());
    bool can_show_wheel()
    {
        if (wheels.empty() || wheels[wheel_index].entries.empty())
            return false;

        if (!is_wheel_visible &&
            (UI::get_MainMenuVisible() ||
            UI::get_WorldMapVisible() ||
            UI::get_ShardShopVisible() ||
            UI::IsInventoryVisible()))
            return false;

        return !is_in_trial;
    }

    void handle_custom_wheel(input::Action action, bool pressed)
    {
        if (pressed)
        {
            if (!can_show_wheel())
                return;

            auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
            switch (wheel_behavior)
            {
            case WheelBehavior::Standalone:
                custom_wheel_input = true;
                if (is_wheel_visible)
                    refresh_wheel();
                else
                {
                    auto* msm = il2cpp::get_class<app::UI__Class>("Game", "UI")->static_fields->m_sMenu;
                    MenuScreenManager::ShowEquipmentWheel(msm);
                }

                break;
            case WheelBehavior::Toggle:
                // TODO: implement toggle behavior
                break;
            }
        }
        else
        {
            if (wheels.empty() || wheels[wheel_index].entries.empty())
                return;

            auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
            switch (wheel_behavior)
            {
            case WheelBehavior::Standalone:
            {
                custom_wheel_input = false;

                if (!il2cpp::get_nested_class<app::Input_Cmd__Class>("Core", "Input", "Cmd")->static_fields->OpenWeaponWheel->fields.IsPressed)
                {
                    auto* msm = il2cpp::get_class<app::UI__Class>("Game", "UI")->static_fields->m_sMenu;
                    MenuScreenManager::HideEquipmentWhell(msm);
                }
                else
                    refresh_wheel();

                if (!wheels[wheel_index].sticky)
                    wheel_index = 0;

                break;
            }
            case WheelBehavior::Toggle:
                // TODO: implement toggle behavior
                break;
            }
        }
    }

    void initialize_wheel()
    {
        input::add_on_pressed_callback(input::Action::OpenRandoWheel, handle_custom_wheel);
        input::add_on_released_callback(input::Action::OpenRandoWheel, handle_custom_wheel);
    }

    bool override_set_active = false;
    bool override_set_active_value = false;
    IL2CPP_INTERCEPT(, CleverMenuItem, void, RefreshVisible, (app::CleverMenuItem* this_ptr)) {
        if (custom_wheel_on && this_ptr->fields.m_selectionManager == wheel_selection_manager)
        {
            override_set_active = true;
            override_set_active_value = true;
        }

        CleverMenuItem::RefreshVisible(this_ptr);
        override_set_active = false;
    }

    DECLARE_INTERCEPT(, EquipmentWheelUIDetails, void, UpdateContext, (app::EquipmentWheelUIDetails* this_ptr, bool to_right));
    IL2CPP_INTERCEPT(, EquipmentRadialSelection, void, Populate, (app::EquipmentRadialSelection* this_ptr, app::List_1_System_Object_ inventory_items, app::Object* grid_context)) {
        wheel_selection_manager = this_ptr->fields.m_navigationManager;
        custom_wheel_on = !wheels.empty() && custom_wheel_input;
        if (custom_wheel_on)
        {
            // Cache the selection manager and its items so we can modify their behavior later.
            radial_selection = this_ptr;
            wheel_selection_manager->fields.KeepSelectedItemActiveWhenInactive = false;
            wheel_selection_manager->fields.KeepMouseInteractionsWhenInactive = false;
            wheel_selection_manager->fields.AlwaysHighlightCurrentMenuItem = false;
            wheel_selection_manager->fields.CheckIfActiveWhenSettingIndexToFirst = true;
        }

        EquipmentRadialSelection::Populate(this_ptr, inventory_items, grid_context);

        auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
        EquipmentWheelUIDetails::UpdateContext_intercept(wheel->fields.EquipmentDetailsCanvas, false);
        const int count = CleverMenuItemSelectionManager::get_MenuItemsCount(wheel_selection_manager);
        if (custom_wheel_on)
        {
            for (int i = 0; i < count; ++i)
            {
                auto* menu_item = CleverMenuItemSelectionManager::GetMenuItem(wheel_selection_manager, i);
                menu_item->fields.m_selectionManager = wheel_selection_manager;
            }
        }
    }

    IL2CPP_INTERCEPT(UnityEngine, GameObject, void, SetActive, (app::GameObject* this_ptr, bool value)) {
        if (override_set_active)
            value = override_set_active_value;

        GameObject::SetActive(this_ptr, value);
    }

    IL2CPP_INTERCEPT(, CleverMenuItem, bool, get_IsVisible, (app::CleverMenuItem* this_ptr)) {
        if (custom_wheel_on && this_ptr->fields.m_selectionManager == wheel_selection_manager)
            return true;

        return CleverMenuItem::get_IsVisible(this_ptr);
    }

    IL2CPP_INTERCEPT(, CleverMenuItem, bool, get_IsActivated, (app::CleverMenuItem* this_ptr)) {
        if (custom_wheel_on && this_ptr->fields.m_selectionManager == wheel_selection_manager)
            return true;
    
        return CleverMenuItem::get_IsActivated(this_ptr);
    }

    // Only used the first time you use the wheel.
    STATIC_IL2CPP_INTERCEPT(, EquipmentWheel, bool, HasElement, (app::EquipmentType__Enum type)) {
        if (custom_wheel_on)
        {
            auto* entry = get_wheel_entry(type);
            return entry != nullptr && entry->enabled;
        }

        return EquipmentWheel::HasElement(type);
    }

    STATIC_IL2CPP_BINDING(UnityEngine, Vector3, float, Distance, (app::Vector3* a, app::Vector3* b));
    STATIC_IL2CPP_BINDING(Core, Input, app::Vector2, get_CursorPositionUI, ());
    IL2CPP_BINDING(, CleverMenuItem, app::Rect, get_Bounds, (app::CleverMenuItem* this_ptr));
    IL2CPP_INTERCEPT(, CleverMenuItemSelectionManager, app::CleverMenuItem*, get_CleverMenuItemUnderCursor, (app::CleverMenuItemSelectionManager* this_ptr)) {
        disable_has_ability_overwrite = true;
        const int count = CleverMenuItemSelectionManager::get_MenuItemsCount(this_ptr);
        auto cursor = Input::get_CursorPositionUI();
        app::CleverMenuItem* item = nullptr;
        float distance = INFINITY;

        for (int i = 0; i < count; ++i)
        {
            auto* current_item = CleverMenuItemSelectionManager::GetMenuItem(this_ptr, i);
            // This is the only meaningful change, we use get_IsActivated instead of calling the Activated delegate directly.
            if (!CleverMenuItem::get_IsVisible_intercept(current_item) || !CleverMenuItem::get_IsActivated_intercept(current_item))
                continue;

            auto item_bounds = CleverMenuItem::get_Bounds(current_item);
            if ((item_bounds.m_XMin > cursor.x) ||
                (cursor.x >= item_bounds.m_Width + item_bounds.m_XMin) ||
                (item_bounds.m_YMin > cursor.y) ||
                (cursor.y >= item_bounds.m_YMin + item_bounds.m_Height))
                continue;
            
            app::Vector3 cursor_v3{ cursor.x, cursor.y, 0.0f };
            app::Vector3 center_v3{ item_bounds.m_XMin + item_bounds.m_Width / 2.0f, item_bounds.m_YMin + item_bounds.m_Height / 2.0f, 0.0f };
            float new_distance = Vector3::Distance(&center_v3, &cursor_v3);
            if (new_distance < distance) {
                item = current_item;
                distance = new_distance;
            }
        }

        disable_has_ability_overwrite = false;
        return item;
    }

    IL2CPP_BINDING(, MessageBox, void, RefreshText, (app::MessageBox* this_ptr));
    IL2CPP_INTERCEPT(, EquipmentWheelUIDetails, void, UpdateContext, (app::EquipmentWheelUIDetails* this_ptr, bool to_right)) {
        if (custom_wheel_on)
        {
            auto* name_message_box = il2cpp::unity::get_components<app::MessageBox>(this_ptr->fields.NameGO, "", "MessageBox")[0];
            auto* description_message_box = il2cpp::unity::get_components<app::MessageBox>(this_ptr->fields.DescriptionGO, "", "MessageBox")[0];
            auto* description_text_box = il2cpp::unity::get_components<app::TextBox>(this_ptr->fields.DescriptionGO, "CatlikeCoding.TextBox", "TextBox")[0];
            description_text_box->fields.maxHeight = 4.00000000;

            CustomWheelEntry* entry = nullptr;
            if (this_ptr->fields.m_item != nullptr)
                entry = get_wheel_entry(this_ptr->fields.m_item->fields.m_type);

            if (entry != nullptr)
            {
                name_message_box->fields.MessageProvider = utils::create_message_provider(entry->name);
                description_message_box->fields.MessageProvider = utils::create_message_provider(entry->description);
            }
            else
            {
                name_message_box->fields.MessageProvider = text_database::get_provider(*static_text_entries::EmptyName);
                description_message_box->fields.MessageProvider = text_database::get_provider(*static_text_entries::Empty);
            }

            GameObject::SetActive(this_ptr->fields.UsesEnergyGO, false);
            GameObject::SetActive(this_ptr->fields.DrainsEnergyGO, false);
            MessageBox::RefreshText(name_message_box);
            MessageBox::RefreshText(description_message_box);
        }
        else
            EquipmentWheelUIDetails::UpdateContext(this_ptr, to_right);
    }

    IL2CPP_BINDING(UnityEngine, MeshFilter, app::Mesh*, get_mesh, (app::MeshFilter* this_ptr));
    IL2CPP_BINDING(UnityEngine, Mesh, app::Vector2__Array*, get_uv, (app::Mesh* this_ptr));
    IL2CPP_INTERCEPT(, SpellUIItem, void, UpdateSpellIcon, (app::SpellUIItem* this_ptr)) {
        auto* renderer = il2cpp::unity::get_components<app::Renderer>(this_ptr->fields.IconGO, "UnityEngine", "Renderer")[0];
        if (custom_wheel_on)
        {
            CustomWheelEntry* entry = this_ptr->fields.m_spell != nullptr ? get_wheel_entry(this_ptr->fields.m_spell->fields.m_type) : nullptr;
            if (entry == nullptr)
            {
                textures::apply_default(renderer);
                SpellUIItem::UpdateSpellIcon(this_ptr);
                return;
            }

            if (entry->texture_data == nullptr)
            {
                entry->texture_data = textures::create_texture();
                auto* spell_settings = il2cpp::get_class<app::SpellSettings__Class>("", "SpellSettings");
                auto* icons = spell_settings->static_fields->Instance->fields.Icons;
                entry->texture_data->set_texture(reinterpret_cast<app::Texture*>(icons->fields._.Missing.InventoryIcon));
            }

            entry->texture_data->apply(renderer);
        }
        else
        {
            textures::apply_default(renderer);
            SpellUIItem::UpdateSpellIcon(this_ptr);
        }
    }

    IL2CPP_INTERCEPT(, SpellUIItem, void, UpdateSpellProperties, (app::SpellUIItem* this_ptr, bool initialize)) {
        //CustomWheelEntry* entry = this_ptr->fields.m_spell != nullptr ? get_wheel_entry(this_ptr->fields.m_spell->fields.m_type) : nullptr;
        if (custom_wheel_on)
        {
            GameObject::SetActive(this_ptr->fields.EquippedGOB, false);
            GameObject::SetActive(this_ptr->fields.EquippedGOX, false);
            GameObject::SetActive(this_ptr->fields.EquippedGOY, false);
            GameObject::SetActive(this_ptr->fields.EquippedShared, false);
            GameObject::SetActive(this_ptr->fields.EnergyGO, false);
            GameObject::SetActive(this_ptr->fields.NewGO, false);
        }
        else
            SpellUIItem::UpdateSpellProperties(this_ptr, initialize);
    }

    IL2CPP_BINDING(, EquipmentWheel, app::SpellUIItem*, get_SelectedSpellUIItem, (app::EquipmentWheel* this_ptr));
    IL2CPP_INTERCEPT(, EquipmentWheel, void, OnPressButton, (app::EquipmentWheel* this_ptr, app::SpellInventory_Binding__Enum binding)) {
        if (custom_wheel_on)
        {
            auto* item = EquipmentWheel::get_SelectedSpellUIItem(this_ptr);
            if (item != nullptr && item->fields.m_spell != nullptr)
            {
                auto* entry = get_wheel_entry(item->fields.m_spell->fields.m_type);
                if (entry != nullptr && entry->action != nullptr)
                    entry->action(*entry, item, binding);
            }
        }
        else
            EquipmentWheel::OnPressButton(this_ptr, binding);
    }

    // Could technically add a 4th button here.
    //IL2CPP_INTERCEPT(, CleverMenuItem, void, OnPressed, (app::CleverMenuItem* this_ptr)) {
    //    CleverMenuItem::OnPressed(this_ptr);
    //    if (custom_wheel_on && this_ptr->fields.m_selectionManager == wheel_selection_manager)
    //    {
    //        auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
    //        auto* item = EquipmentWheel::get_SelectedSpellUIItem(wheel);
    //        if (item != nullptr && item->fields.m_spell != nullptr)
    //        {
    //            auto* entry = get_wheel_entry(item->fields.m_spell->fields.m_type);
    //            if (entry != nullptr && entry->action != nullptr)
    //                entry->action(*entry, item, 3);
    //        }
    //    }
    //}

    void csharp_action(CustomWheelEntry const& entry, app::SpellUIItem* item, int binding) {
        auto index = EquipmentRadialSelection::GetWheelIndex(item->fields.m_spell->fields.m_type);
        entry.callback(wheel_index, index, binding);

        // Refresh things.
        auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
        EquipmentWheelUIDetails::UpdateContext_intercept(wheel->fields.EquipmentDetailsCanvas, false);
        SpellUIItem::UpdateSpellIcon_intercept(item);
    }
    
    bool is_valid_wheel_index(int wheel, int item)
    {
        return wheel >= 0 && item >= 0 && item < 12;
    }

    void add_wheel_item(int wheel, int item, std::wstring_view name, std::wstring_view description, std::wstring_view texture, CustomWheelEntry::binding_action action)
    {
        auto& entry = wheels[wheel].entries[item];
        entry.name = name;
        entry.description = description;
        entry.enabled = true;
        entry.texture_data = textures::get_texture(texture);
        entry.callback = nullptr;
        entry.action = action;
    }

    CALL_ON_INIT(initialize_wheel);

    IL2CPP_BINDING(, SeinCharacter, app::Vector3, get_Position, (app::SeinCharacter* thisPtr));
    IL2CPP_BINDING(, CleverMenuItemSelectionManager, app::Vector2, get_MenuItemAxis, (app::CleverMenuItemSelectionManager* this_ptr));
    IL2CPP_BINDING(, CleverMenuItemSelectionManager, void, SetCurrentMenuItem, (app::CleverMenuItemSelectionManager* this_ptr, app::CleverMenuItem* item, bool run_actions));
    IL2CPP_BINDING(, CleverMenuItemSelectionManager, void, set_IsHighlightVisible, (app::CleverMenuItemSelectionManager* this_ptr, bool value));
    IL2CPP_BINDING(, CleverMenuItemSelectionManager, void, SetCurrentItem, (app::CleverMenuItemSelectionManager* this_ptr, int index, bool run_actions));
    IL2CPP_BINDING(, CleverMenuItem, void, OnHighlight, (app::CleverMenuItem* this_ptr, bool run_actions));
    IL2CPP_BINDING(UnityEngine, Transform, app::Vector3, get_position, (app::Transform* this_ptr));
    NESTED_STATIC_IL2CPP_BINDING(, MoonMath, Line, float, DistancePointToLine2D, (app::Vector3* p1, app::Vector3* p2, app::Vector3* p))

    void select_closest(app::CleverMenuItemSelectionManager* manager, app::Vector2& axis)
    {
        auto magnitude = sqrtf(axis.x * axis.x + axis.y * axis.y);
        if (magnitude < 0.2f)
            return;

        auto line_p1 = Transform::get_position(il2cpp::unity::get_transform(il2cpp::unity::get_game_object(manager)));
        app::Vector3 line_p2{ line_p1.x + axis.x / magnitude, line_p1.y + axis.y / magnitude, 0.0f };
        float distance = INFINITY;
        auto closest = -1;
        auto i = 0;

        for (; i < manager->fields.m_menuItems->fields._size; ++i)
        {
            auto item = manager->fields.m_menuItems->fields._items->vector[i];
            auto item_bounds = CleverMenuItem::get_Bounds(item);
            app::Vector3 center_v3{ item_bounds.m_XMin + item_bounds.m_Width / 2.0f, item_bounds.m_YMin + item_bounds.m_Height / 2.0f, 0.0f };
            auto i_distance = MoonMath::Line::DistancePointToLine2D(&line_p1, &line_p2, &center_v3);
            if (i_distance < distance)
            {
                closest = i;
                distance = i_distance;
            }
        }

        CleverMenuItemSelectionManager::set_IsHighlightVisible(manager, closest != -1);
        CleverMenuItemSelectionManager::SetCurrentItem(manager, closest, closest != -1);
        il2cpp::invoke(manager->fields.OnRadialItemChanged, "Invoke");
    }

    IL2CPP_INTERCEPT(, CleverMenuItemSelectionManager, void, RefreshVisible, (app::CleverMenuItemSelectionManager* this_ptr)) {
        CleverMenuItemSelectionManager::RefreshVisible(this_ptr);
        // This is stupid but required because this function is called in a lambda.
        if (is_wheel_visible)
            update_wheel_position();
    }

    void update_wheel_position()
    {
        auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
        auto* manager = wheel->fields.RadialSelection->fields.m_navigationManager;

        // Trigger movement so wheel updates selection after refresh.
        auto scheme = il2cpp::get_class<app::GameSettings__Class>("", "GameSettings")->static_fields->Instance->fields.m_currentControlSchemes;
        switch (scheme)
        {
        case app::ControlScheme__Enum_Switch:
        case app::ControlScheme__Enum_Controller:
        case app::ControlScheme__Enum_Keyboard:
            // TODO: Maybe use some other axis.
            select_closest(manager, manager->fields.m_lastMenuAxis);
            break;
        case app::ControlScheme__Enum_KeyboardAndMouse:
            auto item = CleverMenuItemSelectionManager::get_CleverMenuItemUnderCursor_intercept(manager);
            if (il2cpp::unity::is_valid(item))
            {
                CleverMenuItemSelectionManager::SetCurrentMenuItem(manager, item, true);
                CleverMenuItem::OnHighlight(item, true);
            }
            break;
        }
    }
}

INJECT_C_DLLEXPORT bool set_wheel_item_name(int wheel, int item, const wchar_t* name)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    wheels[wheel].entries[item].name = name;
    return true;
}

INJECT_C_DLLEXPORT bool set_wheel_item_description(int wheel, int item, const wchar_t* description)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    wheels[wheel].entries[item].description = description;
    return true;
}

INJECT_C_DLLEXPORT bool set_wheel_item_texture(int wheel, int item, const wchar_t* texture)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    std::wstring texture_name(texture);
    auto& entry = wheels[wheel].entries[item];
    if (texture_name.empty())
        entry.texture_data = nullptr;
    else
    {
        entry.texture_data = textures::get_texture(texture);
        if (entry.texture_data == nullptr)
        {
            auto texture_str = convert_wstring_to_string(texture);
            warn("wheel", format("failed to find texture %s", texture_str.c_str()));
            return false;
        }
        else
            entry.texture_data->set_color(entry.color);
    }

    return true;
}

INJECT_C_DLLEXPORT bool set_wheel_item_color(int wheel, int item, int r, int g, int b, int a)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    if (r < 0 || 255 < r || g < 0 || 255 < g || b < 0 || 255 < b || a < 0 || 255 < a)
    {
        warn("wheel", format("invalid color passed to wheel [%d, %d]: (%d, %d, %d, %d)", wheel, item, r, g, b, a));
        r = std::max(std::min(r, 255), 0);
        g = std::max(std::min(g, 255), 0);
        b = std::max(std::min(b, 255), 0);
        a = std::max(std::min(a, 255), 0);
    }

    auto& entry = wheels[wheel].entries[item];
    entry.color = app::Color{ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
    if (entry.texture_data != nullptr)
        entry.texture_data->set_color(entry.color);

    return true;
}

INJECT_C_DLLEXPORT bool set_wheel_item_enabled(int wheel, int item, bool enabled)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    wheels[wheel].entries[item].enabled = enabled;
    return true;
}

INJECT_C_DLLEXPORT bool set_wheel_item_callback(int wheel, int item, uint64_t callback)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    auto& entry = wheels[wheel].entries[item];
    entry.action = csharp_action;
    entry.callback = reinterpret_cast<CustomWheelEntry::csharp_callback>(callback);
    return true;
}

INJECT_C_DLLEXPORT bool clear_wheel_item(int wheel, int item)
{
    if (!is_valid_wheel_index(wheel, item))
    {
        warn("wheel", format("invalid wheel index [%d, %d] in command", wheel, item));
        return false;
    }

    wheels[wheel].entries.erase(item);
    return true;
}

INJECT_C_DLLEXPORT void refresh_wheel()
{
    if (is_wheel_visible)
    {
        dont_fade = true;
        auto wheel = il2cpp::get_class<app::EquipmentWheel__Class>("", "EquipmentWheel")->static_fields->Instance;
        EquipmentWheel::ShowImmediate_intercept(wheel);
        dont_fade = false;
    }
}

INJECT_C_DLLEXPORT bool set_active_wheel(int wheel)
{
    auto it = wheels.find(wheel);
    if (it == wheels.end())
    {
        warn("wheel", format("Wheel [%d] does not exist", wheel));
        return false;
    }

    wheel_index = wheel;
    refresh_wheel();
    return true;
}

INJECT_C_DLLEXPORT void set_wheel_sticky(int wheel, bool value)
{
    wheels[wheel].sticky = value;
}

INJECT_C_DLLEXPORT void set_wheel_behavior(int behavior)
{
    wheel_behavior = static_cast<WheelBehavior>(behavior);
}

// For cleanup.
INJECT_C_DLLEXPORT void clear_wheels()
{
    custom_wheel_input = false;
    custom_wheel_on = false;
    wheel_index = 0;
    wheels.clear();
}
