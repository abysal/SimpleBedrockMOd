//
// Created by Akashic on 6/1/2025.
//

#include "expression_node.hpp"

#include "../../hooks/hook_manager.hpp"

gsl::span<HashedString> get_default_collection() {
    static HashedString default_collection{"default"};
    return {&default_collection, 1};
}

ExpressionNode::ExpressionNode(const std::string& source, MolangVersion version) {
    static auto ctor =
        static_cast<void (*)(ExpressionNode*, const std::string&, MolangVersion)>(
            sbm::HookManager::pattern_address<sbm::ExpressionNodeExpressionNode>()
        );

    ctor(this, source, version);
}

MolangScriptArg* ExpressionNode::eval_generic(details::RenderParams& params) {
    static auto eval_generic =
        reinterpret_cast<MolangScriptArg* (*)(ExpressionNode*, details::RenderParams&)>(
            sbm::HookManager::pattern_address<sbm::ExpressionNodeEvalGeneric>()
        );
    return eval_generic(this, params);
}
