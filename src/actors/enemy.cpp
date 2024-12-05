
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "player.h"

#include "enemy.h"


namespace adonai
{
    Enemy::Enemy(bn::fixed_point position, 
                bn::sprite_item sprite_item, 
                int max_hp) :
        Actor(sprite_item, position, max_hp)
    {
        _col = bn::rect(  (int)_pos.x(), (int)_pos.y() + 1, 
                        15, 9);

        enemy_anim = 
            bn::create_sprite_animate_action_forever
            (
                _sprite,
                0,
                sprite_item.tiles_item(),
                0,0
        );
        
        BN_LOG("Enemy constructor: FINISHED");
    }

    Enemy::Enemy(   bn::fixed_point position, bn::sprite_item sprite_item,
                    int max_hp, bn::sprite_item shot_sprite_item, 
                    E_Shot_Type shot_type) :
        Actor( sprite_item, position, max_hp),
        _shot(shot_sprite_item),
        _shot_type(shot_type) 
    {
        has_shot = true;
        _col = bn::rect(  (int)_pos.x(), (int)_pos.y() + 1, 
                        15, 9);

        enemy_anim = 
            bn::create_sprite_animate_action_forever
            (
                _sprite,
                0,
                sprite_item.tiles_item(),
                0,0
        );

        BN_LOG("Enemy constructor: FINISHED");
    }
    void Enemy::copy_Enemy(const Enemy &enemy)
    {
        copy_Actor(enemy);
        _cols = enemy._cols;
        enemy_anim = enemy.enemy_anim;
        has_shot = enemy.has_shot;
        _shot = enemy._shot;
        _shot_type = enemy._shot_type;
    }

    //add and start script
    void Enemy::add_script(I_Script<Enemy>& script)
    {
        _scripts.push_back(&script);
        _scripts[_scripts.size()-1]->start(this);
    }

    void Enemy::remove_script(I_Script<Enemy> &script)
    {
        // get index of recieved script
        for (int i = 0; i < _scripts.size(); i++)
        {
            if(_scripts.at(i) == &script){
                _scripts.erase(_scripts.begin()+i);
                return;
            }
            
        }
    }

    void Enemy::receive_hit()
    {
        if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        if (_hp > 0) {
            if(!is_hitting){
                hit_feedback();
            }
            return;
        }
        wait_to_destroy = true;
        _scripts.empty();
        explode();
    }

    void Enemy::shoot()
    {
        if(!can_shoot()){return;}
        _enemy_state = E_Enemy_State::E_Enemy_State_SHOOTING;
        
        if (_shot_type ==  E_Shot_Type::E_Shot_Type_1){
            shot_type_1();
        }
        else if (_shot_type ==  E_Shot_Type::E_Shot_Type_2){
            shot_type_2();
        }
        else if (_shot_type ==  E_Shot_Type::E_Shot_Type_3){
            shot_type_3();
        }

        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }

    bool Enemy::can_shoot()
    {
        if(!has_shot){
            return false;
        }
        int n = n_shots_availables();
        if(_enemy_state == E_Enemy_State::E_Enemy_State_SHOOTING 
            || (n < 3) ){ //coloquei 3 no lugar de 40 para ter redundância quanto a disponibilidade de shots quando mais de um enemy tentar execução simultanea
            BN_LOG("NÃO ATIRE - Falta disponiveis: ", n);
            return false;
        } // evitar que cause multiplos tiros simultâneos por vez.
        return true;
    }

    int Enemy::n_shots_availables(){
        int counter = 0;
        for (int i = 0; i < ntt_shots->size(); i++)
        {
            if(ntt_shots->at(i)._available){
                counter++;
            }
        }
        return counter;
    }

#pragma region Shot_Types
    //Tiro unico para frente.
    void Enemy::shot_type_1()
    {
        //pega o primeiro disponível e substitui por um com novas informações
        for (int i = 0; i < ntt_shots->size(); i++)
        {
            if(ntt_shots->at(i)._available == true){
                ntt_shots->at(i)._available = false;
                ntt_shots->at(i).copy_Shot_Enemy( Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) ));
                break;
            }
        }
        BN_LOG("ntt_shots usados: ", 40 - n_shots_availables());
        BN_LOG("shot instance added to ntt_shots");
    }

    //Tiro triplo diagonais e para frente.
    void Enemy::shot_type_2()
    {
        int counter = 0;
        for (int i = 0; i < ntt_shots->size(); i++)
        {
            //comporta mais 3 tiros?
            if(n_shots_availables() >= 3){ 
                if(ntt_shots->at(i)._available == true){
                    counter++;
                    ntt_shots->at(i)._available = false;
                    ntt_shots->at(i).copy_Shot_Enemy( Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) ));
                    switch (counter)
                    {
                    case 1:
                        ntt_shots->at(i).pre_direction = bn::fixed_point(-16,-8);
                    break;
                    case 2: 
                        ntt_shots->at(i).pre_direction = bn::fixed_point{0,0};
                    break;
                    case 3:
                        ntt_shots->at(i).pre_direction = bn::fixed_point(-16,+8);
                    break;
                    default:
                        BN_ERROR("Switch com valor inexperado!");
                    break;
                    }
                }
                if(counter >= 3){
                    break;
                }
            }
        }
        
        BN_LOG("ntt_shots usados: ", 40 - n_shots_availables());
        BN_LOG("shot instance added to ntt_shots");
    }

    // Tiro unico para ultima posição do jogador.
    void Enemy::shot_type_3()
    {
        for (int i = 0; i < ntt_shots->size(); i++)
        {
            if(ntt_shots->at(i)._available == true){
                ntt_shots->at(i)._available = false;
                ntt_shots->at(i).copy_Shot_Enemy( Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) ));
                ntt_shots->at(i).pre_direction = normalize(GLOBALS::global_player->pos() - pos());
                break;
            }
        }
        
        BN_LOG("ntt_shots usados: ", 40 - n_shots_availables());
        BN_LOG("shot instance added to ntt_shots");
    }
#pragma endregion


    void Enemy::update_collider()
    {
        if(!wait_to_destroy) {
            if (_cols.at(0) != bn::rect{0,0,0,0}) {
                int cols_index = enemy_anim.current_index()-1<0?_cols.size()-1:enemy_anim.current_index()-1;
                _col = _cols[cols_index];
                }
            _col.set_position((int)_pos.x(), (int)_pos.y());
        }else{
            _col = bn::rect(128,88,0,0);
        }
    }
    
    void Enemy::update_scripts() {
        if(_scripts.size() == 0) { return; }
        for (u_int8_t i = 0; i < _scripts.size(); i++)
        {
            if(_scripts[i] == nullptr){continue;}
            _scripts[i]->update(this);
        }
    };

    void Enemy::update()
    {
        if(!can_update()){ return; }
        
        // scripts
        update_scripts();

        enemy_anim.update();
        
        update_collider();
        
        _sprite.set_position(_pos);
        
        update_hit_fx();

        if(explosion.available == false && !explosion._explosion_anim.done()) {
            explosion.update();
        }
        if(explosion._explosion_anim.done() && explosion.available && wait_to_destroy ) {// && all_shots_available()){
            wait_to_destroy = false;
            _available = true;
        }
    }

// (Só por segurança, talvez não precise, mas caso entre no 
// loop fora após destruído, isso ira impedir continuar o update)
    bool Enemy::can_update(){
        if(hp() > 0 || wait_to_destroy){
            return true;
        }
        return false;
    }
}
