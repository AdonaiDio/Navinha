
#include "bn_display.h"
#include "bn_array.h"
#include "bn_sound_items.h"
#include "bn_span.h"

#include "utility.h"

#include "player.h"

#include "enemy.h"


namespace adonai
{

    extern bn::vector<Shot*, 30> ntt_shots;

    Enemy::Enemy(   bn::sprite_item sprite_item, bn::fixed_point position, 
                    bn::sprite_item shot_sprite_item, E_Shot_Type shot_type, 
                    int max_hp)
        : Actor(    sprite_item,
                    position,
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item)),
        _shot_type(shot_type)
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
        //BN_LOG("Enemy constructor: FINISHED");
    }
    Enemy::~Enemy(){
        // BN_LOG("Enemy destruido");
        // BN_LOG("enemies: ", ntt_enemies.size());
        
    }

    
    Enemy::Enemy(   bn::sprite_item sprite_item, bn::fixed_point position, 
                    bn::sprite_item shot_sprite_item, E_Shot_Type shot_type, 
                    const int anim_frames_duration, 
                    //anim_frames_qty: 1 < value < 11
                    const int anim_frames_qty, 
                    int max_hp)
        : Actor(    sprite_item,
                    position,
                    max_hp),
        _shot(adonai::Shot_Enemy(shot_sprite_item)),
        _shot_type(shot_type)
    {
        ntt_enemies.push_back(this);

        _col = bn::rect(  (int)_pos.x()-1, (int)_pos.y()-1, 
                        10, 14);
        //CODIGO ERRADO!!!
        //definir os colliders de cada frame
        //TODO: Esses colliders deveriam ser definidos de forma automática baseado na sprite recebida
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y()-1,
                        10, 14} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y()-1,
                        10, 14} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y()-1,
                        10, 12} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y(),
                        10, 12} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y(),
                        10, 10} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y(),
                        10, 12} );
        _cols.push_back( { (int)_pos.x()-1, (int)_pos.y()-1,
                        10, 12} );

        #pragma region Setup Anim
        // =============================================
        // ALETAR DE CODIGO FEIO!!
        // ALERTA DE CODIGO FEIO!!
        // Configurando animação conforme a quantidade de frames
        switch (anim_frames_qty)
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
            BN_ERROR("ERRO! anim_frames_qty tem que ser no minimo 2 e no maximo 10");
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


    // Enemy::Enemy(){

    // }


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
        for (int i = 0; i < ntt_enemies.size(); i++)
        {
            if(ntt_enemies[i] == this){
                ntt_enemies.erase(ntt_enemies.begin()+i);
                break;
            }
        }
        this->~Enemy();
        BN_LOG("DELETED");
    }

    //shoot() :  Spawna a(s) instância(s) de tiro/shot 1 vez.
    // ///////// Também distingue o tipo do tiro. 
    void Enemy::shoot()
    {
        //Primeiro impedir que atire enquanto ainda estiver concluindo o SHOOTING
        if(_enemy_state == E_Enemy_State::E_Enemy_State_SHOOTING){return;}
        _enemy_state = E_Enemy_State::E_Enemy_State_SHOOTING;

        Shot_Enemy* instance_shot_1 = new Shot_Enemy(_shot.sprite_item(),_pos);
        Shot_Enemy* instance_shot_2 = new Shot_Enemy(_shot.sprite_item(),_pos);
        Shot_Enemy* instance_shot_3 = new Shot_Enemy(_shot.sprite_item(),_pos);

        switch (_shot_type)
        {
        case E_Shot_Type::E_Shot_Type_2:

            instance_shot_1->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
            instance_shot_1->sprite().set_visible(true);
            ntt_shots.push_back(instance_shot_1);
            instance_shot_1->pre_direction = bn::fixed_point(-16,-8);
            BN_LOG("spawn shot_1");

            instance_shot_2->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
            instance_shot_2->sprite().set_visible(true);
            ntt_shots.push_back(instance_shot_2);
            BN_LOG("spawn shot_2");

            instance_shot_3->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
            instance_shot_3->sprite().set_visible(true);
            ntt_shots.push_back(instance_shot_3);
            instance_shot_3->pre_direction = bn::fixed_point(-16,+8);
            BN_LOG("spawn shot_3");

            BN_LOG("ntt_shots Size: ", ntt_shots.size());
            break;

        case E_Shot_Type::E_Shot_Type_3:
            instance_shot_2->~Shot_Enemy();
            instance_shot_3->~Shot_Enemy();

            instance_shot_1->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
            instance_shot_1->sprite().set_visible(true);
            ntt_shots.push_back(instance_shot_1);
            //direção do player
            instance_shot_1->pre_direction = GLOBALS::global_player->pos();
            BN_LOG("Spawn Shot! ntt_shots index: ", ntt_shots.size()-1);
            break;
        
        default: //E_Shot_Type::E_Shot_Type_1
            instance_shot_2->~Shot_Enemy();
            instance_shot_3->~Shot_Enemy();
            //Shot_Enemy* instance_shot = new Shot_Enemy(_shot.sprite_item(),_pos);

            instance_shot_1->pos(bn::fixed_point(_pos.x()-4, _pos.y()));
            BN_LOG("Position: x:", instance_shot_1->pos().x(), ", y:", instance_shot_1->pos().y());
            instance_shot_1->sprite().set_visible(true);

            ntt_shots.push_back(instance_shot_1);

            BN_LOG("Spawn Shot! ntt_shots index: ", ntt_shots.size()-1);
            break;
        }
        _enemy_state = E_Enemy_State::E_Enemy_State_NONE;
    }

    void Enemy::update_collider()
    {
        if(!wait_to_destroy){
            if (_cols.size()>0)
            {
                //se esperou por x frames, então trocar par o proximo index do _cols 
                //se for depois do ultimo voltar ao primeiro 

                //OBS: Estou adiantando o index da animação pois por algum motivo 
                /////// o index vem atrasado por 1 index em relação a sprite apresentada
                const int cols_index = enemy_anim.current_index()-1<0?_cols.size()-1:enemy_anim.current_index()-1;
                _col = _cols.at(cols_index);
                // BN_LOG("anim_index: ", cols_index);
                // BN_LOG("col width: ", _col.dimensions().width(), " height: ", _col.dimensions().height());
            }
            else
            {
                _col.set_position((int)_pos.x(), (int)_pos.y());
            }
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
        enemy_clone_anim.update();
        
        update_collider();
        
        _sprite.set_position(_pos);
        _sprite_clone.set_position(_pos);

        hit_feedback();

        if(explosion && !explosion->_explosion_anim.done()){
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy){
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
