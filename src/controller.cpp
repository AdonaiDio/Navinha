#include "player.h"
#include "bn_keypad.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_display.h"
#include "bn_log.h"


#include "controller.h"

namespace adonai
{
    Controller::Controller()
    {}

    void Controller::InputAction_Move(adonai::Player &player)
    {
        if (bn::keypad::up_held())
        {
            player.set_pos(player.pos() + bn::fixed_point(0, -1));
        }
        else if (bn::keypad::down_held())
        {
            player.set_pos(player.pos() + bn::fixed_point(0, 1));
        }

        if (bn::keypad::left_held())
        {
            player.set_pos(player.pos() + bn::fixed_point(-1, 0));
        }
        else if (bn::keypad::right_held())
        {
            player.set_pos(player.pos() + bn::fixed_point(1, 0));
            player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(1));
        }
        else if (bn::keypad::right_released())
        {
            player.sprite().set_tiles(bn::sprite_items::nova.tiles_item().create_tiles(0));
        }
        
        // clamp em X
        const bn::fixed _x = bn::clamp(player.pos().x(), 
                    (bn::fixed)-(bn::display::width()/2), 
                    (bn::fixed)(bn::display::width()/2));
        // clamp em Y
        const bn::fixed _y = bn::clamp(player.pos().y(), 
                    (bn::fixed)-(bn::display::height()/2), 
                    (bn::fixed)(bn::display::height()/2));

        player.set_pos(bn::fixed_point(_x, _y));

        player.update_sprite_position(player);
    }

    void Controller::InputAction_Shoot(adonai::Player &player)
    {
        if (bn::keypad::b_pressed())
        {
            // TODO: Instanciar o tiro/shoot

            
            // usar um shoot do player que não está no estado de shooting
            // se não houver shoot no estado none, então não atira.
            for(int i=0; i<player._shoots.max_size(); i++)
            {
                if(player._shoots[i]._state == adonai::Shoot_State::NONE)
                {
                    //reseta a posição e muda o estado para shooting
                    player._shoots[i].set_pos(bn::fixed_point(player.pos().x() +3, player.pos().y() +4));
                    player._shoots[i].sprite().set_visible(true);
                    player._shoots[i]._state = adonai::Shoot_State::SHOOTING;
                    BN_LOG("shoot index: ",i," x:", player._shoots[i].pos().x(), " y:", player._shoots[i].pos().y());
                    return;
                }
            }
        }
        // percorre todos os shoots e e move_forward apenas os com state SHOOTING

        // FIXME: NÃO POSSO ATUALIZAR A POSIÇÃO PELO CONTROLLER. Já QUE A CADA FRAME ELE VAI
        // PEGAR A POSIÇÃO ATUAL DO JOGADOR. AO COMEÇAR O TIRO, CADA TIRO DEVE CUIDAR DO MOVIMENTO 
        // INDEPENDENTEMENTE.
        for(int i=0; i<player._shoots.max_size(); i++)
        {
            if(player._shoots[i]._state == adonai::Shoot_State::SHOOTING)
            {
                player._shoots[i].Move_Forward();
            }
        }
        
    };
}
