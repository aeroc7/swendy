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

#ifndef PPM_H_
#define PPM_H_

#include <cstdint>
#include <fstream>
#include <memory>

namespace output::ppm {
struct PPMColor {
    using col_type = std::uint8_t;
    constexpr PPMColor(col_type r, col_type g, col_type b)
        : r_channel(r), g_channel(g), b_channel(b) {}

    constexpr std::tuple<col_type, col_type, col_type> get_colors() const {
        return {r_channel, g_channel, b_channel};
    }

    ~PPMColor() = default;

private:
    col_type r_channel{};
    col_type g_channel{};
    col_type b_channel{};
};

class PPMOutput {
public:
    using size_type = std::size_t;
    using data_type = std::uint32_t;

    constexpr PPMOutput() = default;

    constexpr PPMOutput(size_type width, size_type height)
        : image_width(width), image_height(height) {
        image_data = std::make_unique<data_type[]>(width * height);  // NOLINT
    }

    constexpr size_type width() const noexcept { return image_width; }

    constexpr size_type height() const noexcept { return image_height; }

    constexpr size_type size() const noexcept { return width() * height(); }

    data_type &at(size_type x, size_type y) {
        const auto index = coords_to_index(x, y);

        if (index >= size()) {
            out_of_range();
        }

        return image_data[index];
    }

    const data_type &at(size_type x, size_type y) const {
        const auto index = coords_to_index(x, y);

        if (index >= size()) {
            out_of_range();
        }

        return image_data[index];
    }

    void set_pixel_color(size_type x, size_type y, const PPMColor &color) {
        const auto index = coords_to_index(x, y);
        const auto [r, g, b] = color.get_colors();

        image_data[index] |= r << 24;
        image_data[index] |= g << 16;
        image_data[index] |= b << 8;
    }

    PPMColor get_pixel_color(size_type x, size_type y) const {
        const auto index = coords_to_index(x, y);

        const auto r = static_cast<std::uint8_t>(image_data[index] >> 24);
        const auto g = static_cast<std::uint8_t>(image_data[index] >> 16);
        const auto b = static_cast<std::uint8_t>(image_data[index] >> 8);

        return {r, g, b};
    }

    data_type *get() { return image_data.get(); }

    void write_file(const std::string &path) {
        std::ofstream file(path, std::ios::binary);

        // Header
        file << "P6\n";
        // Width & height
        file << width() << ' ' << height() << '\n';
        // Maximum color value
        file << "255" << '\n';

        for (size_type y = 0; y < height(); ++y) {
            for (size_type x = 0; x < width(); ++x) {
                const auto index = coords_to_index(x, y);
                const auto r =
                    static_cast<std::uint8_t>(image_data[index] >> 24);
                const auto g =
                    static_cast<std::uint8_t>(image_data[index] >> 16);
                const auto b =
                    static_cast<std::uint8_t>(image_data[index] >> 8);

                file.write(reinterpret_cast<const char *>(&r), sizeof(r));
                file.write(reinterpret_cast<const char *>(&g), sizeof(g));
                file.write(reinterpret_cast<const char *>(&b), sizeof(b));
            }
        }
    }

    ~PPMOutput() = default;

private:
    constexpr size_type coords_to_index(
        size_type x, size_type y) const noexcept {
        return x + (y * width());
    }

    [[noreturn]] static void out_of_range() {
        throw std::out_of_range("Index is out of array bounds");
    }

    size_type image_width{};
    size_type image_height{};
    std::unique_ptr<data_type[]> image_data;
};
}  // namespace output::ppm
#endif  // PPM_H_