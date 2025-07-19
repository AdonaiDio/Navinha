#include <bn_core.h>
#include "bn_regular_bg_ptr.h"
#include "bn_sound_items.h"
#include "bn_keypad.h"

#include "bn_regular_bg_items_controls_bg.h"

#include "scene_controls.h"


namespace adonai
{
    Controls::Controls() {}

    Scene Controls::execute()
    {
        bn::regular_bg_ptr map = bn::regular_bg_items::controls_bg.create_bg(0 , 0);
        int timer = 0;
        bool started = false;

        while(true)
        {
            if(bn::keypad::any_pressed()){
                started = true;
            }
            if(started){
                if(timer == 0){
                //som de click
                    bn::sound_items::select.play();
                }
                if(timer > 50){
                    return Scene::STAGE_1;
                }
                ++timer;

            }
            bn::core::update();
        }   
    }
}