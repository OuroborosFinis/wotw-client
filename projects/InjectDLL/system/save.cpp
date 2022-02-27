#include <dll_main.h>
#include <ipc.h>
#include <macros.h>
#include <csharp_bridge.h>
#include <features/instantiate_objects.h>
#include <pickups/pickups.h>
#include <system/textures.h>
#include <uber_states/state_applier.h>
#include <uber_states/uber_state_manager.h>

#include <Il2CppModLoader/common.h>
#include <Il2CppModLoader/interception_macros.h>

#include <guiddef.h>
#include <combaseapi.h>

using namespace modloader;

extern bool temporary_glide_switch;

namespace
{
    void handle_enter_switches()
    {
        if (temporary_glide_switch)
            set_ability(app::AbilityType__Enum_Glide, false);
    }

    void handle_exit_switches()
    {
        if (temporary_glide_switch)
            set_ability(app::AbilityType__Enum_Glide, true);
    }

    STATIC_IL2CPP_BINDING(, SaveSlotsManager, int, get_CurrentSlotIndex, ());
    STATIC_IL2CPP_BINDING(, SaveSlotsManager, int, get_BackupIndex, ());

    IL2CPP_INTERCEPT(, GameController, void, CreateCheckpoint, (app::GameController* thisPtr, bool doPerformSave, bool respectRestrictCheckpointZone)) {
        handle_enter_switches();
        bool c = collecting_pickup; // fuck fuck fuck shit damn aaaaa
        collecting_pickup = false;
        csharp_bridge::on_checkpoint();
        collecting_pickup = c;
        GameController::CreateCheckpoint(thisPtr, doPerformSave, respectRestrictCheckpointZone);
        handle_exit_switches();
    }

    IL2CPP_BINDING(Moon, SerializedIntUberState, void, set_Value, (app::SerializedIntUberState* this_ptr, int value));
    IL2CPP_INTERCEPT(, NewGameAction, void, Perform, (app::NewGameAction* this_ptr, app::IContext* context)) {
        GUID gid;
        CoCreateGuid(&gid);
        auto part_A_value = static_cast<int>(gid.Data1);
        auto part_B_value = static_cast<int>(static_cast<unsigned long>(gid.Data2) << 16 | gid.Data3);
        auto part_C_value = static_cast<int>(
            (static_cast<unsigned long>(gid.Data4[0]) << 24) |
            (static_cast<unsigned long>(gid.Data4[1]) << 16) |
            (static_cast<unsigned long>(gid.Data4[2]) << 8) |
            static_cast<unsigned long>(gid.Data4[3])
            );
        auto part_D_value = static_cast<int>(
            (static_cast<unsigned long>(gid.Data4[4]) << 24) |
            (static_cast<unsigned long>(gid.Data4[5]) << 16) |
            (static_cast<unsigned long>(gid.Data4[6]) << 8) |
            static_cast<unsigned long>(gid.Data4[7])
            );

        auto part_A = uber_states::get_uber_state<app::SerializedIntUberState>(uber_states::constants::RANDO_STATE_GROUP_ID, 50000);
        auto part_B = uber_states::get_uber_state<app::SerializedIntUberState>(uber_states::constants::RANDO_STATE_GROUP_ID, 50001);
        auto part_C = uber_states::get_uber_state<app::SerializedIntUberState>(uber_states::constants::RANDO_STATE_GROUP_ID, 50002);
        auto part_D = uber_states::get_uber_state<app::SerializedIntUberState>(uber_states::constants::RANDO_STATE_GROUP_ID, 50003);

        SerializedIntUberState::set_Value(part_A, part_A_value);
        SerializedIntUberState::set_Value(part_B, part_B_value);
        SerializedIntUberState::set_Value(part_C, part_C_value);
        SerializedIntUberState::set_Value(part_D, part_D_value);

        csharp_bridge::new_game(SaveSlotsManager::get_CurrentSlotIndex());
        NewGameAction::Perform(this_ptr, context);
        perform_preload();
        uber_states::load_dynamic_redirects();
        ipc_report_load();
    }

    IL2CPP_INTERCEPT(, SaveGameController, void, SaveToFile, (app::SaveGameController* thisPtr, int32_t slotIndex, int32_t backupIndex, app::Byte__Array* bytes)) {
        handle_enter_switches();
        uber_states::save_dynamic_redirects();
        csharp_bridge::on_save(slotIndex, backupIndex);
        SaveGameController::SaveToFile(thisPtr, slotIndex, backupIndex, bytes);
        handle_exit_switches();
    }

    IL2CPP_INTERCEPT(, SaveSlotBackupsManager, void, PerformBackup, (app::SaveSlotBackupsManager* thisPtr, app::SaveSlotBackup* saveSlot, int32_t backupIndex, app::String* backupName)) {
        handle_enter_switches();
        uber_states::save_dynamic_redirects();
        csharp_bridge::on_save(saveSlot->fields.Index, backupIndex);
        SaveSlotBackupsManager::PerformBackup(thisPtr, saveSlot, backupIndex, backupName);
        handle_exit_switches();
    }

    IL2CPP_INTERCEPT(, SaveGameController, void, OnFinishedLoading, (app::SaveGameController* thisPtr)) {
        csharp_bridge::on_load(SaveSlotsManager::get_CurrentSlotIndex(), SaveSlotsManager::get_BackupIndex());
        SaveGameController::OnFinishedLoading(thisPtr);
        perform_preload();
        uber_states::load_dynamic_redirects();
        ipc_report_load();
    }

    IL2CPP_INTERCEPT(, SaveGameController, void, RestoreCheckpoint, (app::SaveGameController* thisPtr)) {
        csharp_bridge::on_load(SaveSlotsManager::get_CurrentSlotIndex(), SaveSlotsManager::get_BackupIndex());
        SaveGameController::RestoreCheckpoint(thisPtr);
        perform_preload();
        uber_states::load_dynamic_redirects();
        ipc_report_load();
    }

    IL2CPP_INTERCEPT(, SeinHealthController, void, OnRespawn, (app::SeinHealthController* thisPtr)) {
        csharp_bridge::on_load(SaveSlotsManager::get_CurrentSlotIndex(), SaveSlotsManager::get_BackupIndex());
        SeinHealthController::OnRespawn(thisPtr);
        uber_states::load_dynamic_redirects();
        ipc_report_load();
    }

    STATIC_IL2CPP_INTERCEPT(, SaveSlotsManager, void, CopySlot, (int32_t from, int32_t to)) {
        SaveSlotsManager::CopySlot(from, to);
        csharp_bridge::on_copy(from, to);
    }

    STATIC_IL2CPP_INTERCEPT(, SaveSlotsManager, void, DeleteSlot, (int32_t index)) {
        SaveSlotsManager::DeleteSlot(index);
        csharp_bridge::on_delete(index);
    }
}

INJECT_C_DLLEXPORT void save()
{
    trace(MessageType::Info, 3, "csharp_interop", "Save requested by c# code");
    GameController::CreateCheckpoint(get_game_controller(), true, false);
}

INJECT_C_DLLEXPORT void checkpoint()
{
    trace(MessageType::Info, 3, "csharp_interop", "Checkpoint requested by c# code");
    GameController::CreateCheckpoint(get_game_controller(), false, false);
}
