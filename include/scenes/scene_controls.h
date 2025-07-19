#pragma once

#include "scene.h"
#include "i_scene.h"

namespace adonai 
{
    class Controls : I_Scene
    {       
        public:
            Controls();
            Scene execute();
    };
}