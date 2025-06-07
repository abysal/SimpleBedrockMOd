//
// Created by Akashic on 6/1/2025.
//

#ifndef MOLANGPARSECONFIG_HPP
#define MOLANGPARSECONFIG_HPP
#include <vector>

#include "../brstd/bitset.hpp"
#include <gsl/span>

#include "../hashed_string.hpp"

enum class MolangVersion : short {
    Invalid = -1, BeforeVersioning, Initial,
    FixedItemRemainingUseDurationQuery,
    ExpressionErrorMessages, UnexpectedOperatorErrors,
    ConditionalOperatorAssociativity,
    ComparisonAndLogicalOperatorPrecedence, DivideByNegativeValue,
    FixedCapeFlapAmountQuery, QueryBlockPropertyRenamedToState,
    DeprecateOldBlockQueryNames, DeprecatedSnifferAndCamelQueries,
    LeafSupportingInFirstSolidBlockBelow,
    NumValidVersions,
    Latest = 12,
    HardcodedMolang = Latest
};

using ExpressionOpBitField = brstd::bitset<77>;
using QuerySetIdentifierCollection = gsl::span<HashedString>;
static_assert(sizeof(ExpressionOpBitField) == 16);

struct MolangParseConfig {
    MolangVersion version = MolangVersion::Latest;
    QuerySetIdentifierCollection allowed_query_sets;
    ExpressionOpBitField allowed_operations{std::array{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}}; // Set all bits cuz fuck it
    std::vector<std::string> allowed_specific_queries{};
};

static_assert(sizeof(MolangParseConfig) == 64);

#endif //MOLANGPARSECONFIG_HPP
