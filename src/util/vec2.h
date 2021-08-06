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

#ifndef VEC2_H_
#define VEC2_H_

#include <ostream>

namespace util {
template <typename T>
class Vec2 {
public:
    Vec2() = default;
    Vec2(T x_, T y_) noexcept {
        x_pos = x_;
        y_pos = y_;
    }

    Vec2(const Vec2<T> &other) = default;
    Vec2(Vec2<T> &&other) = default;

    Vec2<T> &operator=(const Vec2<T> &other) = default;
    Vec2<T> &operator=(Vec2<T> &&other) = default;
    auto operator<=>(const Vec2<T> &) const noexcept = default;

    friend Vec2<T> operator+(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return Vec2<T>{lhs.x() + rhs.x(), lhs.y() + rhs.y()};
    }

    friend std::ostream &operator<<(std::ostream &stream, const Vec2<T> &data) {
        stream << data.x() << ' ' << data.y();
        return stream;
    }

    const T &x() const noexcept { return x_pos; }
    const T &y() const noexcept { return y_pos; }
    T &x() noexcept { return x_pos; }
    T &y() noexcept { return y_pos; }

    void add(const Vec2<T> &other) noexcept {
        x_pos += other.x_pos;
        y_pos += other.y_pos;
    }

    virtual ~Vec2() = default;

private:
    T x_pos{};
    T y_pos{};
};
}  // namespace util
#endif  // VEC2_H_