// Copyright 2025 Memgraph Ltd.
//
// Use of this software is governed by the Business Source License
// included in the file licenses/BSL.txt; by using this file, you agree to be bound by the terms of the Business Source
// License, and you may not use this file except in compliance with the Business Source License.
//
// As of the Change Date specified in that file, in accordance with
// the Business Source License, use of this software will be governed
// by the Apache License, Version 2.0, included in the file
// licenses/APL.txt.

#include "utils/uuid.hpp"

#include "slk/serialization.hpp"

#include <nlohmann/json.hpp>

namespace memgraph::utils {

void to_json(nlohmann::json &j, const UUID &uuid) { j = nlohmann::json(uuid.uuid); }

void from_json(const nlohmann::json &j, UUID &uuid) {
  auto arr = UUID::arr_t{};
  j.get_to(arr);
  uuid = UUID(arr);
}

std::string GenerateUUID() {
  uuid_t uuid;
  char decoded[37];  // magic size from: man 2 uuid_unparse
  uuid_generate(uuid);
  uuid_unparse(uuid, decoded);
  return {decoded};
}

}  // namespace memgraph::utils

// Serialize UUID
namespace memgraph::slk {
void Save(const memgraph::utils::UUID &self, memgraph::slk::Builder *builder) {
  const auto &arr = static_cast<utils::UUID::arr_t>(self);
  memgraph::slk::Save(arr, builder);
}

void Load(memgraph::utils::UUID *self, memgraph::slk::Reader *reader) { memgraph::slk::Load(&self->uuid, reader); }
}  // namespace memgraph::slk
