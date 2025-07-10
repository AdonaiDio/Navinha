#pragma once

#include "scene.h"
#include "i_scene.h"

namespace adonai 
{
    class Butano_Logo : I_Scene
    {       
        public:
            Butano_Logo();
            Scene execute();
    };
}