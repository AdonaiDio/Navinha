#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

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

    void Shot_Player::Move_Forward()
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

    bool Shot_Player::check_collision()
    {
        //ATUALIZAR COLLISION
        _col = bn::rect( (int)_pos.x(), (int)_pos.y(),
                        4, 1 );
        //BN_LOG("CHECK COLLISION");
        for (int i = 0; i < ntt_enemies.size(); i++)
        {
            //BN_LOG("enemies: ", ntt_enemies.size());
            if ( _col.intersects(ntt_enemies.at(i)->col()))
            {
                //BN_LOG("Colidiu com o inimigo!");
                ntt_enemies.at(i)->receive_hit(i);
                return true;
                break;
            }            
        }
        return false;
    }
}