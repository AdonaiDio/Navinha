#pragma once

#include "bn_regular_bg_ptr.h"
#include "scene.h"

namespace adonai
{
    class Bg_FX
    {
        public:
            bn::span<bn::color> bg_palette_hbe(bn::regular_bg_ptr r_bg);
    };
}