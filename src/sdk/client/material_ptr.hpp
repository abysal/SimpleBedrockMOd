//
// Created by Akashic on 6/7/2025.
//

#ifndef MATERIAL_PTR_HPP
#define MATERIAL_PTR_HPP
#include <memory>

#include "../hashed_string.hpp"

namespace mce {
    class RenderMaterialInfo : public std::enable_shared_from_this<RenderMaterialInfo> {
    public:
        HashedString mHashedName;

        RenderMaterialInfo(const HashedString &name);
    };

    class MaterialPtr {
    public:
        std::shared_ptr<RenderMaterialInfo> mRenderMaterialInfoPtr;
    };
} // mce

#endif //MATERIAL_PTR_HPP
