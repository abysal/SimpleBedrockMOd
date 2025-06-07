//
// Created by Akashic on 6/1/2025.
//

#ifndef HASHED_STRING_HPP
#define HASHED_STRING_HPP
#include <string>
#include <string_view>


class HashedString {
public:
    HashedString() noexcept = default;

    constexpr explicit HashedString(const std::string_view str) noexcept : hash(compute_hash(str)),
                                                                           string(std::string(str)) {
    }

    constexpr HashedString(const std::string &str) noexcept : hash(compute_hash(str)), string(str) {
    }

    constexpr HashedString(const char *str) noexcept : hash(compute_hash(str)), string(std::string(str)) {
    }

    constexpr HashedString(std::string &&str) noexcept : hash(compute_hash(str)), string(std::move(str)) {
    }

    constexpr HashedString(HashedString &&other) noexcept : hash(other.hash), string(std::move(other.string)) {
        other.hash = 0;
        other.last_match = nullptr;
    }

    constexpr HashedString(const HashedString &other) noexcept {
        if (this == &other) {
            return;
        }
        this->hash = other.hash;
        this->string = other.string;
    }

    bool constexpr operator==(const HashedString &other) const noexcept {
        if (this->hash == other.hash) {
            if (this->last_match == std::addressof(other) && other.last_match == this) {
                return true;
            }

            if (this->string == other.string) {
                this->last_match = std::addressof(other);
                other.last_match = this;
                return true;
            }
        }

        this->last_match = nullptr;
        return false;
    }

    bool constexpr operator!=(const HashedString &other) const noexcept {
        return !(*this == other);
    }

    constexpr std::strong_ordering operator<=>(const HashedString &other) const noexcept {
        if (this->hash != other.hash) {
            return this->hash <=> other.hash;
        }

        return this->string <=> other.string;
    }

    constexpr operator std::string_view() const noexcept {
        return std::string_view(this->string);
    }

    constexpr operator const std::string &() const noexcept {
        return this->string;
    }

    [[nodiscard]] constexpr size_t get_hash() const noexcept {
        return this->hash;
    }

private:
    static constexpr uint64_t compute_hash(std::string_view string) {
        if (string.empty()) {
            return 0;
        }

        uint64_t hash = 0xCBF29CE484222325;
        for (const char c: string) {
            hash = c ^ (0x100000001B3ull * hash);
        }
        return hash;
    }

private:
    uint64_t hash{0};
    std::string string{};
    mutable const HashedString *last_match{nullptr};
};

namespace std {
    template<>
    struct hash<HashedString> {
        size_t operator()(HashedString const &str) const noexcept { return str.get_hash(); }
    };
}

#endif //HASHED_STRING_HPP
