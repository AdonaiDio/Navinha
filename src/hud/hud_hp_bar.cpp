
#include "bn_display.h"
#include "bn_sprite_items_hud_hp.h"

#include "bn_log.h"

#include "player.h"

#include "hud_hp_bar.h"


namespace adonai
{
    hud_hp_bar::hud_hp_bar(adonai::Player& player) :
    _player(player),
    hp_bar_sprites({
        bn::sprite_items::hud_hp.create_sprite( (-bn::display::width()/2) + 4 + 4 //set initial x pos
                                                + (8*0),//offset em x
                                                -(bn::display::height()/2) + (4+5), //set initial y pos
                                                adonai::Graphics::LEFT_BAR_INDEX),
        bn::sprite_items::hud_hp.create_sprite( (-bn::display::width()/2) + 8  //set initial x pos
                                                + (8*1),//offset em x
                                                -(bn::display::height()/2) + 9, //set initial y pos
                                                adonai::Graphics::HP_BAR_QTY_4_INDEX),
        bn::sprite_items::hud_hp.create_sprite( (-bn::display::width()/2) + 8 //set initial x pos
                                                + (8*2),//offset em x
                                                -(bn::display::height()/2) + 9, //set initial y pos
                                                adonai::Graphics::RIGHT_BAR_INDEX)
    })
    { 
        hp_bar_sprites.at(0).set_bg_priority(1); 
        hp_bar_sprites.at(1).set_bg_priority(1); 
        hp_bar_sprites.at(2).set_bg_priority(1); 
    }
    hud_hp_bar::~hud_hp_bar(){}

    void hud_hp_bar::counter_handler()
    {
        int hp = _player.hp();
        // if ( hp <= 4 )
        // {
        switch (hp)
        {
            case 0:
                // este sprite
                hp_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_hp.tiles_item().create_tiles(
                        adonai::Graphics::HP_BAR_QTY_0_INDEX
                    )
                );
                break;
            
            case 1:
                hp_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_hp.tiles_item().create_tiles(
                        adonai::Graphics::HP_BAR_QTY_1_INDEX
                    )
                );
                break;
            
            case 2:
                hp_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_hp.tiles_item().create_tiles(
                        adonai::Graphics::HP_BAR_QTY_2_INDEX
                    )
                );
                break;
            
            case 3:
                hp_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_hp.tiles_item().create_tiles(
                        adonai::Graphics::HP_BAR_QTY_3_INDEX
                    )
                );
                break;
            
            default: //4
                hp_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_hp.tiles_item().create_tiles(
                        adonai::Graphics::HP_BAR_QTY_4_INDEX
                    )
                );
                break;
        }
        // }

    }

    void hud_hp_bar::update()
    {
        counter_handler();
    }
}
