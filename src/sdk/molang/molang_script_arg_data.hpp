//
// Created by Akashic on 6/7/2025.
//

#ifndef MOLANG_SCRIPT_ARG_DATA_HPP
#define MOLANG_SCRIPT_ARG_DATA_HPP
#include <array>
#include <vector>

#include "../client/material_ptr.hpp"
#include "../hashed_string.hpp"

#include <functional>
#include <variant>

class Actor;
using ActorUniqueID       = uint64_t;
using MolangVariableIndex = uint16_t;

template <typename T> struct MolangHashStringVariable : protected HashedString {
    explicit MolangHashStringVariable(const HashedString& str) : HashedString(str) {}

    HashedString& get_name() { return *this; }
};

enum class MolangScriptArgType : int {
    Unset = -1,
    Float,
    HashType64,
    MolangLoopBreak,
    MolangActorPtr,
    MolangActorIdPtr,
    Variant
};

constexpr std::string_view script_to_string(MolangScriptArgType t) { 
    switch (t) {
        case MolangScriptArgType::Unset:
            return "Unset";
        case MolangScriptArgType::Float:
            return "Float";
        case MolangScriptArgType::HashType64:
            return "HashType64";
        case MolangScriptArgType::MolangLoopBreak:
            return "MolangLoopBreak";
        case MolangScriptArgType::MolangActorPtr:
            return "MolangActorPtr";
        case MolangScriptArgType::MolangActorIdPtr:
            return "MolangActorIdPtr";
        case MolangScriptArgType::Variant:
            return "Variant";
    };
       
    return "I HAVE NO IDEA WHAT THE FUCK HAPPENED";
}

struct MolangLoopBreak {};
struct MolangLoopContinue {};

union MolangScriptArgPOD {
    float                mFloat;
    size_t               mHashType64;
    MolangLoopBreak      mLoopBreak;
    MolangLoopContinue   mLoopContinue;
    Actor*               mActorPtr;
    int64_t              mActorId;
    class ItemStackBase* mItemStackBasePtr;
    uint64_t             _mData;

    MolangScriptArgPOD() : mFloat(0.0f) {}
};

struct MolangScriptArg;

struct MolangMemberVariable;

class RenderParams;

namespace details {

    using QueryFunctionAccessor = std::function<
        MolangScriptArg&(RenderParams&, const std::vector<class ExpressionNode>&)>;

    enum class MolangQueryFunctionReturnType : unsigned long {
        Float = 1,
        HashType64,
        ActorPtr           = 4,
        ActorIdPtr         = 8,
        ActorArrayPtr      = 16,
        ActorIdArrayPtr    = 32,
        ArrayVariable      = 64,
        ClientTexture      = 128,
        ContextVariable    = 256,
        DataDrivenGeometry = 512,
        EntityVariable     = 1024,
        GeometryVariable   = 2048,
        MaterialVariable   = 4096,
        MemberAccessor     = 8192,
        MemberArray        = 16384,
        TempVariable       = 32768,
        TextureVariable    = 65536,
        Bool               = 131072,
        Matrix             = 262144,
        Number             = 131073,
        ActorSingle        = 12,
        ActorArray         = 48,
        Actor              = 60,
        Variable           = 34048,
        Resource           = 71808
    };

    struct MolangMatrix {
        float mMatrix[4][4];
    };

    class MaterialVariants {
    public:
        std::array<std::byte, sizeof(mce::MaterialPtr) * 2> cheat_padding;

        static MaterialVariants mDefaultErrorValue;
    };

    struct MolangActorArrayPtr {
    private:
        std::vector<Actor*> mActors;
    };

    struct MolangActorIdArrayPtr {
    private:
        std::vector<ActorUniqueID> mActorIds;
    };

    struct MolangArrayVariable : public MolangHashStringVariable<MolangArrayVariable> {};

    struct MolangClientTextureSet {
    private:
        HashedString mData;
    };

    struct MolangContextVariable : public MolangHashStringVariable<MolangContextVariable> {
        MolangVariableIndex mMolangVariableIndex;
    };

    struct MolangDataDrivenGeometry {
    private:
        std::array<std::byte, 16> mGeometry{};
        HashedString              mName;
    };

    struct MolangEntityVariable : public MolangHashStringVariable<MolangEntityVariable> {
        MolangVariableIndex mMolangVariableIndex;
    };

    struct MolangGeometryVariable : public MolangHashStringVariable<MolangGeometryVariable> {};

    struct MolangMaterialVariable : public MolangHashStringVariable<MolangMaterialVariable> {};

    struct MolangMemberAccessor : public MolangHashStringVariable<MolangMemberAccessor> {};

    struct MolangMemberArray {
    private:
        std::vector<MolangMemberVariable> mMembers;
    };

    struct MolangQueryFunctionPtr {
    private:
        MolangQueryFunctionReturnType mReturnType;
        const QueryFunctionAccessor*  mQueryFunctionPtr;
        HashedString                  mName;
    };

    struct MolangTempVariable : public MolangHashStringVariable<MolangTempVariable> {
        MolangVariableIndex mMolangVariableIndex;
    };

    struct MolangTextureVariable : public MolangHashStringVariable<MolangTextureVariable> {};

    struct MolangOffsetPlaceholder {
        HashedString mName;
        size_t       mResourceOffset;
    };

    struct MolangResourceOffset {
        uint32_t mOffset;
    };

    using MolangScriptArgData = std::variant<
        MolangMatrix, MaterialVariants, MolangActorArrayPtr, MolangActorIdArrayPtr,
        MolangArrayVariable, MolangClientTextureSet, MolangContextVariable,
        MolangDataDrivenGeometry, MolangEntityVariable, MolangGeometryVariable,
        MolangMaterialVariable, MolangMemberAccessor, MolangMemberArray, MolangQueryFunctionPtr,
        MolangTempVariable, MolangTextureVariable, MolangOffsetPlaceholder,
        MolangResourceOffset>;
}; // namespace details

struct MolangScriptArg {
    MolangScriptArgType          type{};
    MolangScriptArgPOD           pod{};
    details::MolangScriptArgData data{};
};

struct MolangMemberVariable {
    HashedString    mName;
    MolangScriptArg mData;
};

#endif // MOLANG_SCRIPT_ARG_DATA_HPP
