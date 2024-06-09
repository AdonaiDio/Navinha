//butano
#include <bn_core.h>
#include "bn_log.h"
#include "bn_sprite_ptr.h"

//my code
#include "player.h"
#include "controller.h"

//assets
#include "bn_sprite_items_gizmos_16x16.h"

//this
#include "scene_stage_1.h"

namespace adonai
{
    Stage_1::Stage_1(Player& player)
    : _player(&player) {}

    Scene Stage_1::execute(bn::fixed_point spawn_location)
    {
        //spawn_location = bn::fixed_point(-30,-30);
        //bn::regular_bg_ptr map = bn::regular_bg_items::splash_logo.create_bg(0 , 0);
        
        BN_LOG("Entrou na cena Stage_1");

        _player->set_pos(spawn_location);
        _player->sprite().set_visible(true);
        _player->sprite().set_z_order(-1);
        // instancia o controller
        adonai::Controller controller = adonai::Controller();

        bn::sprite_ptr gizmos = bn::sprite_items::gizmos_16x16.create_sprite(0,0,1);

        while(true)
        {
            controller.InputAction_Move(*_player);
            
            gizmos.set_position(_player->pos());

            bn::core::update();
        }   
    }
}