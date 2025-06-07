//
// Created by Akashic on 5/30/2025.
//

#ifndef HOOK_MANAGER_HPP
#define HOOK_MANAGER_HPP
#include <print>
#include <typeindex>
#include <libhat/scanner.hpp>
#include <libhat/signature.hpp>
#include <safetyhook.hpp>

namespace sbm {
    struct ThreadingGetMainThreadScheduler {
        static constexpr auto pattern = hat::compile_signature<"48 89 5C 24 ? 57 48 83 EC ? 33 DB 48 8B 05">();
    };

    struct InvokeKeyDownEventHandlers {
        static constexpr auto pattern = hat::compile_signature<
            "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B F1 4C 8D B1 ? ? ? ? 49 8B 06 49 8B CE 48 8B 40 ? E8 ? ? ? ? 85 C0 0F 88">();
    };

    struct InvokeKeyUpEventHandlers {
        static constexpr auto pattern = hat::compile_signature<
            "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B F1 4C 8D B1 ? ? ? ? 49 8B 06 49 8B CE 48 8B 40 ? E8 ? ? ? ? 85 C0 78">();
    };

    struct InvokeDelegatesKeyDownHandler {
        static constexpr auto pattern = hat::compile_signature<
            "48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 49 8B E8 4C 8B CA 4C 8B F9 33 FF 33 DB 48 89 5C 24 ? 48 85 D2 74 ? 48 8D 4A ? E8 ? ? ? ? 49 8B D9 48 89 5C 24 ? 4C 8B 73 ? 48 8B 73 ? 48 3B 73 ? 74 ? 48 8B 0E 48 8B 01 49 8B 57 ? 4C 8B 02 49 8B 17 48 8B 12 48 8B 40 ? E8 ? ? ? ? 8B F8 3D ? ? ? ? 75 ? 45 33 C0 33 D2 8B CF 48 FF 15 ? ? ? ? 0F 1F 44 00 ? 48 8B 16 48 8B CD E8 ? ? ? ? 33 FF EB ? 81 FF ? ? ? ? 74 ? 81 FF ? ? ? ? 74 ? 81 FF ? ? ? ? 74 ? 81 FF ? ? ? ? 74 ? 85 FF 78 ? 49 83 C6 ? 48 83 C6 ? EB ? 48 8B CB E8 ? ? ? ? 8B C7 48 8B 5C 24 ? 48 83 C4 ? 41 5F 41 5E 5F 5E 5D C3 CC 48 FF 15 ? ? ? ? 0F 1F 44 00 ? 90 85 C0 75 ? 45 33 C0 33 D2 8B CF 48 FF 15 ? ? ? ? 0F 1F 44 00 ? EB ? 8B DF 49 8B 06 48 89 44 24 ? 48 83 64 24 ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 54 24 ? 8B CF 48 FF 15 ? ? ? ? 0F 1F 44 00 ? 85 C0 78 ? 48 8B 54 24 ? 48 8B 0E 48 FF 15 ? ? ? ? 0F 1F 44 00 ? 33 FF 85 C0 0F 48 FB 48 8B 44 24 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 5C 24 ? E9 ? ? ? ? CC CC CC CC CC CC CC CC CC CC 48 83 EC">();
    };

    struct DetailsExpressionNodeParse {
        static constexpr auto pattern = hat::compile_signature<
            // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E0 4C 89 44 24 ? 48 8B F2: 1.21.70
            "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8 4C 89 44 24 ? 48 8B F2 48 89 54 24">();
    };

    struct ExpressionNodeExpressionNode {
        static constexpr auto pattern = hat::compile_signature<
            "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B FA 48 8B D9 48 89 4C 24 ? 66 44 89 44 24">();
    };

    struct OptionsGetFov {
        static constexpr auto pattern = hat::compile_signature<
            "48 8B C4 48 89 58 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 0F B6 F0">();
    };

    struct TessellatorBegin {
        static constexpr auto pattern = hat::compile_signature<"40 53 55 48 83 EC ? 80 B9 ? ? ? ? ? 44 0F B6 D2">();
    };

    struct MinecraftUiRenderContextCtor {
        static constexpr auto pattern = hat::compile_signature<
            "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 41 56 41 57 48 83 EC ? 49 8B E9 4C 8B F2">();
    };

    struct ScreenViewSetupAndRender {
        static constexpr auto pattern = hat::compile_signature<
            "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E2 48 89 55 ? 4C 8B F9">();
    };


    class HookManager {
    public:
        static HookManager &get_instance();

        template<typename Signature>
        static void *pattern_address() {
            static void *signature = get_instance().addresses.at(std::type_index(typeid(Signature)));
            return signature;
        }

        template<typename Signature>
        static SafetyHookInline hook(void *callback) {
            return safetyhook::create_inline(
                HookManager::pattern_address<Signature>(), callback
            );
        }

    private:
        hat::process::module windows_ui_module = *hat::process::get_module("Windows.UI.dll");
        std::unordered_map<std::type_index, void *> addresses{};

    private:
        HookManager();

        template<typename Signature>
        void insert_signature() {
            auto result = hat::find_pattern(Signature::pattern, ".text");

            if (!result.has_result()) {
                std::println("Failed to find signature pattern windows");
            }

            this->addresses[typeid(Signature)] = result.get();
        }

        template<typename Signature>
        void insert_signature_windows() {
            auto result = hat::find_pattern(Signature::pattern, ".text", this->windows_ui_module);

            if (!result.has_result()) {
                std::println("Failed to find signature pattern");
            }

            this->addresses[typeid(Signature)] = result.get();
        }
    };
} // sbm

#endif //HOOK_MANAGER_HPP
