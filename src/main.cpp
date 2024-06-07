#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"

#include "bn_log.h"

#include "bn_sprite_actions.h"

#include "bn_sprite_items_nova.h"

#include "player.h"

int main()
{
    bn::core::init();

    bn::sprite_ptr nave_sprite = bn::sprite_items::nova.create_sprite(0, 0);
    adonai::Player player = adonai::Player(nave_sprite);

    const bn::fixed_point amplitude_pos = bn::fixed_point(0, 2);

    while(true)
    {
        
        nave_sprite.set_position(player.pos());

        if (bn::keypad::up_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 0, -1);
            nave_action_moveBy.update();

            player.spawn(nave_sprite.position());
        }
        else if (bn::keypad::down_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 0, 1);
            nave_action_moveBy.update();

            player.spawn(nave_sprite.position());
        }

        if (bn::keypad::left_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, -1, 0);
            nave_action_moveBy.update();

            player.spawn(nave_sprite.position());
        }
        else if (bn::keypad::right_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 1, 0 );
            nave_action_moveBy.update();

            player.spawn(nave_sprite.position());
        }
        
        bn::sprite_move_loop_action nave_action_hover(nave_sprite, 30, player.pos() + amplitude_pos);
        nave_action_hover.update();

        BN_LOG("x: ", player.pos().x(), " y: ", player.pos().y());
        bn::core::update();
    }
}
