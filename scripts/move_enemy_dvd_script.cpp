#pragma once
//butano
#include <bn_log.h>
#include "bn_display.h"
//assets
//#include <bn_sprite_items_.h>
//my code
#include <../include/utility.h>
#include "enemy.h"
//this interface
#include <D:/Adonai/My_ROMs/Navinha/scripts/i_script.hpp>

namespace adonai {
    class Move_Enemy_DVD_Script : public I_Script<Enemy>{
        private:
        int8_t _x = -1; 
        int8_t _y = 1; 
        public:
        void start(Enemy* e) override {
        };
        void update(Enemy* e) override {
            _y = (e->pos().y() >= bn::display::height()/2) ? -1 :  
                    (e->pos().y() <= -bn::display::height()/2) ? 1 : _y;
            _x = (e->pos().x() >= bn::display::width()/2) ? -1 : 
                    (e->pos().x() <= -bn::display::width()/2) ? 1 : _x;

            // e->pos(move_towards(e->pos(), e->pos()+bn::fixed_point(_x*16,_y*16), e->velocity()));
            e->pos(e->pos()+bn::fixed_point(_x*e->velocity(),_y*e->velocity()));

        };
    };
}
/*
A ideia é fazer aquele efeito de ficar quicando 
na tela que nem a proteção de tela de DVD
*/