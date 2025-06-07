//
// Created by Akashic on 6/7/2025.
//

#include "static_optimized_string.hpp"

#include <stdexcept>

namespace Bedrock {
    StaticOptimizedString::StaticOptimizedString(const std::string_view string,
                                                 const StorageLocation location): string_data(nullptr) {
        this->set(string, location);
    }

    StaticOptimizedString::StaticOptimizedString(const StaticOptimizedString &other) : string_data(nullptr) {
        if (other.is_dynamic()) {
            *this = StaticOptimizedString(other.get(), StorageLocation::Dynamic);
        } else {
            this->string_data = other.string_data;
        }
    }

    StaticOptimizedString::StaticOptimizedString(StaticOptimizedString &&other) noexcept : string_data(nullptr) {
        this->string_data = other.string_data;
        other.string_data = StringPackedPointer(nullptr);
    }

    StaticOptimizedString &StaticOptimizedString::operator=(const StaticOptimizedString &other) {
        this->free();
        if (other.is_dynamic()) {
            *this = StaticOptimizedString(other.get(), StorageLocation::Dynamic);
        } else {
            this->string_data = other.string_data;
        }

        return *this;
    }

    StaticOptimizedString &StaticOptimizedString::operator=(StaticOptimizedString &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        this->free();

        this->string_data = std::exchange(other.string_data, nullptr);
        return *this;
    }


    void StaticOptimizedString::free() const {
        if (this->string_data.p() == nullptr) {
            return;
        }
        if (!this->is_dynamic()) {
            return;
            // Since the value we are pointing to is static it will be deallocated by the os on exit or func exit
        }

        ::operator delete(std::bit_cast<void *>(this->c_str()), static_cast<std::align_val_t>(8));
    }


    StaticOptimizedString::~StaticOptimizedString() {
        this->free();
    }

    bool StaticOptimizedString::operator==(const std::string_view &other) const {
        return this->get() == other;
    }

    void StaticOptimizedString::allocate_long_string(const std::string_view value) {
        // We allocate 8 extra bytes at the start since we want to shove the string length there
        // Then we allocate the last byte for null term
        auto *allocation = operator new(value.length() + 9, static_cast<std::align_val_t>(8));

        // Store the string length at the start of our allocation
        *static_cast<size_t *>(allocation) = value.length();

        // Skip over our size
        char *string_allocation = static_cast<char *>(allocation) + sizeof(size_t);

        memcpy(string_allocation, value.data(), value.length());
        string_allocation[value.length()] = 0; // Nulls the end

        auto allocation_raw = std::bit_cast<uintptr_t>(allocation);
        // Sets a flag to annotate that this string is dynamic
        allocation_raw |= this->DynamicMask;

        this->string_data = allocation_raw;

        // Sanity check
        if (this->string_data.p() != allocation) {
            throw std::runtime_error("Allocation has a broken pointer");
        }
    }

    void StaticOptimizedString::set(const std::string_view value, const StorageLocation location) {
        if (value.empty()) {
            this->string_data = nullptr;
            return; // Not accurate to the game
        }

        if (value.length() > 0x7F || location == StorageLocation::Dynamic) {
            allocate_long_string(value);
            return;
        }

        auto string_ptr = std::bit_cast<uintptr_t>(value.data()) & this->Mask;

        if (string_ptr != std::bit_cast<uintptr_t>(value.data())) {
            throw std::runtime_error("Allocation has a broken pointer");
        }

        // Encode the length into the pointer
        const auto size = value.length() << 48;

        string_ptr |= size;

        this->string_data = string_ptr;
    }

    const char *StaticOptimizedString::c_str() const {
        return this->string_data.p();
    }

    std::string_view StaticOptimizedString::get() const {
        if (!this->is_dynamic()) {
            return std::string_view(this->string_data.p(), this->length());
        }

        const auto length = this->length();

        // The offset is to handle the fact there is a length packed
        return std::string_view(this->c_str() + sizeof(size_t), length);
    }

    bool StaticOptimizedString::is_dynamic() const {
        return (this->string_data.flags() & 0x80) == 0x80;
    }

    size_t StaticOptimizedString::length() const {
        if (this->is_dynamic()) {
            // Read back our size which we pack into the start
            return *std::bit_cast<size_t *>(this->string_data.p());
        } else {
            return this->string_data.flags() & 0x7F;
        }
    }

    bool StaticOptimizedString::operator==(const StaticOptimizedString &other) const {
        return this->get() == other.get();
    }
} // Bedrock
