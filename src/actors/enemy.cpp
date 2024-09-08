
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "enemy.h"


namespace adonai
{

    extern bn::vector<Shot*, 30> ntt_shots;

    Enemy::Enemy(   bn::sprite_item sprite_item, bn::fixed_point position, 
                    bn::sprite_item shot_sprite_item, int max_hp)
        : Actor(    sprite_item,
                    position,
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item, bn::fixed_point(0,0)))
    {
        ntt_enemies.push_back(this);
        _col = bn::rect(  (int)_pos.x(), (int)_pos.y() + 1, 
                        15, 9);

        enemy_anim = 
            bn::create_sprite_animate_action_forever
            (
                _sprite,
                0,
                sprite_item.tiles_item(),
                0,0,0,0,0,0,0
        );
        enemy_clone_anim = 
            bn::create_sprite_animate_action_forever
            (
                _sprite_clone,
                0,
                sprite_item.tiles_item(),
                0,0,0,0,0,0,0
        );

        //BN_LOG("Enemy constructor: FINISHED");
    }
    Enemy::~Enemy(){
        // BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
    }

    
    Enemy::Enemy(   bn::sprite_item sprite_item, bn::fixed_point position, 
                    bn::sprite_item shot_sprite_item, bool has_animation, 
                    const int anim_frames_duration, 
                    //anim_frames_count: 1 < value < 11
                    const int anim_frames_count, 
                    int max_hp)
        : Actor(    sprite_item,
                    position,
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item, bn::fixed_point(0,0)))
    {
        ntt_enemies.push_back(this);
        _col = bn::rect(  (int)_pos.x(), (int)_pos.y() + 1, 
                        15, 9);

        #pragma region Setup Anim
        // =============================================
        // ALETAR DE CODIGO FEIO!!
        // ALERTA DE CODIGO FEIO!!
        // Configurando animação conforme a quantidade de frames
        switch (anim_frames_count)
        {
        case 2:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1

            );
            break;
        case 3:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2

            );
            break;
        case 4:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3

            );
            break;
        case 5:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4

            );
            break;
        case 6:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5

            );
            break;
        case 7:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6

            );
            break;
        case 8:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7

            );
            break;
        case 9:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7,8

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7,8

            );
            break;
        case 10:
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7,8,9

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,1,2,3,4,5,6,7,8,9

            );
            break;
        
        default:
            BN_ERROR("ERRO! anim_frames_count tem que ser no minimo 2 e no maximo 10");
            enemy_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,0

            );
            enemy_clone_anim = 
                bn::create_sprite_animate_action_forever
                (
                    _sprite_clone,
                    anim_frames_duration,
                    sprite_item.tiles_item(),
                    0,0

            );
            break;
        }
        
        // ALETAR DE CODIGO FEIO!!
        // ALERTA DE CODIGO FEIO!!
        // =============================================
        #pragma endregion


        //BN_LOG("Enemy with Animation and Collider Dinamic constructor: FINISHED");
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

    void Enemy::shoot()
    {
        //shoot faz uma instancia de shot a frente do enemy dando inicio ao movimento automático.
        Shot_Enemy* instance_shot = new Shot_Enemy(_shot.sprite_item(),_pos);

        instance_shot->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        BN_LOG("Position: x:", instance_shot->pos().x(), ", y:", instance_shot->pos().y());
        instance_shot->sprite().set_visible(true);

        ntt_shots.push_back(instance_shot);
        BN_LOG("Spawn Shot! ntt_shots index: ", ntt_shots.size()-1);
    }

    // void Enemy::moveset_follow_path(const bn::array<bn::fixed_point,3>& path)
    // {
    //     if(_pos != path.at(path_pos_current_index))  
    //     {
    //         pos(move_towards(_pos, path.at(path_pos_current_index), velocity()));
    //         if(_pos == path.at(path_pos_current_index)){
    //             // BN_LOG("chegou no ponto: ", path_pos_current_index);
    //             path_pos_current_index = bn::clamp(path_pos_current_index+1, 0, path.size()-1);
    //         }
    //     }
    // }

    // void Enemy::update_moveset()
    // {
    //     if(_snake_group > 0){
    //         this->moveset_follow_path(path_1);
    //     }
    // }

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
        enemy_anim.update();
        enemy_clone_anim.update();
        //atualiza posicao com o moveset
        //update_moveset();
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
