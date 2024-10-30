#pragma once

#include "bn_log.h"

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_rect.h"
#include "bn_sprite_ptr.h"
#include <bn_sprite_palette_ptr.h>
#include "bn_colors.h"
#include "bn_sound_items.h"
#include <bn_optional.h>

#include "bn_sprite_palette_items_feedback_palette.h"

#include "explosion_fx.h"
#include "hit_fx.h"

#include "bn_vector.h"
#include "bn_sprite_animate_actions.h"

#include "new_shot_enemy.h"

#include "i_script.hpp"

#include "bn_sprite_items_shoot.h"
#include "bn_sprite_items_spaceship_1.h"
#include "bn_sprite_items_spaceship_2.h"

#define MAX_FRAMES_ANIM 10
#define MAX_ENEMY_SHOTS 12

#include "enemy.h"
#include "bn_keypad.h"

namespace adonai
{  
    namespace GLOBALS
    {
        extern Player* global_player;
    }
    // extern bn::vector<Enemy*, 20> ntt_enemies; 

    class Inimigo {
        private:
            bn::sprite_ptr _sprite;
            bn::sprite_item _sprite_item; //para usar o frame correto no hit_feedback
            // sprite compartilhado entre todos os shots deste enemy
            bn::sprite_ptr _sprite_shot;
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );

            int _hp;
            bn::fixed _velocity = 1;

            // extras
            Explosion_FX* explosion;
            Hit_FX* hit_fx;
            bool is_hitting = false;
            int _sprite_shot_index = -1; //usado para mudar a posição do sprite compartilhado dos shots
            
        protected:
        
        public:
            //bn::vector<Inimigo*, 20>* ntt_enemies;//referencia da lista de ntts

            Inimigo(bn::fixed_point position = bn::fixed_point(0,0), 
                    bn::sprite_item sprite_item = bn::sprite_items::spaceship_2, 
                    bn::sprite_item shot_sprite_item = bn::sprite_items::shoot, 
                    E_Shot_Type shot_type = E_Shot_Type::E_Shot_Type_1, 
                    int max_hp = 3);
            ~Inimigo();

            bn::fixed_point pos()                   { return _pos; }
            void pos(bn::fixed_point position)  { _pos = position; }
            void pos_x(bn::fixed x)  { _pos = bn::fixed_point(x, _pos.y()); }
            void pos_y(bn::fixed y)  { _pos = bn::fixed_point(_pos.x(), y); }
            bn::rect col()                          { return _col; }
            void col(bn::rect new_value)                { _col = new_value; }

            bn::sprite_ptr sprite()              { return _sprite; }

            int hp()                                 { return _hp; }
            void hp(int new_value)              { _hp = new_value; }
            bn::fixed velocity()               { return _velocity; }
            void velocity(bn::fixed new_vel){ _velocity = new_vel; }

            // lugar para guardar os scripts associados ao enemy
            // bn::vector<I_Script<Inimigo>*, 12> _scripts; //não vou usar script nesse teste
            // void add_script(I_Script<Inimigo>& script);
            // void remove_script(I_Script<Inimigo>& script);

            bool wait_to_destroy = false;

            E_Enemy_State _enemy_state = E_Enemy_State::E_Enemy_State_NONE;

            // bn::sprite_item _shot_sprite_item;

            bn::array<New_Shot_Enemy, MAX_ENEMY_SHOTS> _shots;
            //true se shot tiver disponível
            bn::array<bool*, MAX_ENEMY_SHOTS> _shots_is_available;
            E_Shot_Type _shot_type = E_Shot_Type::E_Shot_Type_1;


            //_cols é uma lista de colliders 1 para cada frame do spritesheet
            bn::array<bn::rect, MAX_FRAMES_ANIM> _cols;

            bn::sprite_animate_action<MAX_FRAMES_ANIM> enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    0,
                    bn::sprite_items::spaceship_2.tiles_item(),
                    0,0
            );
            
            //--methods--
            void hit_feedback(){
                is_hitting = true;
                hit_fx = new Hit_FX(_pos, _sprite_item, enemy_anim.current_graphics_index(), is_hitting);
                BN_LOG("is hitting: ", is_hitting);
            BN_LOG("hitFX Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            }

            // experimental -- para autodestruição de todos os inimigos
            void damaged(){
                if (bn::keypad::a_pressed())
                {
                    BN_LOG("DAMAGED");
                    receive_hit();
                }
            }
            void shooting(){
                if (bn::keypad::r_pressed())
                {
                    BN_LOG("ATIROU");
                    shoot();
                }
            }
            //

            void receive_hit();

            void explode()
            {
                _sprite.set_visible(false);
                explosion = new Explosion_FX(_pos);
            BN_LOG("explosion Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            };

            void hit_feedback_update();

            void just_delete_this();

            void shoot();
            bool can_shoot();//retorna true se puder atirar, além de atualizar a lista de disponibilidade dos tiros.
            void shot_type_1();
            void shot_type_2();
            void shot_type_3();
            void update_all_shots_occupied();
            bool all_shots_available();
            void update_shared_sprite_shot_position();

            void update_collider();
            // void update_scripts();
            void update();


            bool can_update();
    };
}