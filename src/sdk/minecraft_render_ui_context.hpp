//
// Created by Akashic on 6/7/2025.
//

#ifndef MINECRAFT_RENDER_UI_CONTEXT_HPP
#define MINECRAFT_RENDER_UI_CONTEXT_HPP
#include <array>

struct ScreenContext {
    char pad_0000[200]; // 0x0000
    void *Tessellator; // 0x00C8
};

struct MinecraftRenderUiContext {
    virtual ~MinecraftRenderUiContext() = 0;

    void *ci; // IClientInstance
    ScreenContext *screen_context;
    std::array<std::byte, 320 - 24> padding;
};
#endif //MINECRAFT_RENDER_UI_CONTEXT_HPP
