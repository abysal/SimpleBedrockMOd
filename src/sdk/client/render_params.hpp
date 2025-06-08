//
// Created by Akashic on 6/7/2025.
//

#ifndef RENDER_PARAMS_HPP
#define RENDER_PARAMS_HPP
#include <array>
#include <functional>
#include <glm/vec3.hpp>

#include "../block/block_pos.hpp"
#include "../molang/molang_script_arg_data.hpp"
#include "particle_system.hpp"

enum class ResponseParameterContext : int { Actor, Block, Item, None };

enum class ShadowContext : unsigned char { Unknown, ShadowOnly, PlayerShadowMapOnly, FullDraw };

enum class AttachableSlotIndex : int {
    Head,
    Torso,
    Legs,
    Feet,
    Body,
    CarriedItem,
    OffhandItem,
    _Count
};

namespace Molang {
    class MolangVariableMap;
}

class RenderParams {
public:
    struct Flags {
        uint32_t mIsChild;
    };

    RenderParams() = default;
    RenderParams(Molang::MolangVariableMap* variable_map) : mVariables(variable_map) {}

    class BaseActorRenderContext*          mBaseActorRenderContext{nullptr};
    Molang::MolangVariableMap*             mVariables{nullptr};
    class AnimationComponent*              mAnimationComponent{nullptr};
    class AnimationComponent*              mRootAnimationComponent{nullptr};
    std::array<std::byte, 16>              mModel{};
    ResponseParameterContext               mSourceContext;
    class Actor*                           mActor{nullptr};
    class Actor*                           mOther{nullptr};
    class Actor*                           mPlayer{nullptr};
    class Actor*                           mTarget{nullptr};
    class Actor*                           mParent{nullptr};
    class Actor*                           mBaby{nullptr};
    class Actor*                           mDamager{nullptr};
    class ILevel*                          mLevel{nullptr};
    class ItemStackBase*                   mItemStackBasePtr{nullptr};
    const class Block*                     mBlock{nullptr};
    BlockPos                               mBlockPos;
    class BlockSource*                     mBlockSource{nullptr};
    class ActorRenderData*                 mActorRenderData{nullptr};
    class ParticleSystem::ParticleEmitter* mParticleEmitter{nullptr};
    class IBlockWorldGenAPI*               mBlockPlacementTarget{nullptr};
    uint16_t                               mSubRenderLayerIndex;
    std::function<float()>                 mRandomFunction = []() {
        return static_cast<float>(rand()) / std::numeric_limits<uint32_t>::max();
    };
    float               mCameraDistance;
    ShadowContext       mShadowContext;
    float               mParams[8];
    MolangScriptArg     mThisValue;
    MolangScriptArg     mScratchValue;
    RenderParams::Flags mFlags{0};
    glm::vec3           mClickPos;
    AttachableSlotIndex mSlotIndex;
};

#endif // RENDER_PARAMS_HPP
