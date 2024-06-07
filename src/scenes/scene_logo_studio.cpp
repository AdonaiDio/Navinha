#include "scene_logo_studio.h"
#include <bn_core.h>


namespace adonai
{
    Scene LOGO_STUDIO::execute()
    {
        //bn::regular_bg_ptr map = bn::regular_bg_items::splash_logo.create_bg(0 , 0);
        int timer = 0;
        while(true)
        {
            if(timer > 180){
                return Scene::STAGE_1;
            }
            
            ++timer;
            bn::core::update();
        }   
    }
}