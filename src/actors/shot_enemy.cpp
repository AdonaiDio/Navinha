#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

#include "player.h"

#include "shot_enemy.h"


namespace adonai
{

    extern bn::vector<Shot*, 30> ntt_shots;

    Shot_Enemy::Shot_Enemy(   
            const bn::sprite_item& sprite_item, 
            const bn::fixed_point& initial_position)
        :Shot(sprite_item,
            initial_position),
        _sprite(sprite_item.create_sprite(bn::fixed_point(bn::display::width()+8,0))),
        _sprite_item(sprite_item)
    {
        _state = Shot_State::NONE;
        _sprite.set_visible(false);
    }
    Shot_Enemy::~Shot_Enemy() {
        for (int i = 0; i < ntt_shots.size(); i++)
        {
            if(ntt_shots.at(i) == this){
                ntt_shots.erase(ntt_shots.begin()+i);
                BN_LOG("Destroy Shot! ntt_shots size: ", ntt_shots.size());
                break;
            }
        }
    }

    bn::sprite_item Shot_Enemy::sprite_item()
    {
        return _sprite_item;
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void Shot_Enemy::Move_Forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos = bn::fixed_point(((-1 * bn::display::width()/2)-8),0);
            _sprite.set_position(_pos);
            _state = Shot_State::NONE;
            return;
        }
        
        //incrementa a posição em X do shoot
        _pos = _pos + bn::fixed_point( bn::fixed(-1 * velocity), 0);
        //corrigir a posição do sprite em relação a posição 'pos' dele
        _sprite.set_position(_pos);

        // ao chegar no fim da tela a direita, volta a ser NONE
        if(_sprite.position().x() < (-1 * bn::display::width()/2)-4)
        {
            _state = Shot_State::NONE;
            this->~Shot_Enemy();
        }
    }

    bool Shot_Enemy::check_collision()
    {
        //ATUALIZAR COLLISION
        _col = bn::rect( (int)_pos.x(), (int)_pos.y(),
                        4, 1 );
        //BN_LOG("CHECK COLLISION");
        if ( _col.intersects(GLOBALS::global_player->col()))
        {
            //BN_LOG("Colidiu com o player!");
            GLOBALS::global_player->receive_hit();
            return true;
        }            
        return false;
    }
}
