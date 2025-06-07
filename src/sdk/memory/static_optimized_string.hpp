//
// Created by Akashic on 6/7/2025.
//

#ifndef STATIC_OPTIMIZED_STRING_HPP
#define STATIC_OPTIMIZED_STRING_HPP
#include <string_view>

#include "packed_pointer.hpp"

namespace Bedrock {
    class StaticOptimizedString {
    public:
        enum class StorageLocation {
            Static,
            Dynamic
        };

        constexpr static size_t Mask = 0xFF00FFFFFFFFFFFF;
        constexpr static size_t DynamicMask = 0x80000000000000;

        StaticOptimizedString(std::string_view string, StorageLocation location);

        StaticOptimizedString(const StaticOptimizedString &);

        StaticOptimizedString &operator=(const StaticOptimizedString &);

        StaticOptimizedString &operator=(StaticOptimizedString &&other) noexcept;

        StaticOptimizedString(StaticOptimizedString &&) noexcept;


        ~StaticOptimizedString();


        void set(std::string_view value, StorageLocation location);

        const char *c_str() const;

        std::string_view get() const;

        bool is_dynamic() const;

        size_t length() const;

        bool operator==(const StaticOptimizedString &other) const;

        bool operator!=(const StaticOptimizedString &other) const {
            return !(*this == other);
        }

        bool operator==(const std::string_view &other) const;

        bool operator!=(const std::string_view &other) const {
            return !(*this == other);
        }

    private:
        void allocate_long_string(std::string_view value);

        void free() const;

    private:
        StringPackedPointer string_data;
    };
} // Bedrock

#endif //STATIC_OPTIMIZED_STRING_HPP
