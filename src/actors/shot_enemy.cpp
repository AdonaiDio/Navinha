#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

#include "utility.h"

#include "player.h"

#include "shot_enemy.h"


namespace adonai
{

    extern bn::array<Shot_Enemy*, 40> ntt_shots;

    Shot_Enemy::Shot_Enemy( const bn::sprite_item& sprite_item ) :
        Shot( sprite_item, {0,0} ),
        _sprite_item(sprite_item)
    {
        // _available = true;
    }
    Shot_Enemy::Shot_Enemy(const Shot_Enemy &shot, const bn::fixed_point &initial_position) :
        Shot( shot._sprite_item, initial_position, shot._col, shot.velocity ),
        _sprite_item(shot._sprite_item),
        ntt_shots(shot.ntt_shots)
    {
        // _available = true;
    }
    Shot_Enemy::~Shot_Enemy()
    {
        for (int i = 0; i < ntt_shots->size(); i++) {
            if(ntt_shots->at(i) == this) {
                ntt_shots->erase(ntt_shots->begin()+i);
                // BN_LOG("Destroy Shot! ntt_shots size: ", ntt_shots->size());
                break;
            }
        }
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void Shot_Enemy::move_forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            _pos = bn::fixed_point(((-bn::display::width()/2)-8),0);
            _sprite.set_position(_pos);
            // _available = true;
            this->~Shot_Enemy();
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
        sprite().set_position(_pos);
        // BN_LOG("shot pos: ",_pos.x(),",",_pos.y());

        // Ao sair da tela, volta a ser NONE / available / é destruído
        if (is_out_of_screen()) {
            // _available = true;
            this->~Shot_Enemy();
        }
    }

    bool Shot_Enemy::is_out_of_screen() {
        if(_pos.x() < (-bn::display::width() / 2) - 8){
            return true;
        }
        else if(_pos.x() > (bn::display::width() / 2) + 8){
            return true;
        }
        else if(_pos.y() < (-bn::display::height() / 2) - 8){
            return true;
        }
        else if(_pos.y() > (bn::display::height() / 2) + 8){
            return true;
        }
        return false;
    }


    bool Shot_Enemy::check_collision() {
        //ATUALIZAR COLLISION
        col_position({(int)_pos.x(), (int)_pos.y()});
        // BN_LOG("shot col: x",col().x(),",y",col().y(),",w",col().width(),",h",col().height());
        // BN_LOG("player col: x",GLOBALS::global_player->col().x(),",y",GLOBALS::global_player->col().y(),",w",GLOBALS::global_player->col().width(),",h",GLOBALS::global_player->col().height());
        if ( _col.intersects(GLOBALS::global_player->col()))
        {
            BN_LOG("player -> shot enemy");
            // _available = true;
            GLOBALS::global_player->receive_hit();
            return true;
        }            
        return false;
    }
    void Shot_Enemy::update()
    {
        // if(_available == true){return;}
        move_forward();
        //se tiver que piscar imagem ou algo que aconteça com o passar do tempo deve ser executado aqui.
    }
}
