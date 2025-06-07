//
// Created by Akashic on 5/31/2025.
//

#ifndef SBM_HPP
#define SBM_HPP
#include <utility>

namespace sbm {

    template<typename T>
    T enum_mix(T base, T add) noexcept {
        auto base_val = std::to_underlying(base);
        auto add_val = std::to_underlying(add);
        auto enum_val = base_val |= add_val;
        return static_cast<T>(enum_val);
    }
}

#endif //SBM_HPP
