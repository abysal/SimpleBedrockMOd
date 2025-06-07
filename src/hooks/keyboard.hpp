//
// Created by Akashic on 5/30/2025.
//

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <functional>
#include <safetyhook.hpp>
#include <unordered_map>
#include <winrt/Windows.UI.Core.h>

namespace sbm {

    enum class Modifier {
        None = 0,
        LeftShift = 1,
        RightShift = 2,
        Ctrl = 4,
    };

    using Key = winrt::Windows::System::VirtualKey;

    enum class PressType {
        Press,
        Hold,
        Down,
        Release,
    };

    struct KeyState {
        friend static std::size_t hash_value(const KeyState &obj) {
            std::size_t seed = 0x5AD8D4B2;
            seed ^= (seed << 6) + (seed >> 2) + 0x61443704 + static_cast<std::size_t>(obj.modifier);
            seed ^= (seed << 6) + (seed >> 2) + 0x5C4812D5 + static_cast<std::size_t>(obj.key);
            return seed;
        }

        auto operator<=>(const KeyState &) const = default;

        Key key{};
        Modifier modifier{};
    };

    class Keyboard {
    public:
        static Keyboard& get_instance();

        static void register_bind(std::function<void()>&& callback, KeyState required_state, PressType press_type = PressType::Press);

    private:
        Keyboard();
        ~Keyboard();

        static long key_down_callback(void *windows_server, winrt::Windows::UI::Core::IKeyEventArgs *key_state);
        static long key_up_callback(void *windows_server, winrt::Windows::UI::Core::IKeyEventArgs *key_state);
        static KeyState build_bind_from_state(winrt::Windows::UI::Core::IKeyEventArgs * state);

    private:
        struct KeyStateInternal {
            bool was_down_last_frame{false};
        };
    private:
        std::unordered_map<size_t, std::vector<std::pair<std::function<void()>, PressType>>> listeners{};
        std::unordered_map<size_t, KeyStateInternal> states{};
        SafetyHookInline key_down{};
        SafetyHookInline key_up{};
    };

} // sbm

#endif //KEYBOARD_HPP
