#pragma once

#include "scene.h"
#include "i_scene.h"

namespace adonai 
{
    class Logo_Studio : I_Scene
    {       
        public:
        void SpawnEnemy() override{
        }
            Logo_Studio();
            Scene execute();
    };
}