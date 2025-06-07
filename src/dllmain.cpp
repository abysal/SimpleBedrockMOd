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

#include "sdk/memory/static_optimized_string.hpp"

std::thread our_thread;
HMODULE our_module;

void test() {
    auto string = Bedrock::StaticOptimizedString("Hello world",
                                                 Bedrock::StaticOptimizedString::StorageLocation::Static);

    std::println("{}, is dynamic: {}", string.get(), string.is_dynamic());

    string = Bedrock::StaticOptimizedString(
        "Some Really Really Really Really Really Really Really Really Really Really Really Really Really Really Really Really Really Long String",
        Bedrock::StaticOptimizedString::StorageLocation::Static);
    std::println("{}, is dynamic: {}", string.get(), string.is_dynamic());
}

void entry() {
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    SetConsoleTitleA("Bedrock Test Mod");
    FILE *in;
    freopen_s(&in, "CONIN$", "r", stdin);
    FILE *out;
    freopen_s(&out, "CONOUT$", "w", stdout);
    FILE *err;
    freopen_s(&err, "CONOUT$", "w", stderr);

    if (const auto status = kiero::init(kiero::RenderType::D3D12);
        status != kiero::Status::Success) {
        std::println("{}", static_cast<int>(status));
        return;
    }

    std::println("SBM loaded");
    test();
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
