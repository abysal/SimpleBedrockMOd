//
// Created by Akashic on 5/30/2025.
//

#include "hooks/hook_manager.hpp"
#include "hooks/keyboard.hpp"
#include "kiero.hpp"
#include "sdk/threading.hpp"
#include <dxgi1_4.h>
#include <libhat/scanner.hpp>
#include <print>
#include <safetyhook.hpp>
#include <thread>
#include <windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Core.h>
#include <wrl.h>

#include "sdk/molang/expression_node.hpp"
#include <random>

std::thread our_thread;
HMODULE our_module;

SafetyHookInline expr_node_parse{};

bool expression_node_parse(ExpressionNode* self, std::string_view expression, const MolangParseConfig& config) {
    const auto value = expr_node_parse.call<bool>(self, expression, config);
    // self->instructions.clear();
    return value;
}

SafetyHookInline tess_begin_hook;

void tess_begin(void* self, void* a2, void* a3) { 
    tess_begin_hook.call<void>(self, a2, a3);
    std::println("Tess pointer: {:x}", std::bit_cast<uintptr_t>(self));
}

SafetyHookInline minecraft_ui_render_context;

struct ScreenContext {
    char  pad_0000[200]; // 0x0000
    void* Tessellator;   // 0x00C8
};

struct MinecraftRenderUiContext {
    virtual ~MinecraftRenderUiContext() = 0;
    void* ci; // IClientInstance
    ScreenContext* screen_context;
    std::array<std::byte, 320 - 24> padding;
};


void* minecraft_ui_render_context_ctor(void* self, void* client_instance, ScreenContext* screen_context, void* unk) {
    std::println("Screen Context: {:x}", std::bit_cast<uintptr_t>(screen_context));
    std::println("McUiRenderContext ptr: {:x}", std::bit_cast<uintptr_t>(self));
    return minecraft_ui_render_context.call<void*>(self, client_instance, screen_context, unk);
}


void entry() {
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Bedrock Test Mod");
    FILE* in;
    freopen_s(&in, "CONIN$", "r", stdin);
    FILE* out;
    freopen_s(&out, "CONOUT$", "w", stdout);
    FILE* err;
    freopen_s(&err, "CONOUT$", "w", stderr);

    if (const auto status = kiero::init(kiero::RenderType::D3D12);
        status != kiero::Status::Success) {
        std::println("{}", static_cast<int>(status));
        return;
    }

    tess_begin_hook = sbm::HookManager::hook<sbm::TessellatorBegin>(&tess_begin);
    minecraft_ui_render_context =
        sbm::HookManager::hook<sbm::MinecraftUiRenderContextCtor>(&minecraft_ui_render_context_ctor);

    std::println("SBM loaded");

    // Wait for key press
    while (!(GetKeyState(VK_LCONTROL) & 0x8000)) {
        Sleep(10); // avoid busy-waiting
    }

    while (!(GetKeyState(VK_INSERT) & 0x8000)) {
        Sleep(10); // avoid busy-waiting
    }

    std::println("SBM unloading");
    FreeLibrary(our_module);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        our_module = hInstance;;
        our_thread = std::thread(entry);
        our_thread.detach();
    }

    return TRUE;
}
