#include "scene_stage_1.h"
#include <bn_core.h>

namespace adonai
{
    Stage_1::Stage_1(Player& player)
    : _player(&player) {}

    Scene Stage_1::execute(bn::fixed_point spawn_location)
    {
        //spawn_location = bn::fixed_point(-30,-30);
        //bn::regular_bg_ptr map = bn::regular_bg_items::splash_logo.create_bg(0 , 0);

        _player->spawn(spawn_location);
        
        while(true)
        {

            bn::core::update();
        }   
    }
}