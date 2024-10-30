#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

#include "utility.h"

#include "player.h"

#include "new_shot_enemy.h"


namespace adonai
{

    // extern bn::array<New_Shot_Enemy*, 40> ntt_shots;

    New_Shot_Enemy::New_Shot_Enemy()//const bn::fixed_point& initial_position)
    {
        // _state = Shot_State::NONE; //caiu em desuso se o available funcionar
        _available = true;
        //_sprite.set_visible(false);
    }
    New_Shot_Enemy::~New_Shot_Enemy() {
        // for (int i = 0; i < ntt_shots.size(); i++)
        // {
        //     if(ntt_shots.at(i) == this){
        //         ntt_shots.erase(ntt_shots.begin()+i);
        //         BN_LOG("Destroy Shot! ntt_shots size: ", ntt_shots.size());
        //         break;
        //     }
        // }
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void New_Shot_Enemy::move_forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos = bn::fixed_point(((-bn::display::width()/2)-8),0);
            // _sprite.set_position(_pos);
            // _state = Shot_State::NONE;
            _available = true;
            // this->~New_Shot_Enemy();
            return;
        }

        // Se o valor da direção pre-definida estiver zerado, 
        // então atirar para frente
        // caso esteja diferente de {0,0},
        // então mudar _pos com base na direção pre-definida
        if(pre_direction == bn::fixed_point{0,0}){
            //incrementa a posição em X do shoot
            _pos = _pos + bn::fixed_point( bn::fixed(-velocity), 0);
        }
        else{
            //Mudar a posição em X e Y do shoot basiado na direção
            bn::fixed_point new_pos = pre_direction + _pos;
            _pos = move_towards_direction(_pos, new_pos, velocity);
        }

        //corrigir a posição do sprite em relação a posição 'pos' dele
        // _sprite.set_position(_pos);
        // BN_LOG("shot pos: ",_pos.x(),",",_pos.y());

        // ao chegar no fim da tela a esquerda, volta a ser NONE
        if(_pos.x() < (-bn::display::width()/2)-4)
        {
            // _state = Shot_State::NONE;
            _available = true;
            // this->~New_Shot_Enemy();
        }
    }

#pragma region Codigo depreciado!!
    void New_Shot_Enemy::move_forward(bn::fixed_point point_direction)
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos = bn::fixed_point(((-bn::display::width()/2)-8),0);
            // _sprite.set_position(_pos);
            // _state = Shot_State::NONE;
            _available = true;
            return;
        }
        
        //Mudar a posição em X e Y do shoot basiado na direção
        _pos = move_towards_direction(_pos, point_direction, velocity);
        //corrigir a posição do sprite em relação a posição 'pos' dele
        // _sprite.set_position(_pos);

        // ao chegar no fim da tela a esquerda, volta a ser NONE
        if(_pos.x() < (-1 * bn::display::width()/2)-4)
        {
            // _state = Shot_State::NONE;
            _available = true;
            // this->~New_Shot_Enemy();
        }
    }
#pragma endregion


    bool New_Shot_Enemy::check_collision()
    {
        //ATUALIZAR COLLISION
        _col = bn::rect( (int)_pos.x(), (int)_pos.y(),
                        4, 1 );
        //BN_LOG("CHECK COLLISION");
        if ( _col.intersects(GLOBALS::global_player->col()))
        {
            //BN_LOG("Colidiu com o player!");
            // _state = Shot_State::NONE;
            _available = true;
            // _sprite.set_visible(false);
            GLOBALS::global_player->receive_hit();
            return true;
        }            
        return false;
    }
    void New_Shot_Enemy::update()
    {
        if(_available == true){return;}
        move_forward();
        //se tiver que piscar imagem ou algo que aconteça com o passar do tempo deve ser executado aqui.
    }
}
