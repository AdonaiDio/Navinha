
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "player.h"

#include "enemy.h"


namespace adonai
{

    extern bn::array<Shot_Enemy*, 40> _shots;

    Enemy::Enemy(   bn::fixed_point position, bn::sprite_item sprite_item, 
                    bn::sprite_item shot_sprite_item, E_Shot_Type shot_type, 
                    int max_hp)
        : Actor(    sprite_item,
                    position,
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item)),
        _shots({Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item)),
                Shot_Enemy(adonai::Shot_Enemy(shot_sprite_item))}),
        _shot_type(shot_type)
    {
        // (*ntt_enemies).push_back(this);
        _shots_is_available = { &_shots[0]._available, &_shots[1]._available, &_shots[2]._available,
                                &_shots[3]._available, &_shots[4]._available, &_shots[5]._available,
                                &_shots[6]._available, &_shots[7]._available, &_shots[8]._available,
                                &_shots[9]._available, &_shots[10]._available, &_shots[11]._available};

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
        enemy_clone_anim = 
            bn::create_sprite_animate_action_forever
            (
                _sprite_clone,
                0,
                sprite_item.tiles_item(),
                0,0
        );

        BN_LOG("Enemy constructor: FINISHED");
        // BN_LOG("enemies: ", (*ntt_enemies).size());
    }
    Enemy::~Enemy(){
        BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
        
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

    void Enemy::receive_hit(const int index)
    {
        if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        if (_hp > 0) {
            bn::sound_items::hit.play();
            hit_feedback_duration = 15; //frames de duração do hit_feedback
            return;
        }
        this->wait_to_destroy = true;
        explode();
    }

    void Enemy::just_delete_this()
    {
        _scripts.empty();
        for (int i = 0; i < (*ntt_enemies).size(); i++)
        {
            if((*ntt_enemies)[i] == this){
                (*ntt_enemies).erase((*ntt_enemies).begin()+i);
                break;
            }
        }
        this->~Enemy();
        BN_LOG("DELETED");
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
        if(_enemy_state == E_Enemy_State::E_Enemy_State_SHOOTING ){
            BN_LOG("NÃO ATIRE");
            return false;
        } // evitar que cause multiplos tiros simultâneos por vez.

        int aux_cnt = 0;
        //buscar disponibilidade de todos os 3 tiros
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if( *_shots_is_available[i] == true){
                aux_cnt++;
                if(_shot_type != E_Shot_Type::E_Shot_Type_2){ //se precisar apenas de 1 é true.
                    return true;
                }
            }
        }
        if(aux_cnt < 3){ //tiro triplo porem não tem 3 disponíveis
            return false;
        }else{
            return true;
        }
    }

#pragma region Shot_Types
    void Enemy::shot_type_1()
    {
        //Tiro unico para frente.
        //Shot_Enemy* instance_shot = new Shot_Enemy(_shot.sprite_item(),_pos);

        int shot_index = -9;
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if( *_shots_is_available[i] == true){
                shot_index = i;
                break;
            }
        }

        _shots[shot_index].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        _shots[shot_index].sprite().set_visible(true);
        // _shots[shot_index]._state = Shot_State::SHOOTING;
        _shots[shot_index]._available = false;
        
        // BN_LOG("Position: x:", _shot.pos().x(), ", y:", _shot.pos().y());
        // BN_LOG("shot visible: ",_shot.sprite().visible());
        BN_LOG("spawn shot[",shot_index,"]");
        
        // BN_LOG("Spawn Shot! _shots index: ", _shots.size()-1);
        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }

    void Enemy::shot_type_2()
    {
        //Tiro triplo diagonais e para frente.

        int i_1 = -9; //-9 um numero arbitrário para indicar que nunca foi alterado
        int i_2 = -9;
        int i_3 = -9;
        //buscar disponibilidade de todos os 3 tiros
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if( *_shots_is_available[i] == true){
                if(i_1 == -9){
                    i_1 = i;
                    continue;
                }
                else if(i_2 == -9){
                    i_2 = i;
                    continue;
                }
                else if(i_3 == -9){
                    i_3 = i;
                    break;
                }
            }
        }
        _shots[i_1].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        _shots[i_1].sprite().set_visible(true);
        // _shots[i_1]._state = Shot_State::SHOOTING;
        _shots[i_1]._available = false;
        _shots[i_1].pre_direction = bn::fixed_point(-16,-8);
        BN_LOG("spawn shot_1");
        
        _shots[i_2].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        _shots[i_2].sprite().set_visible(true);
        // _shots[i_2]._state = Shot_State::SHOOTING;
        _shots[i_2]._available = false;
        BN_LOG("spawn shot_2");
        
        _shots[i_3].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        _shots[i_3].sprite().set_visible(true);
        // _shots[i_3]._state = Shot_State::SHOOTING;
        _shots[i_3]._available = false;
        _shots[i_3].pre_direction = bn::fixed_point(-16,+8);
        BN_LOG("spawn shot_3");
            
        // BN_LOG("_shots Size: ", _shots.size());
    }

    void Enemy::shot_type_3()
    {
        // Tiro unico para ultima posição do jogador.

        int shot_index = -9;
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if( *_shots_is_available[i] == true){
                shot_index = i;
                break;
            }
        }
        _shots[shot_index].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        _shots[shot_index].sprite().set_visible(true);
        // _shots[shot_index]._state = Shot_State::SHOOTING;
        _shots[shot_index]._available = false;
        
        //direção do player
        _shots[shot_index].pre_direction = normalize(GLOBALS::global_player->pos() - pos());
        // BN_LOG("Spawn Shot! _shots index: ", _shots.size()-1);
        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }
#pragma endregion


    void Enemy::update_collider()
    {
        if(!wait_to_destroy) {
            if (_cols.at(0) != bn::rect{0,0,0,0}) {
                //se esperou por x frames, então trocar par o proximo index do _cols 
                //se for depois do ultimo voltar ao primeiro 

                //OBS: Estou adiantando o index da animação pois por algum motivo 
                /////// o index vem atrasado por 1 index em relação a sprite apresentada
                int cols_index = enemy_anim.current_index()-1<0?_cols.size()-1:enemy_anim.current_index()-1;
                _col = _cols[cols_index];
                }
            _col.set_position((int)_pos.x(), (int)_pos.y());
        }else{
            _col = bn::rect(128,88,0,0);
        }
    }

    void Enemy::update_scripts() {
        for (u_int8_t i = 0; i < _scripts.size(); i++)
        {
            if(_scripts[i] == nullptr){continue;}
            _scripts[i]->update(this);
        }
    };

    
    void Enemy::update_all_shots_occupied(){
        for (int i = 0; i < _shots_is_available.size(); i++) {
            if( *_shots_is_available.at(i) == false){
                _shots.at(i).update();
            }
        }
    };

    void Enemy::update()
    {
        if(!can_update()){ return; }

        // scripts
        update_scripts();

        enemy_anim.update();
        enemy_clone_anim.update();
        
        update_collider();
        
        _sprite.set_position(_pos);
        _sprite_clone.set_position(_pos);

        hit_feedback();

        update_all_shots_occupied();

        if(explosion && !explosion->_explosion_anim.done()){
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy && all_shots_available()){
            wait_to_destroy = false;
            _scripts.empty();
            just_delete_this();
        }

    }

    bool Enemy::all_shots_available()
    {
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if(*_shots_is_available[i] == false){
                return false;
            }
        }
        return true;
    }

// (Só por segurança, talvez não precise, mas caso entre no 
// loop fora após destruído, isso ira impedir continuar o update)
    bool Enemy::can_update(){
        if(this->hp() > 0 || this->wait_to_destroy){
            return true;
        }
        return false;
    }
}
