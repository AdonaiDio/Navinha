#pragma once

#include "scene.h"
#include "i_scene.h"

namespace adonai 
{
    class Credits : I_Scene
    {       
        public:
            Credits();
            Scene execute();
    };
}