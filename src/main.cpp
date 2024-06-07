#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"

#include "bn_sprite_actions.h"

#include "bn_sprite_items_nova.h"

int main()
{
    bn::core::init();
    
    const bn::sprite_ptr nave = bn::sprite_items::nova.create_sprite(0, 0);
    const bn::sprite_ptr nave_sprite = bn::sprite_items::nova.create_sprite(0, 0);

    const bn::fixed_point amplitude_pos = bn::fixed_point(0, 2);

    while(true)
    {
        if (bn::keypad::up_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 0, -1);
            bn::sprite_move_by_action nave_action_moveBy2( nave, 0, -1);
            nave_action_moveBy.update();
            nave_action_moveBy2.update();
        }
        else if (bn::keypad::down_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 0, 1);
            bn::sprite_move_by_action nave_action_moveBy2( nave, 0, 1);
            nave_action_moveBy.update();
            nave_action_moveBy2.update();
        }

        if (bn::keypad::left_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, -1, 0);
            bn::sprite_move_by_action nave_action_moveBy2( nave, -1, 0);
            nave_action_moveBy.update();
            nave_action_moveBy2.update();
        }
        else if (bn::keypad::right_held())
        {
            bn::sprite_move_by_action nave_action_moveBy( nave_sprite, 1, 0 );
            bn::sprite_move_by_action nave_action_moveBy2( nave, 1, 0 );
            nave_action_moveBy.update();
            nave_action_moveBy2.update();
            
        }
        
        bn::sprite_move_loop_action nave_action_hover(nave_sprite, 30, nave.position() + amplitude_pos);
        nave_action_hover.update();

        bn::core::update();
    }
}
