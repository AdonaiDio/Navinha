
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "player.h"

#include "enemy.h"


namespace adonai
{
    Enemy::Enemy(bn::vector<Enemy *, 20> *ntt_e, 
                bn::fixed_point position, bn::sprite_item sprite_item, 
                int max_hp) :
        Actor(sprite_item, position, max_hp),
        ntt_enemies(ntt_e)
    {
        ntt_enemies->push_back(this);
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
        // BN_LOG("enemies: ", (*ntt_enemies).size());
    }

    Enemy::Enemy( bn::vector<Enemy*, 20>* ntt_e,
                    bn::fixed_point position, bn::sprite_item sprite_item,
                    int max_hp, bn::sprite_item shot_sprite_item, 
                    E_Shot_Type shot_type) :
        Actor( sprite_item, position, max_hp),
        ntt_enemies(ntt_e),
        _shot(shot_sprite_item),
        _shot_type(shot_type)
    {
        has_shot = true;
        ntt_enemies->push_back(this);
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

    void Enemy::receive_hit()
    {
        if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        if (_hp > 0) {
            bn::sound_items::hit.play();
            if(!is_hitting){
                hit_feedback();
            }
            return;
        }
        this->wait_to_destroy = true;
        explode();
    }
    // void Enemy::receive_hit(int index) //não precisa
    // {
    //     if(this != ntt_enemies->at(index)){return;}
    //     if (_hp <= 0) {return;}//assegurar que não vai receber hit se já estiver morto
    //     _hp -= 1;
    //     if (_hp > 0) {
    //         bn::sound_items::hit.play();
    //         if(!is_hitting){
    //             hit_feedback();
    //         }
    //         return;
    //     }
    //     this->wait_to_destroy = true;
    //     explode();
    // }

    void Enemy::just_delete_this()
    {
        _scripts.empty();
        for (int i = 0; i < ntt_enemies->size(); i++)
        {
            if(ntt_enemies->at(i) == this){
                ntt_enemies->erase(ntt_enemies->begin()+i);
                break;
            }
        }
        if(hit_fx != nullptr){
            hit_fx->~Hit_FX();
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
        if(!has_shot){
            // BN_LOG("Não possui shot!"); 
            return false;
        }
        if(_enemy_state == E_Enemy_State::E_Enemy_State_SHOOTING 
            || !(ntt_shots->size() < 37)
            || bn::sprites::available_items_count() < 12 ){
            // BN_LOG("NÃO ATIRE");
            return false;
        } // evitar que cause multiplos tiros simultâneos por vez.
        return true;
    }

#pragma region Shot_Types
    void Enemy::shot_type_1()
    {
        //Tiro unico para frente.
        Shot_Enemy* instance_shot = new Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) );
        // instance_shot->_available = false;

        BN_LOG("ntt_shots size: ",ntt_shots->size());
        ntt_shots->push_back(instance_shot);
        BN_LOG("shot instance added to ntt_shots");
    }

    void Enemy::shot_type_2()
    {
        //Tiro triplo diagonais e para frente.
        Shot_Enemy* instance_shot_1 = new Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) );
        // instance_shot_1->_available = false;
        instance_shot_1->pre_direction = bn::fixed_point(-16,-8);
        ntt_shots->push_back(instance_shot_1);
        Shot_Enemy* instance_shot_2 = new Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) );
        // instance_shot_2->_available = false;
        ntt_shots->push_back(instance_shot_2);
        Shot_Enemy* instance_shot_3 = new Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) );
        // instance_shot_3->_available = false;
        instance_shot_3->pre_direction = bn::fixed_point(-16,+8);
        ntt_shots->push_back(instance_shot_3);
    }

    void Enemy::shot_type_3()
    {
        // Tiro unico para ultima posição do jogador.
        Shot_Enemy* instance_shot = new Shot_Enemy(_shot, (_pos + bn::fixed_point{-7,0}) );
        // instance_shot->_available = false;
        instance_shot->pre_direction = normalize(GLOBALS::global_player->pos() - pos());
        ntt_shots->push_back(instance_shot);
    }
#pragma endregion


    void Enemy::update_collider()
    {
        if(!wait_to_destroy) {
            if (_cols.at(0) != bn::rect{0,0,0,0}) {
                // Ternario: Se esperou por x frames, então trocar para o proximo index do _cols 
                // se for depois do ultimo voltar ao primeiro 
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

    void Enemy::update()
    {
        if(!can_update()){ return; }
        
        // scripts
        update_scripts();

        enemy_anim.update();
        
        update_collider();
        
        _sprite.set_position(_pos);
        
        if(hit_fx){
            hit_fx->update();
        }
        if(explosion && !explosion->_explosion_anim.done()) {
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy ) {// && all_shots_available()){
            wait_to_destroy = false;
            _scripts.empty();
            just_delete_this();
        }
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
