
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "player.h"
// #include "hit_fx.h"

#include "inimigo.h"


namespace adonai
{

    extern bn::array<Shot_Enemy*, 40> _shots;

    Inimigo::Inimigo(  bn::fixed_point position, bn::sprite_item sprite_item, 
                    bn::sprite_item shot_sprite_item, E_Shot_Type shot_type, 
                    int max_hp) :
        _sprite(sprite_item.create_sprite(position)),
        _sprite_item(sprite_item),
        _sprite_shot(shot_sprite_item.create_sprite({136,96})),
        _sprite_shot_2(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_3(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_4(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_5(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_6(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_7(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_8(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_9(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_10(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_11(shot_sprite_item.create_sprite({136,96})),
        // _sprite_shot_12(shot_sprite_item.create_sprite({136,96})),
        _pos(position),
        _hp(max_hp),
        // _shot_sprite_item(shot_sprite_item),
        _shots({New_Shot_Enemy(), New_Shot_Enemy(), New_Shot_Enemy(),
                New_Shot_Enemy(), New_Shot_Enemy(), New_Shot_Enemy(),
                New_Shot_Enemy(), New_Shot_Enemy(), New_Shot_Enemy(),
                New_Shot_Enemy(), New_Shot_Enemy(), New_Shot_Enemy()}),
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
        // enemy_clone_anim = 
        //     bn::create_sprite_animate_action_forever
        //     (
        //         _sprite_clone,
        //         0,
        //         sprite_item.tiles_item(),
        //         0,0
        // );

        BN_LOG("Enemy constructor: FINISHED");
        // BN_LOG("enemies: ", (*ntt_enemies).size());
    }
    Inimigo::~Inimigo(){
        BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
        
    }

    //add and start script
    // void Inimigo::add_script(I_Script<Inimigo>& script)
    // {
    //     _scripts.push_back(&script);
    //     _scripts[_scripts.size()-1]->start(this);
    // }

    // void Inimigo::remove_script(I_Script<Inimigo> &script)
    // {
    //     // get index of recieved script
    //     for (int i = 0; i < _scripts.size(); i++)
    //     {
    //         if(_scripts.at(i) == &script){
    //             _scripts.erase(_scripts.begin()+i);
    //             return;
    //         }
            
    //     }
    // }

    void Inimigo::receive_hit()
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

    void Inimigo::just_delete_this()
    {
        // _scripts.empty();
        // for (int i = 0; i < (*ntt_enemies).size(); i++)
        // {
        //     if((*ntt_enemies)[i] == this){
        //         (*ntt_enemies).erase((*ntt_enemies).begin()+i);
        //         break;
        //     }
        // }
        if(hit_fx != nullptr){
            hit_fx->~Hit_FX();
        }
        this->~Inimigo();
        BN_LOG("DELETED");
    }

    void Inimigo::shoot()
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

    bool Inimigo::can_shoot()
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
    void Inimigo::shot_type_1()
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
        // _shots[shot_index].sprite().set_visible(true);
        // _shots[shot_index]._state = Shot_State::SHOOTING;
        _shots[shot_index]._available = false;
        
        // BN_LOG("Position: x:", _shot.pos().x(), ", y:", _shot.pos().y());
        // BN_LOG("shot visible: ",_shot.sprite().visible());
        BN_LOG("spawn shot[",shot_index,"]");
        
        // BN_LOG("Spawn Shot! _shots index: ", _shots.size()-1);
        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }

    void Inimigo::shot_type_2()
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
        // _shots[i_1].sprite().set_visible(true);
        // _shots[i_1]._state = Shot_State::SHOOTING;
        _shots[i_1]._available = false;
        _shots[i_1].pre_direction = bn::fixed_point(-16,-8);
        BN_LOG("spawn shot_1");
        
        _shots[i_2].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        // _shots[i_2].sprite().set_visible(true);
        // _shots[i_2]._state = Shot_State::SHOOTING;
        _shots[i_2]._available = false;
        BN_LOG("spawn shot_2");
        
        _shots[i_3].pos(bn::fixed_point(_pos.x()-4, _pos.y()));
        // _shots[i_3].sprite().set_visible(true);
        // _shots[i_3]._state = Shot_State::SHOOTING;
        _shots[i_3]._available = false;
        _shots[i_3].pre_direction = bn::fixed_point(-16,+8);
        BN_LOG("spawn shot_3");
            
        // BN_LOG("_shots Size: ", _shots.size());
    }

    void Inimigo::shot_type_3()
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
        // _shots[shot_index].sprite().set_visible(true);
        // _shots[shot_index]._state = Shot_State::SHOOTING;
        _shots[shot_index]._available = false;
        
        //direção do player
        _shots[shot_index].pre_direction = normalize(GLOBALS::global_player->pos() - pos());
        // BN_LOG("Spawn Shot! _shots index: ", _shots.size()-1);
        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }
#pragma endregion


    void Inimigo::update_collider()
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

    // void Inimigo::update_scripts() {
    //     for (u_int8_t i = 0; i < _scripts.size(); i++)
    //     {
    //         if(_scripts[i] == nullptr){continue;}
    //         _scripts[i]->update(this);
    //     }
    // };

    
    void Inimigo::update_all_shots_occupied(){
        for (int i = 0; i < _shots_is_available.size(); i++) {
            if( *_shots_is_available.at(i) == false){
                _shots.at(i).update();
            }
        }
    };

    void Inimigo::update()
    {
        if(!can_update()){ return; }


        // scripts
        // update_scripts();

        enemy_anim.update();
        // enemy_clone_anim.update();
        
        update_collider();
        
        _sprite.set_position(_pos);
        
        update_shots();
        
        if(hit_fx){
            hit_fx->update();
        }
        if(explosion && !explosion->_explosion_anim.done()){
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy  ){// && all_shots_available()){
            wait_to_destroy = false;
            // _scripts.empty();
            just_delete_this();
        }

        shooting();
        damaged();

    }

    bool Inimigo::all_shots_available()
    {
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if(*_shots_is_available[i] == false){
                return false;
            }
        }
        return true;
    }
    int Inimigo::shots_occupied_qty()
    {
        int counter = 0;
        for (int i = 0; i < _shots_is_available.size(); i++)
        {
            if(*_shots_is_available[i] == false){
                counter++;
            }
        }
        return counter;
    }

    void Inimigo::update_shared_sprite_shot_position(bn::sprite_ptr& sprite_shot)
    {
        bool return_count_i_to_zero = true;
        
        if(shots_occupied_qty() > 1){
            for (int i = _last_spr_shot_updated_index; i < _shots_is_available.size(); i++) {
                if( _last_spr_shot_updated_index != i &&
                    *_shots_is_available.at(i) == false )
                {
                    sprite_shot.set_position(_shots.at(i).pos());
                    _last_spr_shot_updated_index = i;
                    return_count_i_to_zero = false;
                    break;
                }
            }
        }
        //apenas em caso de ter percorrido a lista até o fim que vai buscar desde o 0
        if( return_count_i_to_zero == false){return;}

        for (int i = 0; i < _shots_is_available.size(); i++) {
            if(_last_spr_shot_updated_index == i){
                if( shots_occupied_qty() == 1 &&
                    *_shots_is_available.at(i) == false)
                {
                    sprite_shot.set_position(_shots.at(i).pos());
                    _last_spr_shot_updated_index = i;
                    break;
                }
            }else{
                if( *_shots_is_available.at(i) == false){
                    sprite_shot.set_position(_shots.at(i).pos());
                    _last_spr_shot_updated_index = i;
                    break;
                }
            }
        }
    }

    void Inimigo::update_shots()
    {
        update_all_shots_occupied();
        if(!all_shots_available()){
            update_shared_sprite_shot_position(_sprite_shot);
            if(shots_occupied_qty() > 1){
                update_shared_sprite_shot_position(_sprite_shot_2);
                // update_shared_sprite_shot_position(_sprite_shot_3 );
                // update_shared_sprite_shot_position(_sprite_shot_4 );
                // update_shared_sprite_shot_position(_sprite_shot_5 );
                // update_shared_sprite_shot_position(_sprite_shot_6 );
                // update_shared_sprite_shot_position(_sprite_shot_7 );
                // update_shared_sprite_shot_position(_sprite_shot_8 );
                // update_shared_sprite_shot_position(_sprite_shot_9 );
                // update_shared_sprite_shot_position(_sprite_shot_10 );
                // update_shared_sprite_shot_position(_sprite_shot_11 );
                // update_shared_sprite_shot_position(_sprite_shot_12 );
            }
            else{
                _sprite_shot_2.set_position({136,96});
            }
        }
    }

// (Só por segurança, talvez não precise, mas caso entre no 
// loop fora após destruído, isso ira impedir continuar o update)
    bool Inimigo::can_update(){
        if(this->hp() > 0 || this->wait_to_destroy){
            return true;
        }
        return false;
    }
}
