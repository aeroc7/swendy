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

#include "obj.h"

#include <fstream>
#include <limits>

#include "../util/split_string.h"
#include "../util/str_to_num.h"

namespace obj_parser {
WavefrontObj::WavefrontObj(const std::string &file_path) {
    parse_file_data(file_path);
}

WavefrontObj::WavefrontObj(const std::vector<char> &buffer) {
    parse_buf_data(buffer);
}

void WavefrontObj::parse_file_data(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::binary);

    // Size of file
    file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize file_length = file.gcount();
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::vector<char> file_data(static_cast<std::size_t>(file_length));

    // Read file into vector
    file.read(file_data.data(), file_length);

    parse_buf_data(file_data);
}

void WavefrontObj::parse_buf_data(const std::vector<char> &buffer) {
    std::string line;
    bool inside_comment{false};

    for (const auto &e : buffer) {
        if (e == '#') {
            inside_comment = true;
        }

        if (inside_comment == false) {
            if (e != '\n') {
                line.push_back(e);
            } else {
                parse_obj_line(line);
                line.clear();
            }
        } else {
            if (e == '\n') {
                // Comment finishes at end of line
                inside_comment = false;
            }
        }
    }
}

const Face &WavefrontObj::get_face(std::size_t index) const {
    return faces.at(index);
}

std::size_t WavefrontObj::num_faces() const noexcept { return faces.size(); }

void WavefrontObj::parse_obj_line(const std::string &line) {
    const auto row_code = util::split_string(line, 0, " ");

    if (row_code == "v") {
        // Is a vertex
        const auto x_str = util::split_string(line, 1, " ");
        const auto y_str = util::split_string(line, 2, " ");
        const auto z_str = util::split_string(line, 3, " ");

        vertices.push_back({util::str_to_num<double>(x_str),
            util::str_to_num<double>(y_str), util::str_to_num<double>(z_str)});
    } else if (row_code == "f") {
        auto extract_vertex = [this](const std::string &part) -> std::size_t {
            std::string vertex_pos_str;
            vertex_pos_str.reserve(7);
            for (const auto &e : part) {
                if (e != '/') {
                    vertex_pos_str.push_back(e);
                } else {
                    break;
                }
            }

            const auto vert_pos = util::str_to_num<std::size_t>(vertex_pos_str);

            // Vertex indexes are one-based instead of our usual zero-based
            if ((vert_pos - 1) < vertices.size()) {
                return vert_pos - 1;
            }

            util::log << "Index " << vert_pos
                      << " is larger than our vertice storage\n";
            return {};
        };

        // Face can have three or more elements separated into three groups
        // (groups are separated by a slash '/')
        // We're only interested in the first group within the first three
        // elements (for now at least)

        const auto v1 = extract_vertex(util::split_string(line, 1, " "));
        const auto v2 = extract_vertex(util::split_string(line, 2, " "));
        const auto v3 = extract_vertex(util::split_string(line, 3, " "));

        faces.push_back({{vertices.at(v1), vertices.at(v2), vertices.at(v3)}});
    }
}
}  // namespace obj_parser