
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"

#include "utility.h"

#include "enemy.h"

namespace adonai
{
    Enemy::Enemy(bn::sprite_item sprite_item, bn::fixed_point position, bn::sprite_item shot_sprite_item, int max_hp, int snake_group)
        : Actor(    sprite_item,
                    position, 
                    shot_sprite_item, 
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item, bn::fixed_point(0,0))),
        _snake_group(snake_group)
    {
        ntt_enemies.push_back(this);
        _col = bn::rect(  (int)_pos.x(), (int)_pos.y() + 1, 
                        15, 9);
        //BN_LOG("Enemy constructor: FINISHED");
    }
    Enemy::~Enemy(){
        // BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
    }

    void Enemy::receive_hit(const int index)
    {
        if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        if (_hp > 0) {
            bn::sound_items::hit.play();
            hit_feedback_duration = 15; //frames de duração do hit_feedback
            return;
        }
        wait_to_destroy = true;
        //se foi o suficiente para destruir então apagar do vector
        ntt_enemies.erase(ntt_enemies.begin()+index);
        explode();
    }

    void Enemy::moveset_follow_path(const bn::array<bn::fixed_point,3>& path)
    {
        if(_pos != path.at(path_pos_current_index))  
        {
            pos(move_towards(_pos, path.at(path_pos_current_index), velocity()));
            if(_pos == path.at(path_pos_current_index)){
                // BN_LOG("chegou no ponto: ", path_pos_current_index);
                path_pos_current_index = bn::clamp(path_pos_current_index+1, 0, path.size()-1);
            }
        }
    }

    void Enemy::update_moveset()
    {
        if(_snake_group > 0){
            this->moveset_follow_path(path_1);
        }
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
    }
}
