#include "scene_stage_1.h"
#include <bn_core.h>


namespace adonai
{
    Scene Stage_1::execute()
    {
        //bn::regular_bg_ptr map = bn::regular_bg_items::splash_logo.create_bg(0 , 0);
        while(true)
        {

            bn::core::update();
        }   
    }
}