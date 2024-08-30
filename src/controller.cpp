#include "player.h"
#include "bn_keypad.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_display.h"
#include "bn_log.h"
#include "bn_sound_items.h"

#include "utility.h"

//temp
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_propulsion.h"

#include "controller.h"

namespace adonai
{
    Controller::Controller(adonai::Player &player) :
    _player(player)
    {}

    void Controller::InputAction_Move()
    {
        adonai::Player_States old_player_state = _player._movement_states;

        int _vx = 0, _vy = 0;

        if (bn::keypad::up_held() && bn::keypad::right_held())          { _vx = 1;  _vy =  -1; }
        else if (bn::keypad::down_held() && bn::keypad::left_held())    { _vx = -1;  _vy =  1; }
        else if (bn::keypad::left_held() && bn::keypad::up_held())     { _vx = -1;  _vy =  -1; }
        else if (bn::keypad::right_held() && bn::keypad::down_held())    { _vx = 1;  _vy =  1; }
        else if (bn::keypad::up_held())                                           { _vy =  -1; }
        else if (bn::keypad::right_held())                                          { _vx = 1; }
        else if (bn::keypad::down_held())                                          { _vy =  1; }
        else if (bn::keypad::left_held())                                          { _vx = -1; }

        _player.pos( move_towards( _player.pos(), 
                                _player.pos() + bn::fixed_point(_vx*_player.velocity(), _vy*_player.velocity()), 
                                _player.velocity() ) );

        _player._movement_states = 
            _vx==0? adonai::Player_States::Player_NONE : 
                    _vx>0?  adonai::Player_States::Player_HOLD_MOVE_RIGHT : 
                            adonai::Player_States::Player_HOLD_MOVE_LEFT ;
        
        // clamp em X
        const bn::fixed _x = bn::clamp(_player.pos().x(), 
                    (bn::fixed)-(bn::display::width()/2), 
                    (bn::fixed)(bn::display::width()/2));
        // clamp em Y
        const bn::fixed _y = bn::clamp(_player.pos().y(), 
                    (bn::fixed)-(bn::display::height()/2), 
                    (bn::fixed)(bn::display::height()/2));

        _player.pos(bn::fixed_point(_x, _y));
        
        //SE ESTADO MUDOU ENTÃO TRATAR ANIMAÇÃO
        if(old_player_state != _player._movement_states)
        {
            //index do sprite e frames de animações
            int spr_i, gr_1, gr_2, gr_3;

            switch (_player._movement_states) {
                case adonai::Player_States::Player_HOLD_MOVE_RIGHT:
                    spr_i = 1;
                    gr_1 = 5; gr_2 = 6; gr_3 = 7;
                    break;
                
                case adonai::Player_States::Player_HOLD_MOVE_LEFT:
                    spr_i = 0;
                    gr_1 = 8; gr_2 = 8; gr_3 = 8;
                    break;
                
                default:
                    spr_i = 0;
                    gr_1 = 8; gr_2 = 8; gr_3 = 8;
                    break;
            }
            
            _player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(spr_i));
            _player.propulsion_hold_anim = 
                bn::create_sprite_animate_action_forever(
                    _player.propulsion_sprite(), 
                    15, 
                    bn::sprite_items::propulsion.tiles_item(), 
                    gr_1,gr_2,gr_3
                );
            _player.moved_to_left = 0;
        }
        if( old_player_state == _player._movement_states && 
            old_player_state == adonai::Player_States::Player_HOLD_MOVE_LEFT)
        {
            _player.moved_to_left += _player.velocity();
        }
        _player.propulsion_hold_anim.update();
    }

    // se começa movimento para esquerda, então reseta a posição do shadow blue para o player.x()+1 e visibilidade true
    // Se segurando para esquerda e shadow blue estiver 8+1px de distancia em x, então ativar shadow green
    // se segurando para esquerda e shadow blue estiver a 16+1px (e shadow green 8+1px), ativar shadow red
    // se segurando esquerda, shadow blue clamp max 24px, green clamp max 16px e red clamp max 8px.
    // se soltar esquerda, todos os visiveis vão transladar até o player e desaparecer

    void Controller::InputAction_Shoot()
    {
        if (bn::keypad::b_pressed())
        {
            // usar um shoot do player que não está no estado de shooting
            // se não houver shoot no estado none, então não atira.
            for(int i=0; i<_player._shots.max_size(); i++)
            {
                if(_player._shots[i]._state == adonai::Shot_State::NONE)
                {
                    //reseta a posição e muda o estado para shooting
                    _player._shots[i].pos(bn::fixed_point(_player.pos().x() +3, _player.pos().y() +4));
                    _player._shots[i].sprite().set_visible(true);
                    _player._shots[i]._state = adonai::Shot_State::SHOOTING;
                    //BN_LOG("shoot index: ",i," x:", _player._shoots[i].pos().x(), " y:", _player._shoots[i].pos().y());
                    
                    bn::sound_items::laser.play();
                    return;
                }
            }
        }
        // percorre todos os shoots e e move_forward apenas os com state SHOOTING
        for(int i=0; i<_player._shots.max_size(); i++)
        {
            if(_player._shots[i]._state == adonai::Shot_State::SHOOTING)
            {
                _player._shots[i].Move_Forward();
            }
        }
    };

    void Controller::update()
    {
        if(_player.can_act){
            InputAction_Move();
            InputAction_Shoot();
        }
    }
}
