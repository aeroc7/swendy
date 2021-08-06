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

#ifndef LINE_H_
#define LINE_H_

#include <cassert>
#include <cmath>
#include <type_traits>

#include "../output/ppm/ppm.h"
#include "vec2.h"

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

namespace util {
inline void plot_line(Vec2<int> p0, Vec2<int> p1,
    ::output::ppm::PPMOutput &surface, const ::output::ppm::PPMColor &col) {
    const int dx = std::abs(p1.x() - p0.x());
    const int sx = p0.x() < p1.x() ? 1 : -1;
    const int dy = -std::abs(p1.y() - p0.y());
    const int sy = p0.y() < p1.y() ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (true) {
        assert(p0.x() >= 0);
        assert(p0.y() >= 0);
        surface.set_pixel_color(static_cast<std::size_t>(p0.x()),
            static_cast<std::size_t>(p0.y()), col);

        e2 = err << 1U;

        if (e2 >= dy) {
            if (p0.x() == p1.x()) {
                break;
            }

            err += dy;
            p0.x() += sx;
        }

        if (e2 <= dx) {
            if (p0.y() == p1.y()) {
                break;
            }

            err += dx;
            p0.y() += sy;
        }
    }
}
}  // namespace util

#endif  // LINE_H_