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


        _player._movement_states = adonai::Player_States::Player_NONE;
        if (bn::keypad::up_held())
        {
            _player.pos( move_towards( _player.pos(), 
                                    _player.pos() + bn::fixed_point(0, -1*_player.velocity()), 
                                    _player.velocity() ) );
            _player._movement_states = adonai::Player_States::Player_NONE;

            if (bn::keypad::left_held())
            {
                _player._movement_states = adonai::Player_States::Player_HOLD_MOVE_LEFT;
            }
        }
        if (bn::keypad::down_held())
        {
            _player.pos( move_towards( _player.pos(), 
                                    _player.pos() + bn::fixed_point(0, 1*_player.velocity()), 
                                    _player.velocity() ) );
            _player._movement_states = adonai::Player_States::Player_NONE;
            
            if (bn::keypad::left_held())
            {
                _player._movement_states = adonai::Player_States::Player_HOLD_MOVE_LEFT;
            }
        }


        if (bn::keypad::right_held())
        {
            _player.pos( move_towards( _player.pos(), 
                                    _player.pos() + bn::fixed_point(1*_player.velocity(), 0), 
                                    _player.velocity() ) );

            _player._movement_states = adonai::Player_States::Player_HOLD_MOVE_RIGHT;
        }
        else if (bn::keypad::left_held())
        {
            _player.pos( move_towards( _player.pos(), 
                                    _player.pos() + bn::fixed_point(-1*_player.velocity(), 0), 
                                    _player.velocity() ) );
            _player._movement_states = adonai::Player_States::Player_HOLD_MOVE_LEFT;
        }
        
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
            
            switch (_player._movement_states)
            {
            case 0:
                BN_LOG("Player STATE: NONE");
                break;
            case 2:
                BN_LOG("Player STATE: HOLD_MOVE_RIGHT");
                break;
            case 4:
                BN_LOG("Player STATE: HOLD_MOVE_LEFT");
                break;
            default:
                break;
            }
            //BN_LOG("Player STATE: ", _player._movement_states);
            
            if (_player._movement_states == adonai::Player_States::Player_NONE) //parou
            {
                _player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(0));
                _player.propulsion_hold_anim = 
                    bn::create_sprite_animate_action_forever(
                        _player.propulsion_sprite(), 
                        15, 
                        bn::sprite_items::propulsion.tiles_item(), 
                        8,8,8
                    );
                _player.moved_to_left = 0;
            }
            else if (_player._movement_states == adonai::Player_States::Player_HOLD_MOVE_RIGHT)
            {
                _player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(1));
                _player.propulsion_hold_anim = 
                    bn::create_sprite_animate_action_forever(
                        _player.propulsion_sprite(), 
                        15, 
                        bn::sprite_items::propulsion.tiles_item(), 
                        5,6,7
                    );
                _player.moved_to_left = 0;
            }
            else if (_player._movement_states == adonai::Player_States::Player_HOLD_MOVE_LEFT) //start left
            {
                _player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(0));
                _player.propulsion_hold_anim = 
                    bn::create_sprite_animate_action_forever(
                        _player.propulsion_sprite(), 
                        15, 
                        bn::sprite_items::propulsion.tiles_item(), 
                        8,8,8
                    );
                _player.moved_to_left = 0;
            }
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

        // FIXME: AO COMEÇAR O TIRO, CADA TIRO DEVE CUIDAR DO MOVIMENTO 
        // INDEPENDENTEMENTE.
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
