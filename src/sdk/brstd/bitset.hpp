//
// Created by Akashic on 6/1/2025.
//

#ifndef BITSET_HPP
#define BITSET_HPP
#include <bit>
#include <concepts>
#include <stdexcept>
#include <array>

namespace brstd {
    namespace detail {
        template<typename T>
        class bitset_storage;

        template<std::integral T>
        class bitset_storage<T> {
        public:
            using storage_type = T;

            explicit bitset_storage(T value) : storage(value) {
            }

            constexpr bool operator[](const size_t index) const noexcept {
                return (storage & (1 << index)) != 0;
            }

            constexpr void set(const size_t index, const bool value) {
                this->storage = (this->storage & (~(1 << index))) | (value << index);
            }

        private:
            T storage{};
        };

        template<size_t N>
        class bitset_storage<std::array<uint32_t, N> > {
        public:
            using storage_type = std::array<uint32_t, N>;

            explicit bitset_storage(storage_type value) : storage(value) {
            }

            constexpr bool operator[](const size_t index) const noexcept {
                const auto storage_slot = index / 32;
                const auto bit_index = index % 32;
                return this->storage[storage_slot] & (1 << bit_index);
            }

            constexpr void set(const size_t index, const bool value) {
                throw std::logic_error("bitset_storage::set: not implemented");
            }

        private:
            storage_type storage{};
        };


        // Now that im thinking about it, this is most likely incorrect since this acts like std::bitset which this tries to be better than.
        // So I need to refactor how this is managed, right now we actually make an invalid thing for anything over uint64_t
        template<size_t Bits>
        struct select_storage_type {
            static_assert(Bits > 0, "bitset must have at least 1 bit");
            using type = std::conditional_t<
                (Bits <= 8), uint8_t,
                std::conditional_t<(Bits <= 16), uint16_t,
                    std::conditional_t<(Bits <= 32), uint32_t,
                        std::conditional_t<(Bits <= 64), uint64_t,
                            std::array<uint32_t, std::bit_ceil(Bits) / 32>
                        > > > >;
        };
    }

    template<size_t bits>
    class bitset {
    public:
        using storage_type = typename detail::select_storage_type<bits>::type;
        using underlying = typename detail::bitset_storage<storage_type>::storage_type;

        explicit bitset(underlying value) : storage(value) {
        }

        constexpr bool operator[](const size_t index) const {
            if (index >= bits) {
                throw std::out_of_range("bitset::operator[]: index out of range");
            }
            return this->storage[index];
        }

    private:
        detail::bitset_storage<storage_type> storage{};
    };
} // brstd

#endif //BITSET_HPP
