//
// Created by Akashic on 6/7/2025.
//

#ifndef MOLANG_VARIABLE_MAP_HPP
#define MOLANG_VARIABLE_MAP_HPP
#include "molang_script_arg_data.hpp"

#include "../hashed_string.hpp"
#include <memory>
#include <vector>

namespace Molang {
    enum class MolangVariableSetting_AccessSpecifier : int {
        Private = 0,
        Public  = 1,
    };

    struct MolangVariableSettings {
        MolangVariableIndex                   mIndex{};
        MolangVariableSetting_AccessSpecifier access{1};
    };

    class MolangVariable {
    public:
        HashedString                     mName;
        MolangScriptArg                  mValue;
        std::unique_ptr<MolangScriptArg> mPublicValue;
    };

    class MolangVariableMap {
    public:
        std::vector<short> mMapFromVariableToIndexToVariableArrayOffset{};
        std::vector<std::unique_ptr<MolangVariable>> mVariables{};
        bool                                         mHasPublicVariables{};
    };

} // namespace Molang

#endif // MOLANG_VARIABLE_MAP_HPP
