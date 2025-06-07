//
// Created by Akashic on 5/30/2025.
//

#include "threading.hpp"
#include "../hooks/hook_manager.hpp"

namespace Bedrock {
    Scheduler *Threading::getMainThreadScheduler() {
        struct HookInit {
            struct PtrWrapper {
                Scheduler *inner;
            };

            typedef PtrWrapper (*getMainThreadSchedulerGame)();

            HookInit() {
                this->ptr = static_cast<getMainThreadSchedulerGame>(sbm::HookManager::pattern_address<
                    sbm::ThreadingGetMainThreadScheduler>());
            }

            getMainThreadSchedulerGame ptr{};
        };

        static HookInit hook_init{};
        return hook_init.ptr().inner;
    }
} // Bedrock
