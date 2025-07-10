#include <bn_core.h>
#include "bn_regular_bg_ptr.h"
#include "bn_sound_items.h"
#include "bn_keypad.h"

#include "bn_regular_bg_items_start_menu_bg.h"

#include "scene_start_menu.h"


namespace adonai
{
    Start_Menu::Start_Menu() {}

    Scene Start_Menu::execute()
    {
        bn::regular_bg_ptr map = bn::regular_bg_items::start_menu_bg.create_bg(0 , 0);
        int timer = 0;
        bool started = false;

        while(true)
        {
            if(bn::keypad::start_pressed()){
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