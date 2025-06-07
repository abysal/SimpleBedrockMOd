//
// Created by Akashic on 6/7/2025.
//

#ifndef PACKED_POINTER_HPP
#define PACKED_POINTER_HPP
#include <bit>
#include <cstdint>

namespace Bedrock {
    template<typename PointerType, size_t Align>
    class PackedPointer {
    public:
        uintptr_t pointer;

        constexpr static size_t align = Align;

        constexpr PackedPointer(nullptr_t) : pointer(0x0) {
        }

        constexpr PackedPointer(PointerType *pointer) : pointer(std::bit_cast<uintptr_t>(pointer)) {
        }

        constexpr PackedPointer(std::remove_const_t<PointerType> *pointer) : pointer(
            std::bit_cast<uintptr_t>(pointer)) {
        }

        constexpr PackedPointer &operator=(PointerType *ptr) noexcept {
            pointer = std::bit_cast<uintptr_t>(ptr);
            return *this;
        }

        constexpr PackedPointer &operator=(std::remove_const_t<PointerType> *ptr) noexcept {
            pointer = std::bit_cast<uintptr_t>(ptr);
            return *this;
        }

        constexpr PackedPointer(const uintptr_t pointer) : pointer(pointer) {
        }

    public:
        PointerType *p() const {
            return std::bit_cast<PointerType *>(this->pointer & 0xFF00FFFFFFFFFFFF);
        }

        constexpr uint16_t top() const {
            return static_cast<uint16_t>((this->pointer & 0xFFFF000000000000) >> 48);
        }

        constexpr uint8_t flags() const {
            return static_cast<uint8_t>((this->pointer & 0x00FF000000000000) >> 48);
        }

        uintptr_t raw() const {
            return this->pointer;
        }
    };

    using StringPackedPointer = PackedPointer<const char, 1>;
} // Bedrock

#endif //PACKED_POINTER_HPP
