#pragma once
#include "bn_sprite_ptr.h"
#include "bn_core.h"

namespace adonai
{
    namespace Graphics
    {
        enum HP_Bar_Index{
            LEFT_BAR_INDEX = 0,
            HP_BAR_QTY_4_INDEX = 1,
            HP_BAR_QTY_3_INDEX = 2,
            HP_BAR_QTY_2_INDEX = 3,
            HP_BAR_QTY_1_INDEX = 4,
            HP_BAR_QTY_0_INDEX = 5,
            RIGHT_BAR_INDEX = 6
        };
    }
    class Player;

    class hud_hp_bar
    {
    private:
        /*preciso alocar as sprites do tiro e também saber o index de cada estado
        separar em as sprites que mudam o estado de 'cheio' até 'vazio'
        depois ter um algoritimo que trate quem vai mudar o estado e em que ordem*/
        adonai::Player& _player;
    public:
        bn::array<bn::sprite_ptr, 3> hp_bar_sprites;
        hud_hp_bar(Player& player);
        ~hud_hp_bar();

        void counter_handler();
        void update();
    };
}