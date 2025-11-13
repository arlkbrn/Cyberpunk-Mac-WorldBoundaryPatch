#include <dobby.h>
#include <iostream>
#include "WorldBoundaryPatch.hpp"
#include "Image.hpp"

namespace WorldBoundaryPatch
{

namespace Addresses
{
    constexpr uintptr_t WorldBoundarySystem_Tick = 0x1027ac2cc - 0x100000000;
}

static gameWorldBoundarySystemTick_t real_Tick = nullptr; // Set by Dobby

void fake_Tick(void* a1, void* a2, void* a3, void* a4) {
    return;
    // real_Tick(a1, a2, a3, a4);
}

__attribute__((constructor))
int entry() {
    std::cout << "[WorldBoundaryPatch] Finding image base...\n";

    uintptr_t imageBase = Image::GetImageBase();
    if (imageBase == 0) {
        std::cout << "[WorldBoundaryPatch] Failed to get image base!\n";
        std::cout << "[WorldBoundaryPatch] Exiting...\n";
        exit(1);
    }
    
    std::cout << "[WorldBoundaryPatch] Found image base!\n";
    
    std::cout << "[WorldBoundaryPatch] Hooking...\n";
    
    uintptr_t tickAddress = Addresses::WorldBoundarySystem_Tick + imageBase;
    int result = DobbyHook(reinterpret_cast<void*>(tickAddress), reinterpret_cast<void*>(fake_Tick), reinterpret_cast<void**>(&real_Tick));

    if (result != 0) {
        std::cout << "[WorldBoundaryPatch] Hooking failed.\n";
        std::cout << "[WorldBoundaryPatch] Exiting...\n";
        exit(1);
    }
    
    std::cout << "[WorldBoundaryPatch] Hooked and patched!\n";
}
}