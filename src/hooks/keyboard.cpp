//
// Created by Akashic on 5/30/2025.
//

#include "keyboard.hpp"

#include <iostream>

#include "../sbm.hpp"

#include "hook_manager.hpp"

using namespace winrt::Windows;
using namespace UI::Core;

namespace sbm {
    Keyboard & Keyboard::get_instance() {
        static Keyboard instance;
        return instance;
    }

    void Keyboard::register_bind(std::function<void()> &&callback, KeyState required_state, PressType press_type) {
        auto& instance = get_instance();
        if (instance.listeners.contains(hash_value(required_state))) {
            auto& listeners = instance.listeners.at(hash_value(required_state));
            listeners.emplace_back(std::make_pair(std::move(callback), press_type));
            return;
        }

        instance.listeners[hash_value(required_state)] = {std::move(std::make_pair(std::move(callback), press_type))};
    }

    static Keyboard* instance;

    Keyboard::Keyboard() {
        instance = this;
        /*this->key_down = safetyhook::create_inline(HookManager::pattern_address<InvokeKeyDownEventHandlers>(), &Keyboard::key_down_callback);
        this->key_up = safetyhook::create_inline(HookManager::pattern_address<InvokeKeyUpEventHandlers>(), &Keyboard::key_up_callback);*/
    }

    Keyboard::~Keyboard() {
        while (!this->key_up.disable().has_value()) {};
        while (!this->key_down.disable().has_value()) {};
    }

    long Keyboard::key_down_callback(void *windows_server, IKeyEventArgs *key_state) {
        return instance->key_down.call<long>(windows_server, key_state);
        const auto state = Keyboard::build_bind_from_state(key_state);

        if (!instance->listeners.contains(hash_value(state))) {
            return instance->key_down.call<long>(windows_server, key_state);
        }

         auto last_frame = [&] {
            if ( instance->states.contains(hash_value(state)) ) {
                return instance->states[hash_value(state)];
            }

            return KeyStateInternal{};
        }();

        for (const auto& [callback, press]  : instance->listeners.at(hash_value(state))) {
            if (press == PressType::Press && last_frame.was_down_last_frame == false) {
                callback();
                continue;
            }

            if (press == PressType::Down && last_frame.was_down_last_frame == false) {
                callback();
                continue;
            }

            if (press == PressType::Hold) {
                callback();
                continue;
            }
        }

        last_frame.was_down_last_frame = true;
        instance->states[hash_value(state)] = last_frame;

        return 0x0;
    }

    long Keyboard::key_up_callback(void *windows_server, IKeyEventArgs *key_state) {
        const auto state = Keyboard::build_bind_from_state(key_state);
        return instance->key_up.call<long>(windows_server, key_state);
        if (const auto state = Keyboard::build_bind_from_state(key_state); instance->states.contains(hash_value(state))) {
            instance->states[hash_value(state)] = KeyStateInternal{};
        }

    }

    // This is causing a crash
    KeyState Keyboard::build_bind_from_state(IKeyEventArgs *state) {
        System::VirtualKey code  = state->VirtualKey();
        auto window = CoreWindow::GetForCurrentThread();

        if (!window) {
            std::println("WI");
            std::cout << "WI" << std::endl;
            throw std::logic_error("Window is null");
        }

        const auto modifier = [&] {
            auto mod = Modifier::None;
            //
            // if (const auto key = window.GetKeyState(Key::LeftShift); key == CoreVirtualKeyStates::Down) {
            //     mod = enum_mix(mod, Modifier::LeftShift);
            // }
            //
            // if (const auto key = window.GetKeyState(Key::RightShift); key == CoreVirtualKeyStates::Down) {
            //     mod = enum_mix(mod, Modifier::RightShift);
            // }
            //
            // if (const auto key = window.GetKeyState(Key::Control); key == CoreVirtualKeyStates::Down) {
            //     mod = enum_mix(mod, Modifier::Ctrl);
            // }
            return mod;
        }();

        return KeyState {
            .key = code, .modifier = modifier
        };

    }
} // sbm