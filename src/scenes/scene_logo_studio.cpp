#include <bn_core.h>
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"

#include "bn_regular_bg_items_logo_studio_bg.h"

#include "scene_logo_studio.h"


namespace adonai
{
    Logo_Studio::Logo_Studio() {}

    Scene Logo_Studio::execute()
    {
        bn::regular_bg_ptr map = bn::regular_bg_items::logo_studio_bg.create_bg(0 , 0);
        int timer = 0;

        while(true)
        {
            if(timer > 200){
                return Scene::START_MENU;
            }
            
            ++timer;
            bn::core::update();
        }   
    }
}