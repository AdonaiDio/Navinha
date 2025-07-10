#include <bn_core.h>
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "bn_regular_bg_items_butano_background.h"

#include "scene_butano_logo.h"


namespace adonai
{
    Butano_Logo::Butano_Logo() {}

    Scene Butano_Logo::execute()
    {
        bn::regular_bg_ptr map = bn::regular_bg_items::butano_background.create_bg(0 , 0);
        int timer = 0;

        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();
        bn::vector<bn::sprite_ptr, 32> text_sprites; //output_sprites
        text_generator.generate(0, 60, "Powered by BUTANO", text_sprites);

        while(true)
        {
            if(timer > 180){
                return Scene::LOGO_STUDIO;
            }
            
            ++timer;
            bn::core::update();
        }   
    }
}