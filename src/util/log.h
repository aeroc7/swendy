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

#ifndef SOURCE_LOG_H_
#define SOURCE_LOG_H_

#include <cstring>
#include <iostream>
#include <source_location>

constexpr auto SWENDY_HEADER = "Swendy";

namespace util {
class Logger {
public:
    struct LoggerData {
        LoggerData(Logger &,
            std::source_location loc = std::source_location::current()) noexcept {
            *this << SWENDY_HEADER << " [" << filename_split(loc.file_name())
                  << ':' << loc.line() << "]: ";
        }

    private:
        constexpr std::string_view filename_split(std::string_view path) const noexcept {
            const auto last_path_sep = path.find_last_of("/");
            return std::string_view(
                path.data() + last_path_sep + 1, path.length() - last_path_sep);
        }
    };

    template <typename T>
    friend LoggerData operator<<(LoggerData ld, const T &msg) noexcept {
        std::cout << msg;
        return ld;
    }
};

extern Logger log;
}  // namespace util

#endif  // SOURCE_LOG_H_