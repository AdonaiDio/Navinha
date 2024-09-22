//butano
#include <bn_core.h>
#include "bn_log.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"
#include "bn_colors.h"
#include "bn_bg_palette_color_hbe_ptr.h"
#include "bn_unique_ptr.h"

//assets
#include "bn_sprite_items_gizmos_16x16.h"
#include "bn_regular_bg_items_sky_solid_color.h"
#include "bn_sprite_items_shoot.h"
#include "bn_music_items.h"

//my code
#include "player.h"
#include "enemy.h"
#include "controller.h"
#include "../../include/effects/bg_fx.h"
#include "../../include/actors/shot_enemy.h"
#include "../../include/hud/hud_energy_bar.h"
#include "../../include/hud/hud_hp_bar.h"
#include "hud_game_over.h"

#include "ntt_list_stage_1.h"

//scripts
#include "move_test_script.cpp"

//this
#include "scene_stage_1.h"

namespace adonai
{
    Stage_1::Stage_1(Player& player)
    : _player(&player) {
    }

    Scene Stage_1::execute(bn::fixed_point spawn_location)
    {

        bn::regular_bg_ptr r_bg_1 = bn::regular_bg_items::sky_solid_color.create_bg(0, 0);
        
        
        adonai::hud_energy_bar hud_energy_bar = adonai::hud_energy_bar(*_player);
        for (int i = 0; i < hud_energy_bar.energy_bar_sprites.size(); i++)
        {   hud_energy_bar.energy_bar_sprites.at(i).set_z_order(-2); }

        adonai::hud_hp_bar hud_hp_bar = adonai::hud_hp_bar(*_player);
        for (int i = 0; i < hud_hp_bar.hp_bar_sprites.size(); i++)
        {   hud_hp_bar.hp_bar_sprites.at(i).set_z_order(-2); }
        
        adonai::hud_game_over game_over = adonai::hud_game_over(0, -80-16);
        
        BN_LOG("Entrou na cena Stage_1");

        _player->pos(spawn_location);
        _player->sprite().set_visible(true);
        _player->sprite().set_z_order(-1);
        _player->can_act = true;
        // instancia o controller
        adonai::Controller controller = adonai::Controller(*_player);

        //inimigos
        Enemy* enemy_1 = new Enemy( bn::sprite_items::spaceship_2, 
                                    bn::fixed_point(16*(7+1), (16*2)+8),
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1, 
                                    3);
        Enemy* enemy_2 = new Enemy( bn::sprite_items::spaceship_1,
                                    bn::fixed_point(16*(7+2), (16*2)+8),
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1, 
                                    3);
        Enemy* enemy_3 = new Enemy( bn::sprite_items::spaceship_1,
                                    bn::fixed_point(16*(7+3), (16*2)+8),
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1, 
                                    3);
        //identificar o grupo de inimigos
        //enemy_1.identify_snakeGroup();

        Enemy* enemy_4 = new Enemy( bn::sprite_items::spaceship_2,
                                    bn::fixed_point(0, 0),
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_2, 
                                    15, 7, 3); 
        Enemy* enemy_5 = new Enemy( bn::sprite_items::spaceship_1,
                                    bn::fixed_point(0, 32),
                                    bn::sprite_items::shoot, 
                                    E_Shot_Type::E_Shot_Type_1, 
                                    3);
        enemy_5->sprite().set_z_order(-5);
        // bn::sprite_ptr gizmos = bn::sprite_items::gizmos_16x16.create_sprite(0,0,1);
        
        bn::music_items::nova_theme.play();

        // //teste tiro inimigo
        // Shot_Enemy* shot_e = new Shot_Enemy(bn::sprite_items::shoot, bn::fixed_point(0,0));
        // shot_e->sprite().set_visible(true);
        // shot_e->_state = adonai::Shot_State::SHOOTING;

        // //DEBUG CPU USAGE=======
        // bn::fixed max_cpu_usage;
        // int counter = 1;
        // //======================
        int count_frames_update = 0;

        //Start Scripts
        Move_Test_Script move_script;
        //conecte os scripts aos objetos que vão fazer algo no start() do script
        move_script.start(*enemy_5);


        while(true)
        {
            ///////
            //eu não sei... Coloquei isso aí para reutilizar igual em outro lugar. eu acho.
            #include  "../../include/effects/bg_fx.hpp"
            BG_GRADIENT_FX(r_bg_1);
            // r_bg_1 side scroll
            r_bg_1.set_position( bn::fixed_point(r_bg_1.position().x()-((bn::fixed) 0.05f), 0));
            ///////
            
            //chamar os update() dos scripts e seus associados
            move_script.update(*enemy_5);
            

            controller.update();
            
            // gizmos.set_position(_player->pos());

            if(enemy_1->hp() > 0 || enemy_1->wait_to_destroy) { enemy_1->update(); }
            if(enemy_2->hp() > 0 || enemy_2->wait_to_destroy) { enemy_2->update(); }
            if(enemy_3->hp() > 0 || enemy_3->wait_to_destroy) { enemy_3->update(); }
            if(enemy_4->hp() > 0 || enemy_4->wait_to_destroy) { enemy_4->update(); }
            if(enemy_5->hp() > 0 || enemy_5->wait_to_destroy) { enemy_5->update(); }
            //_player->update();
            if(_player->hp() > 0 || _player->wait_to_destroy) { _player->update(); }
            hud_energy_bar.update();
            hud_hp_bar.update();
            

            // teste de tiro
            // TODO: Isso tem que ser coisa de script futuramente
            if(_player->hp() > 0){
                count_frames_update++;
                if (count_frames_update > 14){
                    count_frames_update = 0;
                    if(enemy_4->hp()>0)
                    {
                        enemy_4->shoot();
                    }
                }
            }
            if(ntt_shots.size() > 0){
                for (int i = 0; i < ntt_shots.size(); i++)
                {
                    // ntt_shots.at(i)->move_forward(bn::fixed_point(
                    //                                     ntt_shots.at(i)->pos().x()-16,
                    //                                     ntt_shots.at(i)->pos().y()-16));
                    ntt_shots.at(i)->update();
                }
            }

            BN_LOG("player x:",_player->pos().x(), " y:",_player->pos().y());
            if(_player->hp() <= 0){ game_over.update(); }

            
            // //teste tiro inimigo
            // shot_e->move_forward();
            
            // //DEBUG CPU USAGE=================
            // bn::fixed max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
            // --counter;

            // if(! counter)
            // {
            //     BN_LOG((max_cpu_usage * 100).right_shift_integer(), "%");
            //     max_cpu_usage = 0;
            //     counter = 10;
            // }
            // //=================

            bn::core::update();
        }
    }
}