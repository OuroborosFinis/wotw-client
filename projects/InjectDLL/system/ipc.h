#pragma once

#include <input/rando_bindings.h>

#include <macros.h>
#include <string_view>

namespace ipc
{
    void update_pipe();
    void send_message(std::string_view message);
    void join_ipc_thread();
}

INJECT_C_DLLEXPORT void report_seed_reload();
INJECT_C_DLLEXPORT void report_load();
INJECT_C_DLLEXPORT void report_uber_state_change(int group, int state, double value);
INJECT_C_DLLEXPORT void report_input(input::Action type, bool pressed);
