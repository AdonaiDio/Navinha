#pragma once
#include "bn_sprite_ptr.h"
#include "bn_core.h"

namespace adonai
{
    namespace Graphics
    {
        enum Energy_Bar_Index{
            TOP_BAR_INDEX = 0,
            ENERGY_BAR_QTY_0_INDEX = 1,
            ENERGY_BAR_QTY_1_INDEX = 2,
            ENERGY_BAR_QTY_2_INDEX = 3,
            ENERGY_BAR_QTY_3_INDEX = 4,
            ENERGY_BAR_QTY_4_INDEX = 5,
            BOTTOM_BAR_INDEX = 6
        };
    }
    class Player;

    class hud_energy_bar
    {
    private:
        /*preciso alocar as sprites do tiro e também saber o index de cada estado
        separar em as sprites que mudam o estado de 'cheio' até 'vazio'
        depois ter um algoritimo que trate quem vai mudar o estado e em que ordem*/
        adonai::Player& _player;
    public:
        bn::array<bn::sprite_ptr, 5> energy_bar_sprites;
        hud_energy_bar(Player& player);
        ~hud_energy_bar();

        int available_shoots();
        void counter_handler();
        void update();
    };
}