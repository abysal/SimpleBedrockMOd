//
// Created by Akashic on 6/1/2025.
//

#include "expression_node.hpp"


gsl::span<HashedString> get_default_collection() {
    static HashedString default_collection{"default"};
    return {&default_collection, 1};
}
