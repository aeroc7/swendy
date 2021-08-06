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

#include "obj/obj.h"
#include "util/line.h"
#include "util/log.h"

constexpr output::ppm::PPMColor WHITE_COLOR{255, 255, 255};

constexpr auto SURFACE_WIDTH = 1000;
constexpr auto SURFACE_HEIGHT = 1000;

constexpr int raw_to_screen_cords(double pos) {
    if (pos < 0) {
        return static_cast<int>(
            (500.0 - (std::fabs(pos) * (SURFACE_WIDTH / 2.0))));
    }

    return static_cast<int>(((pos * (SURFACE_WIDTH / 2.0)) + 500.0));
}

int main() {
    try {
        output::ppm::PPMOutput output_test(SURFACE_WIDTH, SURFACE_HEIGHT);
        obj_parser::WavefrontObj obj("monkey.obj");

        for (std::size_t i = 0; i < obj.num_faces(); ++i) {
            const auto &cur_face = obj.get_face(i);

            for (std::size_t j = 0; j < cur_face.vertices.size(); ++j) {
                const auto &v0 = cur_face.vertices.at(j);
                const auto &v1 = cur_face.vertices.at((j + 1) % 3);

                const util::Vec2<int> p0(
                    raw_to_screen_cords(v0.x), raw_to_screen_cords(v0.y));
                const util::Vec2<int> p1(
                    raw_to_screen_cords(v1.x), raw_to_screen_cords(v1.y));

                util::plot_line(p0, p1, output_test, WHITE_COLOR);
            }
        }

        output_test.write_file("test.ppm");
    } catch (const std::exception &e) {
        util::log << "Caught exception: " << e.what() << '\n';
    }
}