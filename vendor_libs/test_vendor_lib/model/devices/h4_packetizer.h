//
// Copyright 2017 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#pragma once

#include <functional>
#include <vector>

#include "hci.h"
#include "hci_protocol.h"

namespace test_vendor_lib {
namespace hci {

using HciPacketReadyCallback = std::function<void(void)>;
using ClientDisconnectCallback = std::function<void()>;

class H4Packetizer : public HciProtocol {
 public:
  H4Packetizer(int fd, PacketReadCallback command_cb, PacketReadCallback event_cb, PacketReadCallback acl_cb,
               PacketReadCallback sco_cb, ClientDisconnectCallback disconnect_cb);

  size_t Send(uint8_t type, const uint8_t* data, size_t length) override;

  void OnPacketReady();

  void OnDataReady(int fd);

  // 2 bytes for opcode, 1 byte for parameter length (Volume 2, Part E, 5.4.1)
  static constexpr size_t COMMAND_PREAMBLE_SIZE = 3;
  static constexpr size_t COMMAND_LENGTH_OFFSET = 2;

  // 2 bytes for handle, 2 bytes for data length (Volume 2, Part E, 5.4.2)
  static constexpr size_t ACL_PREAMBLE_SIZE = 4;
  static constexpr size_t ACL_LENGTH_OFFSET = 2;

  // 2 bytes for handle, 1 byte for data length (Volume 2, Part E, 5.4.3)
  static constexpr size_t SCO_PREAMBLE_SIZE = 3;
  static constexpr size_t SCO_LENGTH_OFFSET = 2;

  // 1 byte for event code, 1 byte for parameter length (Volume 2, Part
  // E, 5.4.4)
  static constexpr size_t EVENT_PREAMBLE_SIZE = 2;
  static constexpr size_t EVENT_LENGTH_OFFSET = 1;

 private:
  int uart_fd_;

  PacketReadCallback command_cb_;
  PacketReadCallback event_cb_;
  PacketReadCallback acl_cb_;
  PacketReadCallback sco_cb_;

  ClientDisconnectCallback disconnect_cb_;
  bool disconnected_{false};

  hci::PacketType hci_packet_type_{hci::PacketType::UNKNOWN};

  enum State { HCI_TYPE, HCI_PREAMBLE, HCI_PAYLOAD };
  State state_{HCI_TYPE};
  uint8_t packet_type_{};
  std::vector<uint8_t> packet_;
  size_t bytes_read_{0};
};

}  // namespace hci
}  // namespace test_vendor_lib
