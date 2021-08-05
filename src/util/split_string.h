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

#ifndef SPLIT_STRING_H_
#define SPLIT_STRING_H_

#include <array>
#include <cstring>
#include <memory>
#include <string>

namespace util {
inline std::string split_string(
    const std::string &line, int index, const char *delim) {
    constexpr auto MAX_STACK_USE_SIZE = 512;
    const auto str_len = line.length();
    const char *line_cstr = line.c_str();

    auto get_token = [line_cstr, str_len, delim, index](char *buf) {
        int ctr = 0;
        char *token = nullptr;
        char *next_token = nullptr;

        // Copy data
        std::strncpy(buf, line_cstr, str_len);

        // Ensure null termination
        if (buf[str_len] != '\0') {
            buf[str_len] = '\0';
        }

        token = strtok_r(buf, delim, &next_token);

        while (token != nullptr) {
            if (ctr == index) {
                return token;
            }

            ctr++;
            token = strtok_r(nullptr, delim, &next_token);
        }

        throw std::runtime_error("Failed to find matching index");
    };

    if (str_len < MAX_STACK_USE_SIZE) {
        // Use stack
        std::array<char, MAX_STACK_USE_SIZE> buf{};
        return std::string(get_token(buf.data()));
    } else {
        // Use heap, add one for null terminator
        auto buf = std::make_unique<char[]>(str_len + 1);
        return std::string(get_token(buf.get()));
    }
}
}  // namespace util

#endif  // SPLIT_STRING_H_