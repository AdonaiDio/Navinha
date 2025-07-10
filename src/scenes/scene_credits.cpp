#include <bn_core.h>
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_keypad.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "bn_regular_bg_items_fundo.h"

#include "scene_credits.h"


namespace adonai
{
    Credits::Credits() {}

    Scene Credits::execute()
    {
        bn::regular_bg_ptr map = bn::regular_bg_items::fundo.create_bg(0 , 0);

        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();
        bn::vector<bn::sprite_ptr, 32> text_sprites; //output_sprites
        text_generator.generate(0, -20, "Developed by", text_sprites);
        text_generator.generate(0, -4, "Adonai Diógenes ( @AdonaiDio )", text_sprites);
        text_generator.generate(0, 20, "Music by", text_sprites);
        text_generator.generate(0, 36, "Gilberto Lobo ( @wolf_ezel )", text_sprites);

        while(true)
        {
            if( bn::keypad::start_pressed() )
            {
                return Scene::START_MENU;
            }
            bn::core::update();
        }   
    }
}