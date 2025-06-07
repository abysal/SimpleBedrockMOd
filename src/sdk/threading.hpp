//
// Created by Akashic on 5/30/2025.
//

#ifndef THREADING_HPP
#define THREADING_HPP
#include <array>
#include <libhat/access.hpp>
#include <thread>

namespace Bedrock {

    class Scheduler {
    public:
        Scheduler() = delete;

        [[nodiscard]] std::thread::id get_thread_id() const {
            return hat::member_at<std::thread::id>(this, 0x60);
        }
    private:

        std::array<std::byte, 0x68> scheduler{};
    };

    class Threading {
    public:
        static Scheduler* getMainThreadScheduler();
    };

} // Bedrock

#endif //THREADING_HPP
