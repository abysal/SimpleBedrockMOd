//
// Created by Akashic on 6/1/2025.
//

#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP
#include <unordered_map>

#include "./molang_parse_config.hpp"
#include "./expression_op.hpp"
#include <variant>

gsl::span<HashedString> get_default_collection();

class IMolangInstruction {
public:
    virtual ~IMolangInstruction() = default;

    virtual void execute(class MolangEvalParams &) const = 0;

    [[nodiscard]] virtual std::unique_ptr<IMolangInstruction> clone() const = 0;
};

using MolangScriptArgType = int;
using MolangScriptArgPOD = uint64_t;
// using MolangScriptArgData = std::array<std::byte, 72>;
using FloatMatrix = std::array<float, 16>;

using MolangScriptArgData = std::variant<FloatMatrix, std::monostate>;

struct MolangScriptArg {
    MolangScriptArgType type;
    MolangScriptArgPOD pod;
    MolangScriptArgData data;
};


namespace details {
    class IInstruction {
    public:
        virtual ~IInstruction() = default;

        virtual IInstruction *cloneAt(void *) const = 0;

        virtual IInstruction *moveTo(void *) = 0;

        virtual size_t getSize() const = 0;

        virtual auto getCodeAddress() const -> void (*)(::MolangEvalParams &, void *) = 0;
    };

    class RenderParams {
    public:
    };

    class ExpressionNode {
    public:
        // Unknown
        class ResourceReference {
        public:
        };

    public:
        ExpressionOp op;
        MolangVersion version;
        float mul{};
        float add{};
        float unk;
        bool store_stack_state;
        bool needs_to_compile;
        bool has_variable_assignments;
        MolangScriptArg value;
        std::vector<ExpressionNode> children;
        std::string expression_string{};
    };

    static_assert(sizeof(ExpressionNode) == 0xA8);

    class IConstantExpression {
    public:
        virtual ~IConstantExpression() = default;

        virtual std::unique_ptr<IConstantExpression> clone();

        virtual MolangScriptArg *evalGeneric(RenderParams &);

        virtual bool isInitialized();

        virtual void * /*this is a Json::Value */ toJson();

        virtual std::string &getExpressionString();

        virtual MolangVersion getMolangVersion();

        virtual void
        replaceResourceVariables(std::unordered_map<HashedString, ExpressionNode::ResourceReference> &map);

        virtual void replaceArrayVariables(std::unordered_map<HashedString, ExpressionNode> &);

        virtual void validateArrayVariables();

        virtual bool isValid();

        virtual bool isConstantValue();

        virtual bool hasVariableAssignments();

        virtual ExpressionOp getOp();

        virtual bool needsToCompile();

        virtual std::optional<MolangScriptArg> getValueIfConstant();

        virtual ExpressionNode *getSource();
    };

    class SourceExpression : public IConstantExpression {
    public:
        ~SourceExpression() override = default;

        ExpressionNode expression;
    };

    class CompiledExpressionWithSource : public IConstantExpression {
    public:
        ~CompiledExpressionWithSource() override = default;

        ExpressionNode expression;
    };

    class ConstantExpression : public IConstantExpression {
    public:
        ~ConstantExpression() override = default;

        MolangScriptArg value;
    };
}

using ExpressionOrConstant = std::variant<std::unique_ptr<details::IConstantExpression>, float>;
static_assert(sizeof(ExpressionOrConstant) == 16);

class ExpressionNode {
public:
    ExpressionOrConstant expression_or_constant;

    ExpressionNode()
};

class MolangProgramBuildState {
public:
    size_t used_reg_count;
    bool unk2;
    std::vector<std::unique_ptr<details::IInstruction> > instructions;
    std::string expression;
};


#endif // EXPRESSION_NODE_HPP
