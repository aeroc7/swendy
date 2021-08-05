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

#ifndef OBJ_H_
#define OBJ_H_

#include <array>
#include <string>
#include <vector>

namespace obj_parser {
struct Vertex {
    double x;
    double y;
    double z;
};

struct Face {
    std::array<Vertex, 3> vertices;
};

class WavefrontObj {
public:
    WavefrontObj() = default;
    explicit WavefrontObj(const std::string &file_path);
    explicit WavefrontObj(const std::vector<char> &buffer);
    void parse_file_data(const std::string &file_path);
    void parse_buf_data(const std::vector<char> &buffer);
    const Face &get_face(std::size_t index) const;
    std::size_t num_faces() const noexcept;
    virtual ~WavefrontObj() = default;

private:
    void parse_obj_line(const std::string &line);
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};
}  // namespace obj_parser

#endif  // OBJ_H_