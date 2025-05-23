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

#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>

#include <nlohmann/json_fwd.hpp>

namespace memgraph::query::stream {

inline constexpr std::chrono::milliseconds kDefaultBatchInterval{100};
inline constexpr int64_t kDefaultBatchSize{1000};

template <typename TMessage>
using ConsumerFunction = std::function<void(const std::vector<TMessage> &)>;

struct CommonStreamInfo {
  std::chrono::milliseconds batch_interval;
  int64_t batch_size;
  std::string transformation_name;
};

template <typename T>
concept ConvertableToJson = requires(T value, nlohmann::json data) {
  { to_json(data, std::move(value)) } -> std::same_as<void>;
  { from_json(data, value) } -> std::same_as<void>;
};

enum class StreamSourceType : uint8_t { KAFKA, PULSAR };

constexpr std::string_view StreamSourceTypeToString(StreamSourceType type) {
  switch (type) {
    case StreamSourceType::KAFKA:
      return "kafka";
    case StreamSourceType::PULSAR:
      return "pulsar";
  }
}

template <typename T>
StreamSourceType StreamType(const T & /*stream*/);

const std::string kCommonInfoKey = "common_info";

void to_json(nlohmann::json &data, CommonStreamInfo &&info);
void from_json(const nlohmann::json &data, CommonStreamInfo &common_info);
}  // namespace memgraph::query::stream
