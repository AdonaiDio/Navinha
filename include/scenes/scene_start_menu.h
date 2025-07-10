#pragma once

#include "scene.h"
#include "i_scene.h"

namespace adonai 
{
    class Start_Menu : I_Scene
    {       
        public:
            Start_Menu();
            Scene execute();
    };
}