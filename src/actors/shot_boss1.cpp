#include "bn_log.h"
#include "bn_display.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

#include "utility.h"

#include "player.h"

#include "shot_boss1.h"


namespace adonai
{

    extern bn::array<Shot_Boss1, 40> ntt_shots;

    Shot_Boss1::Shot_Boss1(bn::fixed_point pos) :
        Shot( bn::sprite_items::shot_4, pos ),
        _sprite_item(bn::sprite_items::shot_4)
    {
        _sprite.set_visible(false);
        _available = true;
    }
    // muda as infos do shot para as mesmas de outro passado por parametro.
    void Shot_Boss1::copy_Shot_Boss1(const Shot_Boss1& shot)
    {
        copy_Shot(shot);
        _sprite = shot._sprite_item.create_sprite(_pos);
        _sprite_item = shot._sprite_item;
        shot_anim = bn::create_sprite_animate_action_forever (
            _sprite,
            8,
            bn::sprite_items::shot_4.tiles_item(),
            0,1,2
        );
    }

    // o valor do owner_pos_y deve ser criado ao disparar o tiro
    void Shot_Boss1::move_forward()
    {
        //não mover se colidir
        if(check_collision()){
            //se colidir resetar estado do tiro
            BN_LOG("player -> shot enemy");
            GLOBALS::global_player->receive_hit();
            reset_shot();
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
            reset_shot();
        }
    }

    bool Shot_Boss1::is_out_of_screen() {
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


    bool Shot_Boss1::check_collision() {
        //ATUALIZAR COLLISION
        col_position({(int)_pos.x(), (int)_pos.y()});
        // BN_LOG("shot col: x",col().x(),",y",col().y(),",w",col().width(),",h",col().height());
        // BN_LOG("player col: x",GLOBALS::global_player->col().x(),",y",GLOBALS::global_player->col().y(),",w",GLOBALS::global_player->col().width(),",h",GLOBALS::global_player->col().height());
        if ( _col.intersects(GLOBALS::global_player->col()))
        {
            return true;
        }            
        return false;
    }

    void Shot_Boss1::reset_shot()
    {
        _available = true;
        _pos = bn::fixed_point(((-bn::display::width()/2)-8),0);
        sprite().set_position(_pos);
    }

    void Shot_Boss1::update()
    {
        if(_available == true){return;}
        move_forward();
        //se tiver que piscar imagem ou algo que aconteça com o passar do tempo deve ser executado aqui. vvv
        shot_anim.update();
    }
}
