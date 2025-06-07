//
// Created by Akashic on 6/7/2025.
//

#ifndef SEM_VER_HPP
#define SEM_VER_HPP
#include <cstdint>


template<typename StringType>
class SemVersionBase {
public:
    uint16_t major{};
    uint16_t minor{};
    uint16_t patch{};
    bool valid_version{};
    bool any_version;
    StringType pre_release{};
    StringType build_meta{};
};


#endif //SEM_VER_HPP
