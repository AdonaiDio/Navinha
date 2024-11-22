#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

#include "utility.h"

#include "enemy.h"

#include "shot_player.h"

namespace adonai
{
    
    Shot_Player::Shot_Player(   
            const bn::sprite_item& sprite_item, 
            const bn::fixed_point& initial_position)
        :Shot(sprite_item,
            initial_position),
        _sprite(sprite_item.create_sprite(bn::fixed_point(bn::display::width()+8,0)))
    {
        _state = Shot_State::NONE;
        _sprite.set_visible(false);
    }
    Shot_Player::~Shot_Player(){}

    void Shot_Player::move_forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos.set_x((bn::display::width()/2)+4);
            _sprite.set_position(_pos);
            _state = Shot_State::NONE;
            return;
        }
        
        //incrementa a posição em X do shoot
        _pos = _pos + bn::fixed_point( bn::fixed(1 * velocity), 0);
        //corrigir a posição do sprite em relação a posição 'pos' dele
        _sprite.set_position(_pos);

        // ao chegar no fim da tela a direita, volta a ser NONE
        if(_sprite.position().x() > (bn::display::width()/2)+4)
        {
            _state = Shot_State::NONE;
        }
    }

    // void Shot_Player::move_forward(bn::fixed_point point_direction)
    // {
    //     //não mover se colidir
    //     if(check_collision()){
    //         //se colidir resetar estado do tiro
    //         _pos = bn::fixed_point(((-1 * bn::display::width()/2)-8),0);
    //         _sprite.set_position(_pos);
    //         _state = Shot_State::NONE;
    //         return;
    //     }
        
    //     //Mudar a posição em X e Y do shoot basiado na direção
    //     _pos = move_towards_direction(_pos, point_direction, velocity);
    //     //corrigir a posição do sprite em relação a posição 'pos' dele
    //     _sprite.set_position(_pos);

    //     // ao chegar no fim da tela a esquerda, volta a ser NONE
    //     if(_sprite.position().x() < (-1 * bn::display::width()/2)-4)
    //     {
    //         _state = Shot_State::NONE;
    //         this->~Shot_Player();
    //     }
    // };
    
    bool Shot_Player::check_collision()
    {
        //ATUALIZAR COLLISION POSITION
        _col.set_position( (int)_pos.x(), (int)_pos.y() );
        for (int i = 0; i < ntt_enemies->size(); i++)
        {
            // BN_LOG("enemies: ", ntt_enemies->size());
            if ( _col.intersects(ntt_enemies->at(i)->col()))
            {
                BN_LOG("Colidiu com o inimigo!");
                ntt_enemies->at(i)->receive_hit();
                return true;
                break;
            }            
        }
        return false;
    }
}
