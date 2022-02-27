#pragma once

#include <macros.h>
#include <string_view>

namespace ipc
{
    using get_stat_callback = void(*)(int id, float stat);

    enum class ParameterType
    {
        Bool,
        Int,
        Float,
        String
    };

    struct Parameter
    {
        const char* name;
        void* value;
    };

    void update_pipe();
    void send_message(std::string_view message);
    void join_ipc_thread();
}

INJECT_C_DLLEXPORT int ipc_get_stat(const char* stat, ipc::get_stat_callback callback);
INJECT_C_DLLEXPORT void ipc_report_load();
INJECT_C_DLLEXPORT void ipc_report_uber_state_change(int group, int state, double value);
