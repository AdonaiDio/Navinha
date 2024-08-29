#include "bn_sprite_palette_ptr.h"
#include "bn_colors.h"
#include "bn_sound_items.h"

#include "utility.h"

#include "bn_sprite_palette_items_feedback_palette.h"
#include "bn_sprite_items_nova_shadow_rgb.h"

#include "player.h"


namespace adonai
{
    Player::Player(bn::sprite_item sprite_item, bn::fixed x, bn::fixed y, bn::sprite_item shot_sprite_item) : 
        _sprite(sprite_item.create_sprite(x,y)),
        _sprite_clone(sprite_item.create_sprite(x,y)),
        shadow_sprites({
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,0),
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,1),
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,2)
        }),
        _pos(x,y),
        _propulsion_sprite(bn::sprite_items::propulsion.create_sprite(0,0,8)),
        _shots({
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0)),
            adonai::Shot_Player(shot_sprite_item, bn::fixed_point(0,0))
        }) 
    {
        shadow_sprites.at(1).set_z_order(1);
        shadow_sprites.at(2).set_z_order(2);
        shadow_sprites.at(0).set_visible(false);
        shadow_sprites.at(1).set_visible(false);
        shadow_sprites.at(2).set_visible(false);

        _sprite_clone.set_z_order(-2);
        _sprite_clone.set_visible(false);
        _sprite_clone.set_palette(bn::sprite_palette_items::feedback_palette);
    }

    void Player::hit_feedback()
    {
        if (hit_feedback_duration > 0)
        {
            //!!! Codigo RUIM. Paleta trocando para todos os tipos de sprite !!!
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
    
    void Player::receive_hit()
    {
        if (_hp <= 0 || hit_feedback_duration > 0) {return;}//assegurar que não vai receber hit se já estiver morto
        _hp -= 1;
        BN_LOG("HP: ",_hp);
        if (_hp > 0) {
            bn::sound_items::hit.play();
            hit_feedback_duration = 120; //frames de duração do hit_feedback
            return;
        }
        wait_to_destroy = true;
        can_act = false;
        explode();
    }

    //Spawn EXPLOSION_FX
    void Player::explode()
    {
        _sprite.set_visible(false);
        _sprite_clone.set_visible(false);
        _propulsion_sprite.set_visible(false);
        explosion = new Explosion_FX(_pos);
    }
    
    
    // TODO: é mesmo necessário?
    void Player::set_shot_sprite(bn::sprite_ptr shoot_sprite)
    {
        for(int i=0; i<_shots.max_size(); i++)
        {
            _shots[i].sprite(shoot_sprite);
        }
    }

    void Player::check_sprites_states()
    {
        if (_movement_states == Player_States::Player_NONE)
        {
            /* code */
        }
        
    }

    void Player::handle_shadows_rgb()
    {
        /// Tentando sumir com as sombras quando elas ficam travadas
        if( Player_States::Player_NONE == _movement_states &&
            shadow_delay <= 0){
            for (int i = 0; i < shadow_sprites.size(); i++)
            {
                if(shadow_sprites.at(i).position().x() <= _pos.x()+_speed ){
                    shadow_sprites.at(i).set_visible(false);
                    shadow_sprites.at(i).set_position(bn::fixed_point(_pos.x(), _pos.y()));
                }
            }
        }
        ///
        if(_movement_states == adonai::Player_States::Player_HOLD_MOVE_LEFT ||
            moved_to_left > 0)
        { 
            if(!is_collapsing_shadow){
                BN_LOG("moved_to_left: ", moved_to_left,", shadow_delay: ", shadow_delay);
            //starta o shadow blue e contagem regresiva do delay
                if(moved_to_left == 0 || (moved_to_left <= _speed && shadow_delay == 0)) {
                    BN_LOG("shadow blue");
                    shadow_sprites.at(2).set_visible(true);
                    shadow_sprites.at(2).set_position(bn::fixed_point(_pos.x()+1, _pos.y()));
                    shadow_delay = 21;
                }
                if(shadow_delay <= 14 && !shadow_sprites.at(1).visible()) {
                    BN_LOG("shadow green");
                    shadow_sprites.at(1).set_visible(true);
                    shadow_sprites.at(1).set_position(bn::fixed_point(_pos.x()+1, _pos.y()));
                }
                if(shadow_delay <= 7 && !shadow_sprites.at(0).visible()){
                    BN_LOG("shadow red");
                    shadow_sprites.at(0).set_visible(true);
                    shadow_sprites.at(0).set_position(bn::fixed_point(_pos.x()+1, _pos.y()));
                }
                //garantir que o clamp mantenha a uma distância maxima e minima
                for (int i = 0; i < shadow_sprites.size(); i++)
                {
                    shadow_sprites.at(i).set_position(
                        bn::fixed_point( bn::clamp(shadow_sprites.at(i).position().x(), _pos.x(), _pos.x()+(i==2? 24 :i==1? 16 : 8)),
                                        bn::clamp(shadow_sprites.at(i).position().y(), _pos.y(), _pos.y()+(i==2? 24 :i==1? 16 : 8)) )
                        );
                }
            }
        }
        if(shadow_delay > 0) shadow_delay--;
        for (int i = 0; i < shadow_sprites.size(); i++)
        {
            if( shadow_delay <= 0 && 
                shadow_sprites.at(i).position() != _pos){
                shadow_sprites.at(i).set_position(
                        move_towards(shadow_sprites.at(i).position(), pos(), 1.1*_speed)
                    );
                if(i==2){
                    is_collapsing_shadow = true;
                }

            }

            if(shadow_sprites.at(i).position() == _pos){
                //defazer-se da shadow
                shadow_sprites.at(i).set_visible(false);
                if(i==2){
                    is_collapsing_shadow = false;
                    moved_to_left = 0;
                }
            }
        }

    }

    void Player::test_collision()
    {
        if(hit_feedback_duration > 0){return;}
        for (int i = 0; i < ntt_enemies.size(); i++)
        {
            //BN_LOG("enemies: ", ntt_enemies.size());
            if ( _col.intersects(ntt_enemies.at(i)->col()))
            {
                BN_LOG("Colidiu!");
                receive_hit();
            }            
        }
    }

    void Player::update_collider()
    {
        if(!wait_to_destroy){
            _col = bn::rect((int)_pos.x(), (int)_pos.y() + 2,
                            13, 7);
        }else{
            _col = bn::rect(-128,-88,0,0);
        }
    }

    //TODO: Update deve ser chamado todo frame.
    void Player::update()
    {
        //reposicionar em relação ao _pos
        update_collider();
        //sprite correction
        _sprite.set_position(_pos);
        _sprite_clone.set_position(_pos);
        
        _propulsion_sprite.set_position(_pos + bn::fixed_point(-16,0));

        hit_feedback();
        test_collision();

        if(explosion && !explosion->_explosion_anim.done()){
            explosion->update();
        }
        if(explosion->_explosion_anim.done() && wait_to_destroy){
            shadow_sprites.at(0).set_visible(false);
            shadow_sprites.at(1).set_visible(false);
            shadow_sprites.at(2).set_visible(false);
            wait_to_destroy = false;
            BN_LOG("EXPRODIU");
            //faça algo
        }

        handle_shadows_rgb();
    }
}