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

#if FMT_VERSION > 90000
#include <fmt/ostream.h>

#include "storage/v2/property_value.hpp"
#include "storage/v2/storage.hpp"

template <>
class fmt::formatter<memgraph::storage::PropertyValue> : public fmt::ostream_formatter {};
template <>
class fmt::formatter<memgraph::storage::PropertyValue::Type> : public fmt::ostream_formatter {};
template <>
class fmt::formatter<memgraph::storage::Storage::Accessor::Type> : public fmt::ostream_formatter {};
#endif
