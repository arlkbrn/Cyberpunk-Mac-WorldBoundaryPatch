#include <dlfcn.h>
#include <iostream>
#include <mach-o/dyld.h>
#include "Image.hpp"

namespace WorldBoundaryPatch::Image 
{
static uint32_t GetImageIndex() {
    static const auto imageIndex = []() -> uint32_t
    {
        for (uint32_t currImageIndex = 0; currImageIndex < _dyld_image_count(); currImageIndex++)
        {
            std::string_view imageName = _dyld_get_image_name(currImageIndex);
            if (imageName.ends_with("Cyberpunk2077"))
                return currImageIndex;
        }
        return 0;
    }();
    return imageIndex;
}

uintptr_t GetImageBase() {
    if (GetImageIndex() == 0) {
        return 0;
    }
    static const auto base = std::bit_cast<uintptr_t>(_dyld_get_image_header(GetImageIndex()));
    return base;
}
}