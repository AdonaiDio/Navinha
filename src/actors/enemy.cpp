#include "bn_log.h"
#include "bn_color.h"
#include "bn_colors.h"
#include <bn_sprite_palette_ptr.h>
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sprite_palette_items_feedback_palette.h"

#include "enemy.h"

namespace adonai
{

    Enemy::Enemy(bn::sprite_item sprite_item, bn::fixed x, bn::fixed y, bn::sprite_item shoot_sprite_item, int max_hp, int snake_group) :
        _sprite(sprite_item.create_sprite(x,y)),
        _sprite_clone(sprite_item.create_sprite(x,y)),
        _pos(x,y),
        _shoot(adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Left, _tag)),
        _hp(max_hp),
        _snake_group(snake_group)
    {
        ntt_enemies.push_back(this);
        _sprite_clone.set_z_order(-1);
        _sprite_clone.set_visible(false);
        _sprite_clone.set_palette(bn::sprite_palette_items::feedback_palette);
    }
    Enemy::~Enemy(){
        // BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
    }

    bn::sprite_ptr Enemy::sprite()
    {
        return _sprite;
    }

    bn::fixed_point Enemy::pos()
    {
        return _pos;
    }

    void Enemy::pos(bn::fixed_point location)
    {
        _pos = location;
    }

    bn::rect Enemy::col()
    {
        return _col;
    }

    int Enemy::hp()
    {
        return _hp;
    }
    void Enemy::hp(int new_value)
    {
        _hp = new_value;
    }

    void Enemy::hit_feedback()
    {
        if (hit_feedback_duration > 0)
        {
            //!!! Codigo RUIM. Paleta trocando para todos os tipos de enemy !!!
            _sprite_clone.set_visible(true);
            bn::sprite_palette_ptr clone_palette = _sprite_clone.palette();
            //muda as cores para as cores do enemy que está levando hit já que a palette é compartilhada
            for (int i = 0; i < _sprite.palette().colors().size(); i++)
            {
                clone_palette.set_color(i,_sprite.palette().colors().at(i));
            }
            
            if (hit_feedback_duration % 15 == 0) //se for divisível por 15
            {
                clone_palette.set_fade(bn::colors::white, intensity);
                intensity = 1;
            }
            else
            {
                intensity = bn::clamp((bn::fixed(-0.1) + intensity), bn::fixed(0), bn::fixed(1));
                clone_palette.set_fade(bn::colors::white, intensity);
            }
            hit_feedback_duration--;
            if(hit_feedback_duration == 0){
                _sprite_clone.set_visible(false);
            }
        }        
    }
    
    void Enemy::receive_hit(const int i)
    {
        if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        if (_hp > 0) {
            hit_feedback_duration = 15; //frames de duração do hit_feedback
            return;
        }
        wait_to_destroy = true;
        //se foi o suficiente para destruir então apagar do vector
        ntt_enemies.erase(ntt_enemies.begin()+i);
        explode();
        
        //this->~Enemy();
    }

    //Spawn EXPLOSION_FX
    void Enemy::explode()
    {
        _sprite.set_visible(false);
        _sprite_clone.set_visible(false);
        explosion = new Explosion_FX(_pos);
    }


    int Enemy::dir(bn::fixed this_axis, bn::fixed target_axis) {
        if(this_axis > target_axis){
            return -1;
        }
        else if(this_axis < target_axis){
            return 1;
        }
        return 0;
    };

    //funciona apenas no Update()
    void Enemy::translate_pos_to(const bn::fixed_point& target_pos)
    {
        const bn::array<bn::fixed, 2> vector_pos_magnetude = {
            (target_pos.x() - _pos.x()>0)?target_pos.x() - _pos.x():-(target_pos.x() - _pos.x()),
            (target_pos.y() - _pos.y()>0)?target_pos.y() - _pos.y():-(target_pos.y() - _pos.y())};
        
        const int x_dir = dir(_pos.x(), target_pos.x());
        const int y_dir = dir(_pos.y(), target_pos.y());
        //se x>y logo x dividir por y, para saber quantos passos pro x para cada y
        #define __x_ vector_pos_magnetude.at(0)
        #define __y_ vector_pos_magnetude.at(1)
        bn::fixed mx;
        if(__y_ != 0) {
            mx = __x_ / __y_;
        }
        mx = (__x_ == __y_) ? 0 : 1;
        bn::fixed my; // = vector_pos_pointer.at(1) / vector_pos_pointer.at(0);
        if(__x_ != 0) {
            my = __y_ / __x_;
        }
        else if(__y_ == __x_) {
            my = 0;
        }
        else { 
            my = 1;
        }
        //atualiza posição em 1px mais próximo do alvo
        // BN_LOG("x:",_pos.x()," (x_dir: ",x_dir," mx: ",mx,")");
        // BN_LOG("y:",_pos.y()," (y_dir: ",y_dir," my: ",my,")");
        _pos = bn::fixed_point ( _pos.x() + (x_dir*mx).round_integer(), 
                                _pos.y() + (y_dir*my).round_integer());
    }

    void Enemy::moveset_follow_path(const bn::array<bn::point,3>& path)
    {
        if(_pos != path.at(path_pos_current_index))  
        {
            translate_pos_to(path.at(path_pos_current_index));
            if(_pos == path.at(path_pos_current_index)){
                // BN_LOG("chegou no ponto: ", path_pos_current_index);
                path_pos_current_index = bn::clamp(path_pos_current_index+1, 0, path.size()-1);
            }
        }
        
    }

    // void Enemy::identify_snakeGroup(){
    //     ntt_enemies_group_1.clear();
    //     for (int i = 0; i < ntt_enemies.size(); i++)
    //     {
    //         if (ntt_enemies.at(i))
    //         {
    //             if (ntt_enemies.at(i)->_snake_group == 1)
    //             {
    //                 ntt_enemies_group_1.push_back(ntt_enemies.at(i));
    //             }
    //         }
    //     }
    // }

    void Enemy::moveset_snake(){
        //if(ntt_enemies_group_1.size() == 0){return;}
        this->moveset_follow_path(path_1);
    }


    void Enemy::update_moveset()
    {
        if(_snake_group > 0){
            moveset_snake();
        }
        // _pos = bn::fixed_point (
        //     clamp(_pos.x()-1, bn::fixed(-120-8), bn::fixed(120+8)), 
        //     clamp(_pos.y(), bn::fixed(-80-8), bn::fixed(80+8))
        //     );//to the left to the left
        // //action?
    }
    void Enemy::update_collider()
    {
        if(!wait_to_destroy){
            _col = bn::rect((int)_pos.x(), (int)_pos.y() + 1,
                            15, 9);
        }else{
            _col = bn::rect(128,88,0,0);
        }
    }
    void Enemy::update()
    {
        //atualiza posicao com o moveset
        update_moveset();
        //reposicionar em relação ao _pos
        update_collider();
        //sprite correction
        _sprite.set_position(_pos);
        _sprite_clone.set_position(_pos);

        hit_feedback();

        if(explosion && !explosion->_explosion_anim.done()){
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy){
            wait_to_destroy = false;
            this->~Enemy();
        }

        //BN_LOG("enemy x:", _col.width(), " y:", _col.height());
    }
}
