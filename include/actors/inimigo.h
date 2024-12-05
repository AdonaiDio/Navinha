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
            
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );

            int _hp = 1;
            bn::fixed _velocity = 1;

            //--- inimigo exclusivo ---
            New_Shot_Enemy _shot = New_Shot_Enemy(bn::sprite_items::shoot);
            // New_Shot_Enemy _shot; // !!! testar usar optional !!!

            // extras
            Explosion_FX* explosion;
            Hit_FX* hit_fx;
            bool is_hitting = false;
            // < Index do Ultimo Sprite Atualizado >
            // usado para mudar a posição do sprite compartilhado dos shots
            // int _last_spr_shot_updated_index = 0; 
            
            
        public:
            bn::vector<Inimigo*, 20>* ntt_enemies;//referencia da lista de ntts
            bool has_shot = false; //indicativo de que o _shot foi iniciado.
            bn::vector<New_Shot_Enemy*, 40>* ntt_shots; 

            bool wait_to_destroy = false;

            E_Enemy_State _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
            E_Shot_Type _shot_type = E_Shot_Type::E_Shot_Type_1;

            Inimigo(bn::vector<Inimigo*, 20>* ntt_e,
                    bn::fixed_point position,
                    bn::sprite_item sprite_item, 
                    int max_hp);
            Inimigo(bn::vector<Inimigo*, 20>* ntt_e,
                    bn::fixed_point position,
                    bn::sprite_item sprite_item, 
                    int max_hp, 
                    bn::sprite_item shot_sprite_item, 
                    E_Shot_Type shot_type );
            ~Inimigo();

            bn::fixed_point pos()                   { return _pos; }
            void pos(bn::fixed_point position)  { _pos = position; }
            void pos(bn::fixed x, bn::fixed y)  { _pos = bn::fixed_point(x,y); }
            void pos_x(bn::fixed x)  { _pos = bn::fixed_point(x, _pos.y()); }
            void pos_y(bn::fixed y)  { _pos = bn::fixed_point(_pos.x(), y); }
            bn::rect col()                          { return _col; }
            void col(bn::rect new_value)                { _col = new_value; }

            bn::sprite_ptr sprite()              { return _sprite; }
            void sprite(bn::sprite_ptr sprite)              { _sprite = sprite; }

            int hp()                                 { return _hp; }
            void hp(int new_value)              { _hp = new_value; }
            bn::fixed velocity()               { return _velocity; }
            void velocity(bn::fixed new_vel){ _velocity = new_vel; }

            // lugar para guardar os scripts associados ao enemy
            // bn::vector<I_Script<Inimigo>*, 12> _scripts; //não vou usar script nesse teste
            // void add_script(I_Script<Inimigo>& script);
            // void remove_script(I_Script<Inimigo>& script);

            void assign_ntt_shots(bn::vector<New_Shot_Enemy*, 40>* ntt_shots_ptr){
                ntt_shots = ntt_shots_ptr;
                _shot.ntt_shots = ntt_shots_ptr;
            }

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
            void damaged() {
                if (bn::keypad::a_pressed())
                {
                    BN_LOG("DAMAGED");
                    receive_hit();
                }
            }
            void shooting() {
                if (bn::keypad::r_pressed())
                {
                    BN_LOG("ATIROU");
                    shoot();
                }
            }
            //

            void receive_hit();

            void explode() {
                _sprite.set_visible(false);
                // explosion.init_explosion(_pos);
                BN_LOG("explosion Usados: ", bn::sprites::used_items_count());
                BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
                BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
            };

            void just_delete_this();

            void shoot();
            //retorna true se puder atirar, além de atualizar a lista de disponibilidade dos tiros.
            bool can_shoot();
            void shot_type_1();
            void shot_type_2();
            void shot_type_3();

            void update_collider();
            // void update_scripts();
            void update();

            bool can_update();
    };
}