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

MolangScriptArg* ExpressionNode::eval_generic(RenderParams& params) {
    if (std::holds_alternative<float>(this->expression_or_constant)) {
        throw std::logic_error("not implemented");
    }

    auto& expression = std::get<0>(this->expression_or_constant);
    return expression->evalGeneric(params);
}

details::IConstantExpression& ExpressionNode::constant_expression() {
    auto& expression = std::get<0>(this->expression_or_constant);
    return *expression;
}
