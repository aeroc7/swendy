// Copyright 2021 Bennett Anderson
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STR_TO_NUM_H_
#define STR_TO_NUM_H_

#include "log.h"

#include <charconv>
#include <string>

namespace util {
template <typename T>
inline T str_to_num(const std::string &str) noexcept {
    T value;
    const auto [ptr, ec] =
        std::from_chars(str.data(), str.data() + str.size(), value);

    if (ec == std::errc()) {
        return value;
    }

    log << "Failed to convert " << str << " value" << '\n';
    return {};
}
}  // namespace util

#endif  // STR_TO_NUM_H_