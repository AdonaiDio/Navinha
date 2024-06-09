#include "player.h"
#include "bn_keypad.h"
#include "bn_sprite_actions.h"

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
        }
        player.update_sprite_position(player);
    };
}
