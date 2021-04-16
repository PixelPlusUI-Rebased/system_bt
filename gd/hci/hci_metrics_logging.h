/*
 * Copyright 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "hci/hci_packets.h"

namespace bluetooth {
namespace hci {
void log_link_layer_connection_hci_event(std::unique_ptr<CommandView>& command_view, EventView packet);
void log_link_layer_connection_command_status(std::unique_ptr<CommandView>& command_view, ErrorCode status);
void log_link_layer_connection_command_complete(EventView event, std::unique_ptr<CommandView>& command_view);
void log_link_layer_connection_event_le_meta(LeMetaEventView le_meta_event_view);
void log_link_layer_connection_other_hci_event(EventView packet);

}  // namespace hci
}  // namespace bluetooth