cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(bedrock_test_mod)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")  # for /MT

add_library(bedrock_test_mod SHARED src/dllmain.cpp
        src/sdk/threading.cpp
        src/sdk/threading.hpp
        src/hooks/hook_manager.cpp
        src/hooks/hook_manager.hpp
        src/hooks/Keyboard.cpp
        src/hooks/Keyboard.hpp
        src/sbm.hpp
        src/sdk/hashed_string.cpp
        src/sdk/hashed_string.hpp
        src/sdk/brstd/bitset.hpp
        src/sdk/molang/expression_node.cpp
        src/sdk/molang/expression_node.hpp
        src/sdk/molang/molang_parse_config.hpp
        src/sdk/molang/expression_op.hpp
        src/sdk/sem_ver.cpp
        src/sdk/sem_ver.hpp
        src/sdk/memory/packed_pointer.cpp
        src/sdk/memory/packed_pointer.hpp
        src/sdk/memory/static_optimized_string.cpp
        src/sdk/memory/static_optimized_string.hpp)


include(FetchContent)

FetchContent_Declare(
        kiero
        GIT_REPOSITORY https://github.com/BasedInc/kiero.git
        GIT_TAG master  # Or a specific commit/tag
)

set(KIERO_INCLUDE_D3D12 ON)
set(KIERO_USE_MINHOOK OFF)
target_include_directories(bedrock_test_mod PUBLIC ${kiero_SOURCE_DIR})
FetchContent_MakeAvailable(kiero)

FetchContent_Declare(
        safetyhook
        GIT_REPOSITORY "https://github.com/cursey/safetyhook.git"
        GIT_TAG "origin/main"
)
FetchContent_MakeAvailable(safetyhook)

FetchContent_Declare(
        libhat
        GIT_REPOSITORY "https://github.com/BasedInc/libhat.git"
        GIT_TAG "origin/master"
)
FetchContent_MakeAvailable(libhat)

FetchContent_Declare(
        GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
        GIT_TAG "origin/main"
)

FetchContent_MakeAvailable(GSL)


target_link_libraries(bedrock_test_mod PRIVATE safetyhook)
target_link_libraries(bedrock_test_mod PRIVATE kiero)
target_link_libraries(bedrock_test_mod PRIVATE libhat)
target_link_libraries(bedrock_test_mod PRIVATE GSL)
