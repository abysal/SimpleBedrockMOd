//
// Created by Akashic on 6/7/2025.
//

#ifndef SEM_VER_HPP
#define SEM_VER_HPP
#include <cstdint>

#include "memory/static_optimized_string.hpp"


template<typename StringType>
class SemVersionBase {
public:
    uint16_t major{};
    uint16_t minor{};
    uint16_t patch{};
    bool valid_version{true};
    bool any_version{};
    StringType pre_release{};
    StringType build_meta{};
};

using SemVersion = SemVersionBase<Bedrock::StaticOptimizedString>;

static_assert(sizeof(SemVersion) == 24);

#endif //SEM_VER_HPP
