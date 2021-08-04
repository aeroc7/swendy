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

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

namespace util {
inline void plot_line(int x0, int y0, int x1, int y1,
    ::output::ppm::PPMOutput &surface, const ::output::ppm::PPMColor &col) {
    const int dx = std::abs(x1 - x0);
    const int sx = x0 < x1 ? 1 : -1;
    const int dy = -std::abs(y1 - y0);
    const int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (true) {
        assert(x0 >= 0);
        assert(y0 >= 0);
        surface.set_pixel_color(
            static_cast<std::size_t>(x0), static_cast<std::size_t>(y0), col);

        e2 = err << 1U;

        if (e2 >= dy) {
            if (x0 == x1) {
                break;
            }

            err += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            if (y0 == y1) {
                break;
            }

            err += dx;
            y0 += sy;
        }
    }
}
}  // namespace util

#endif  // LINE_H_