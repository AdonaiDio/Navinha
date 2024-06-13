//butano
#include <bn_core.h>
#include "bn_log.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"
#include "bn_colors.h"
#include "bn_bg_palette_color_hbe_ptr.h"
#include "bn_unique_ptr.h"

//my code
#include "player.h"
#include "controller.h"
#include "../../include/effects/bg_fx.h"
#include "shoot.h"

//assets
#include "bn_sprite_items_gizmos_16x16.h"
#include "bn_regular_bg_items_sky_solid_color.h"
#include "bn_sprite_items_shoot.h"

//this
#include "scene_stage_1.h"

namespace adonai
{
    Stage_1::Stage_1(Player& player)
    : _player(&player) {}

    Scene Stage_1::execute(bn::fixed_point spawn_location)
    {
        //TODO: Usar o H-Blank(hbe) para criar efeito de troca de cor do background (gradiente)

        bn::regular_bg_ptr r_bg_1 = bn::regular_bg_items::sky_solid_color.create_bg(0 , 0);

        //------------------
        BN_LOG("Entrou na cena Stage_1");

        _player->set_pos(spawn_location);
        _player->sprite().set_visible(true);
        _player->sprite().set_z_order(-1);
        // instancia o controller
        adonai::Controller controller = adonai::Controller();

        bn::sprite_ptr gizmos = bn::sprite_items::gizmos_16x16.create_sprite(0,0,1);
        
        while(true)
        {
            //eu não sei... Coloquei isso aí para reutilizar igual em outro lugar. eu acho.
            #include  "../../include/effects/bg_fx.hpp"
            BG_GRADIENT_FX(r_bg_1);
            
            // r_bg_1 side scroll
            r_bg_1.set_position( bn::fixed_point(r_bg_1.position().x()-((bn::fixed) 0.05f), 0));

            controller.InputAction_Move(*_player);
            controller.InputAction_Shoot(*_player);
            
            gizmos.set_position(_player->pos());

            bn::core::update();
        }
    }
}