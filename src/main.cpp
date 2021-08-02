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

#include <iostream>

#include "output/ppm/ppm.h"

constexpr output::ppm::PPMColor RED_COLOR{255, 0, 0};
constexpr output::ppm::PPMColor GREEN_COLOR{0, 255, 0};
constexpr output::ppm::PPMColor BLUE_COLOR{0, 0, 255};
constexpr output::ppm::PPMColor YELLOW_COLOR{255, 255, 0};
constexpr output::ppm::PPMColor WHITE_COLOR{255, 255, 255};
constexpr output::ppm::PPMColor BLACK_COLOR{0, 0, 0};

int main() {
    output::ppm::PPMOutput output_test(3, 2);

    output_test.set_pixel_color(0, 0, RED_COLOR);
    output_test.set_pixel_color(1, 0, GREEN_COLOR);
    output_test.set_pixel_color(2, 0, BLUE_COLOR);
    output_test.set_pixel_color(0, 1, YELLOW_COLOR);
    output_test.set_pixel_color(1, 1, WHITE_COLOR);
    output_test.set_pixel_color(2, 1, BLACK_COLOR);

    output_test.write_file("test.ppm");
}