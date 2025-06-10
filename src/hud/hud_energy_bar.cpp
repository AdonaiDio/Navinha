
#include "bn_display.h"
#include "bn_sprite_items_hud_energy.h"

#include "bn_log.h"

#include "player.h"

#include "hud_energy_bar.h"

namespace adonai
{
    hud_energy_bar::hud_energy_bar(adonai::Player& player) :
    _player(player),
    energy_bar_sprites({
        bn::sprite_items::hud_energy.create_sprite( (-bn::display::width()/2) + 8,
                                                    (bn::display::height()/2) - 8
                                        - (8*4),//offset em y
                                                    adonai::Graphics::TOP_BAR_INDEX),
        bn::sprite_items::hud_energy.create_sprite( (-bn::display::width()/2) + 8,
                                                    (bn::display::height()/2) - 8
                                        - (8*3),//offset em y
                                                    adonai::Graphics::ENERGY_BAR_QTY_4_INDEX),
        bn::sprite_items::hud_energy.create_sprite( (-bn::display::width()/2) + 8,
                                                    (bn::display::height()/2) - 8
                                        - (8*2),//offset em y
                                                    adonai::Graphics::ENERGY_BAR_QTY_4_INDEX),
        bn::sprite_items::hud_energy.create_sprite( (-bn::display::width()/2) + 8,
                                                    (bn::display::height()/2) - 8
                                        - (8*1),//offset em y
                                                    adonai::Graphics::ENERGY_BAR_QTY_4_INDEX),
        bn::sprite_items::hud_energy.create_sprite( (-bn::display::width()/2) + 8,
                                                    (bn::display::height()/2) - 8
                                        - (8*0),//offset em y
                                                    adonai::Graphics::BOTTOM_BAR_INDEX)
    })
    {
        energy_bar_sprites.at(0).set_bg_priority(1); 
        energy_bar_sprites.at(1).set_bg_priority(1); 
        energy_bar_sprites.at(2).set_bg_priority(1); 
        energy_bar_sprites.at(3).set_bg_priority(1); 
        energy_bar_sprites.at(4).set_bg_priority(1); 
    }
    hud_energy_bar::~hud_energy_bar(){}
    
    int hud_energy_bar::available_shoots(){
        int available_shoots = 0;
        for(int i=0; i<_player._shots.max_size(); i++)
        {
            if(_player._shots[i]._state == adonai::Shot_State::NONE)
            {
                available_shoots++;
            }
        }
        return available_shoots;
    }

    /*  Cada chunk de sprite de tiros, vale 4 tiros.
        Os sprites modificados são somente os centrais.
        Começa de cima para baixo.
        Exemplo:
        Se 5 disponiveis: 
        sprite[1] = ENERGY_BAR_QTY_0_INDEX(vazio);
        sprite[2] = ENERGY_BAR_QTY_0_INDEX(vazio);
        sprite[3] = ENERGY_BAR_QTY_1_INDEX(possui 1 disponível);
        sprite[4] = ENERGY_BAR_QTY_4_INDEX(cheio);
    */ 
    void hud_energy_bar::counter_handler()
    {
        int shoot_count = available_shoots();
        // if (shoot_count > 12)
        // {
        //     switch (shoot_count)
        //     {
        //     case 13:
        //         energy_bar_sprites.at(1).set_tiles(
        //             bn::sprite_items::hud_energy.tiles_item().create_tiles(
        //                 adonai::Graphics::ENERGY_BAR_QTY_1_INDEX
        //             )
        //         );
        //         break;
            
        //     case 14:
        //         energy_bar_sprites.at(1).set_tiles(
        //             bn::sprite_items::hud_energy.tiles_item().create_tiles(
        //                 adonai::Graphics::ENERGY_BAR_QTY_2_INDEX
        //             )
        //         );
        //         break;
            
        //     case 15:
        //         energy_bar_sprites.at(1).set_tiles(
        //             bn::sprite_items::hud_energy.tiles_item().create_tiles(
        //                 adonai::Graphics::ENERGY_BAR_QTY_3_INDEX
        //             )
        //         );
        //         break;
            
        //     default: //16
        //         energy_bar_sprites.at(1).set_tiles(
        //             bn::sprite_items::hud_energy.tiles_item().create_tiles(
        //                 adonai::Graphics::ENERGY_BAR_QTY_4_INDEX
        //             )
        //         );
        //         break;
        //     }
            
        // }
        // else 
        if ( shoot_count > 8 && shoot_count <= 12 )
        {
            //sprites acima
            // energy_bar_sprites.at(1).set_tiles(
            //     bn::sprite_items::hud_energy.tiles_item().create_tiles(
            //         adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
            //     )
            // );
            switch (shoot_count)
            {
            case 9:
                // este sprite
                energy_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_1_INDEX
                    )
                );
                break;
            
            case 10:
                energy_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_2_INDEX
                    )
                );
                break;
            
            case 11:
                energy_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_3_INDEX
                    )
                );
                break;
            
            default: //12
                energy_bar_sprites.at(1).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_4_INDEX
                    )
                );
                break;
            }
        }
        else if ( shoot_count > 4 && shoot_count <= 8 )
        {
            //sprites acima
            energy_bar_sprites.at(1).set_tiles(
                bn::sprite_items::hud_energy.tiles_item().create_tiles(
                    adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
                )
            );
            // energy_bar_sprites.at(2).set_tiles(
            //     bn::sprite_items::hud_energy.tiles_item().create_tiles(
            //         adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
            //     )
            // );
            switch (shoot_count)
            {
            case 5:
                // este sprite
                energy_bar_sprites.at(2).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_1_INDEX
                    )
                );
                break;
            
            case 6:
                energy_bar_sprites.at(2).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_2_INDEX
                    )
                );
                break;
            
            case 7:
                energy_bar_sprites.at(2).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_3_INDEX
                    )
                );
                break;
            
            default: //8
                energy_bar_sprites.at(2).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_4_INDEX
                    )
                );
                break;
            }
        }
        else if ( shoot_count <= 4 )
        {
            //sprites acima
            energy_bar_sprites.at(1).set_tiles(
                bn::sprite_items::hud_energy.tiles_item().create_tiles(
                    adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
                )
            );
            energy_bar_sprites.at(2).set_tiles(
                bn::sprite_items::hud_energy.tiles_item().create_tiles(
                    adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
                )
            );
            // energy_bar_sprites.at(3).set_tiles(
            //     bn::sprite_items::hud_energy.tiles_item().create_tiles(
            //         adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
            //     )
            // );
            switch (shoot_count)
            {
            case 0:
                // este sprite
                energy_bar_sprites.at(3).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_0_INDEX
                    )
                );
                break;
            
            case 1:
                energy_bar_sprites.at(3).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_1_INDEX
                    )
                );
                break;
            
            case 2:
                energy_bar_sprites.at(3).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_2_INDEX
                    )
                );
                break;
            
            case 3:
                energy_bar_sprites.at(3).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_3_INDEX
                    )
                );
                break;
            
            default: //4
                energy_bar_sprites.at(3).set_tiles(
                    bn::sprite_items::hud_energy.tiles_item().create_tiles(
                        adonai::Graphics::ENERGY_BAR_QTY_4_INDEX
                    )
                );
                break;
            }
        }
        
    }

    void hud_energy_bar::update()
    {
        counter_handler();
    }
}