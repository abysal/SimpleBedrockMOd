//
// Created by Akashic on 5/30/2025.
//

#include "hook_manager.hpp"

namespace sbm {
    HookManager &HookManager::get_instance() {
        static HookManager instance;
        return instance;
    }

    HookManager::HookManager() {
        this->insert_signature<ThreadingGetMainThreadScheduler>();
        this->insert_signature<DetailsExpressionNodeParse>();
        this->insert_signature<ExpressionNodeExpressionNode>();
        this->insert_signature<OptionsGetFov>();
        this->insert_signature<TessellatorBegin>();
        this->insert_signature<MinecraftUiRenderContextCtor>();
        this->insert_signature<ScreenViewSetupAndRender>();

        this->insert_signature_windows<InvokeKeyDownEventHandlers>();
        this->insert_signature_windows<InvokeKeyUpEventHandlers>();
        this->insert_signature_windows<InvokeDelegatesKeyDownHandler>();
    }
} // sbm
