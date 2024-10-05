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
#include "enemy.h"
#include "controller.h"
#include "shot.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"

//assets
#include "bn_sprite_items_gizmos_16x16.h"
#include "bn_regular_bg_items_tela.h"
#include "bn_sprite_items_shoot.h"
#include "bn_music_items.h"

//this
#include "scene_test.h"

namespace adonai
{
    Test::Test(Player& player)
    : _player(&player) {
    }

    Scene Test::execute(bn::fixed_point spawn_location)
    {

        bn::regular_bg_ptr r_bg_1 = bn::regular_bg_items::tela.create_bg(0, 0);
        
        adonai::hud_energy_bar hud_energy_bar = adonai::hud_energy_bar(*_player);
        for (int i = 0; i < hud_energy_bar.energy_bar_sprites.size(); i++)
        {   hud_energy_bar.energy_bar_sprites.at(i).set_z_order(-2); }

        adonai::hud_hp_bar hud_hp_bar = adonai::hud_hp_bar(*_player);
        for (int i = 0; i < hud_hp_bar.hp_bar_sprites.size(); i++)
        {   hud_hp_bar.hp_bar_sprites.at(i).set_z_order(-2); }
        
        adonai::hud_game_over game_over = adonai::hud_game_over(0, -80-16);
        
        BN_LOG("CENA DE TESTE");

        _player->pos(spawn_location);
        _player->sprite().set_visible(true);
        _player->sprite().set_z_order(-1);
        _player->can_act = true;
        // instancia o controller
        adonai::Controller controller = adonai::Controller(*_player);

        //inimigos
        // Enemy* enemy_1 = new Enemy( bn::fixed_point(0, 0),
        //                             bn::sprite_items::spaceship_1,
        //                             bn::sprite_items::shoot, 
        //                             E_Shot_Type::E_Shot_Type_1, 
        //                             3);
        
        bn::music_items::nova_theme.play();

        while(true)
        {
            controller.update();
            
            // gizmos.set_position(_player->pos());

            // if(enemy_1->hp() > 0 || enemy_1->wait_to_destroy) { enemy_1->update(); }
            //_player->update();
            if(_player->hp() > 0 || _player->wait_to_destroy) { _player->update(); }
            hud_energy_bar.update();
            hud_hp_bar.update();
            
            if(_player->hp() <= 0){ game_over.update(); }

            bn::core::update();
        }
    }
}