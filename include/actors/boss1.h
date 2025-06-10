#pragma once

#include "bn_log.h"

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_rect.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_rect.h"

#include "explosion_big_fx.h"

#include "enemy.h"
#include "shot_enemy.h"
#include "bn_sprite_items_shot_4.h"

#include "bn_sprite_items_boss1_part1.h"
#include "bn_sprite_items_boss1_part2.h"
#include "bn_regular_bg_items_boss1.h"
#include "bn_regular_bg_items_boss1_laser_anim.h"

// scripts 

namespace adonai
{
    class Boss1
    {
    #define LASER_OFFSET_X 64
    #define LASER_OFFSET_Y 24
    #define SHOT_OFFSET_X 72
    #define SHOT_OFFSET_Y 3

    private:
        /* data */
        bn::regular_bg_ptr boss1_bg;
        const bn::point sprite_pivot = bn::point(72,0);
        bn::fixed_point _pos;
        
        //estados da nave
        bool dead = false;

        //controle das partes
        const bn::point laser_OFFSET = bn::point(sprite_pivot.x()-8, sprite_pivot.y()+24);
        const bn::point shots_OFFSET = bn::point(sprite_pivot.x(), sprite_pivot.y()+3);
        //boss nao tem HP mas ele é destruido quando todas as suas partes estiverem destruidas/hp<=0
        Explosion_Big_FX explosion_big = Explosion_Big_FX();
        Explosion_Big_FX explosion_big2 = Explosion_Big_FX();
        Explosion_Big_FX explosion_big3 = Explosion_Big_FX();
        Explosion_FX explosion = Explosion_FX();
        Explosion_FX explosion2 = Explosion_FX();
        Explosion_FX explosion3 = Explosion_FX();
        
        bn::regular_bg_ptr laser_bg;
        const bn::point LASER_COL_OFFSET = bn::point(-32,23);
        bn::rect laser_col = bn::rect(  (int)_pos.x()+LASER_COL_OFFSET.x(),
                                        (int)_pos.y()+LASER_COL_OFFSET.y(),
                                        180, 9  );
        bool laser_col_enable = false;
        
        bn::regular_bg_animate_action<13> laser_start_anim = bn::create_regular_bg_animate_action_once(
                    laser_bg, 5, bn::regular_bg_items::boss1_laser_anim.map_item(), 
                    0,1,2,3,4,5,6,7,8,9,10,11,12
        );
        bn::regular_bg_animate_action<4> laser_sustain_anim = bn::create_regular_bg_animate_action_forever(
                    laser_bg, 5, bn::regular_bg_items::boss1_laser_anim.map_item(), 
                    12,13,14,15
        );
        bn::regular_bg_animate_action<13> laser_end_anim = bn::create_regular_bg_animate_action_once(
                    laser_bg, 5, bn::regular_bg_items::boss1_laser_anim.map_item(), 
                    11,10,9,8,7,6,5,4,3,2,1,0,0
        );

        enum Laser_State: int8_t{
            LASER_NONE_STATE=0,
            LASER_START_STATE=1,
            LASER_SUSTAIN_STATE=2,
            LASER_END_STATE=3
        }laser_state = Laser_State::LASER_NONE_STATE;

        int laser_frame_counter = 0;
        const int LASER_DURATION = 5*60; // duração em frames

        const bn::fixed_point ORBS_OFFSET = bn::fixed_point{70,-8};
        bn::array<Shot_Enemy, 40>* ntt_shots; 
        Shot_Enemy _shot = Shot_Enemy(bn::sprite_items::shot_4);

        int destroy_frame_counter = 0;

        public:
        Enemy part_laser;
        Enemy part_shots;
        Enemy* part_laser_ptr;
        Enemy* part_shots_ptr;
        
        Boss1(bn::fixed_point initial_pos):
            boss1_bg (bn::regular_bg_items::boss1.create_bg(initial_pos)),
            laser_bg (bn::regular_bg_items::boss1_laser_anim.create_bg(initial_pos,14)),
            _pos(initial_pos),
            part_laser(Enemy(initial_pos+bn::point(LASER_OFFSET_X, LASER_OFFSET_Y), bn::sprite_items::boss1_part1, 3)),
            part_shots(Enemy(initial_pos+bn::point(SHOT_OFFSET_X,SHOT_OFFSET_Y), bn::sprite_items::boss1_part2, 2))
        {
            boss1_bg.set_priority(3);
            laser_bg.set_priority(1);
            laser_bg.set_z_order(0);
            laser_bg.set_visible(false);
            part_laser.sprite().set_bg_priority(2);
            part_laser._available = false;
            part_shots.sprite().set_bg_priority(2);
            part_shots._available = false;

            part_laser.col(bn::rect((int)(part_laser.pos().x()-2), (int)(part_laser.pos().y()-2), 30,14));
            part_shots.col(bn::rect((int)part_shots.pos().x()+2, (int)part_shots.pos().y()+0, 28,14));

        };
        ~Boss1();
        // Para associar a lista de ntt_shots presentes na cena que ele foi criado.
        void assign_ntt_shots(bn::array<Shot_Enemy, 40>* ntt_shots_ptr){
            ntt_shots = ntt_shots_ptr;
        }
        
        void Move(bn::fixed_point pos){
            _pos = pos;
            //mudar a posição das parts com seus respectivos offsets
            part_laser_ptr->pos(pos+laser_OFFSET);
            part_shots_ptr->pos(pos+shots_OFFSET);
            boss1_bg.set_position(_pos);
            laser_bg.set_position(_pos);
            laser_col.set_position((int)_pos.x()+LASER_COL_OFFSET.x(), (int)_pos.y()+LASER_COL_OFFSET.y());
        }

        //OrbsAttack chamado 1 vez
        void OrbsAttack(){
            for (int i = 0; i < ntt_shots->size(); i++)
            {
                if(ntt_shots->at(i)._available == true){
                    ntt_shots->at(i)._available = false;
                    ntt_shots->at(i).copy_Shot_Enemy( Shot_Enemy(_shot, (_pos + ORBS_OFFSET) ));
                    ntt_shots->at(i).pre_direction = normalize(GLOBALS::global_player->pos() - (_pos + ORBS_OFFSET));
                    ntt_shots->at(i).sprite().set_bg_priority(1);
                    break;
                }
            }
        }

        //LaserAttack chamado 1 vez
        void LaserAttack(){
            //start laser
            laser_state = Laser_State::LASER_START_STATE;
            laser_bg.set_visible(true);
            laser_col_enable = false;
        }

        // Lida com os estados do ataque de laser todo frame
        void LaserUpdate(){
            switch (laser_state)
            {
            case Laser_State::LASER_START_STATE:
                /* ao finalizar animação mudar estado para o Sustain */
                //anim 0-11
                laser_start_anim.update();
                if(laser_start_anim.done()){
                    laser_state = Laser_State::LASER_SUSTAIN_STATE;
                    laser_start_anim.reset();
                    laser_col_enable = true;
                }
                break;
            
            case Laser_State::LASER_SUSTAIN_STATE:
                /* ao encerrar tempo de sustentação mudar estado para End */
                //anim 12-15
                laser_sustain_anim.update();
                if(++laser_frame_counter >= LASER_DURATION){
                    laser_state = Laser_State::LASER_END_STATE;
                    //laser_sustain_anim.reset();
                    laser_col_enable = false;
                }
                break;
            
            case Laser_State::LASER_END_STATE:
                /* ao finalizar animação mudar estado para None */
                //anim 11-0
                laser_end_anim.update();
                if(laser_end_anim.done()){
                    laser_state = Laser_State::LASER_NONE_STATE;
                    laser_end_anim.reset();
                    laser_frame_counter = 0;
                    laser_bg.set_visible(false);
                }
                break;
            
            default:
                break;
            }
            LaserCollision();
        }
        void LaserCollision(){
            if (!laser_col_enable) return;
            
            if(GLOBALS::global_player->col().intersects(laser_col)){
                GLOBALS::global_player->receive_hit(2);
            }
        }

        void update(){
            if(dead) return;
            //temp buttons for actions
            if(bn::keypad::l_pressed()){
                LaserAttack();
            }
            if(bn::keypad::r_pressed()){
                OrbsAttack();
            }
            //
            if(part_laser_ptr->hp()<=0 && part_shots_ptr->hp()<=0){
                Destroy();
                return;
            }
            LaserUpdate();
            // UpdateBossSpawnEnemy();
        }

        void Destroy(){
            //faça algo até o boss ser eliminado
            Move(bn::fixed_point(_pos.x(), _pos.y()+0.3));
            boss1_bg.set_map(bn::regular_bg_items::boss1.map_item(),1);

            // cada 25 frames explosion; cada 60 frames explosion_big;
            const int explo_dur = 25;
            const int explo_big_dur = 60;
            if(++destroy_frame_counter <= 9*60){
                if(destroy_frame_counter == (explo_big_dur*0)+1 ||
                   destroy_frame_counter == (explo_big_dur*3)+1 ||
                   destroy_frame_counter == (explo_big_dur*6)+1){  
                    explosion_big.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+13, sprite_pivot.y()-14));
                }
                if( destroy_frame_counter == (explo_dur*0)+1 ||
                    destroy_frame_counter == (explo_dur*3)+1 ||
                    destroy_frame_counter == (explo_dur*6)+1 ||
                    destroy_frame_counter == (explo_dur*9)+1 ||
                    destroy_frame_counter == (explo_dur*12)+1)
                {
                    explosion.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()-13, sprite_pivot.y()-14));
                    explosion2.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+6, sprite_pivot.y()+6), false);
                    explosion3.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+32, sprite_pivot.y()+22), false);
                }
                if(destroy_frame_counter == (explo_dur*1)+1 ||
                   destroy_frame_counter == (explo_dur*4)+1 ||
                    destroy_frame_counter == (explo_dur*7)+1 ||
                    destroy_frame_counter == (explo_dur*10)+1 ||
                    destroy_frame_counter == (explo_dur*13)+1){  
                    explosion.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+8, sprite_pivot.y()));
                    explosion2.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+32, sprite_pivot.y()-8), false);
                    explosion3.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()-8, sprite_pivot.y()+20), false);
                }
                if( destroy_frame_counter == (explo_dur*2)+1 ||
                    destroy_frame_counter == (explo_dur*5)+1 ||
                    destroy_frame_counter == (explo_dur*8)+1 ||
                    destroy_frame_counter == (explo_dur*11)+1 ||
                    destroy_frame_counter == (explo_dur*14)+1)
                {
                    explosion.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()-32, sprite_pivot.y()+6));
                    explosion2.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+28, sprite_pivot.y()-24), false);
                    explosion3.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+44, sprite_pivot.y()+26), false);
                }
                if(destroy_frame_counter == (explo_big_dur*1)+1 ||
                   destroy_frame_counter == (explo_big_dur*4)+1 ||
                   destroy_frame_counter == (explo_big_dur*7)+1){ 
                    explosion_big.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()-27, sprite_pivot.y()+20));
                }
                if(destroy_frame_counter == (explo_big_dur*2)+1 ||
                   destroy_frame_counter == (explo_big_dur*5)+1 ||
                   destroy_frame_counter == (explo_big_dur*8)+1){ 
                    explosion_big.init_explosion(_pos+bn::fixed_point(sprite_pivot.x()+13, sprite_pivot.y()+20));
                }
                explosion_big.update();
                explosion.update();
                explosion2.update();
                explosion3.update();
            }

            //faça uma ultima coisa e elimine o boss
            else{
                BN_LOG("chama transição de Tela de vitória!");
                dead = true;
            }
        }
        
    };
} // namespace adonai
