#include "bn_sprite_palette_ptr.h"
#include "bn_colors.h"

#include "bn_sprite_palette_items_feedback_palette.h"
#include "bn_sprite_items_nova_shadow_rgb.h"

#include "player.h"


namespace adonai
{
    Player::Player(bn::sprite_item sprite_item, bn::fixed x, bn::fixed y, bn::sprite_item shoot_sprite_item) : 
        _sprite(sprite_item.create_sprite(x,y)),
        _sprite_clone(sprite_item.create_sprite(x,y)),
        shadow_sprites({
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,0),
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,1),
            bn::sprite_items::nova_shadow_rgb.create_sprite(x,y,2)
        }),
        _pos(x,y),
        _propulsion_sprite(bn::sprite_items::propulsion.create_sprite(0,0,8)),
        _shoots({
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag),
            adonai::Shoot(shoot_sprite_item, bn::fixed_point(0,0), adonai::Direction::Right, _tag)
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
    void Player::set_shoot_sprite(bn::sprite_ptr shoot_sprite)
    {
        for(int i=0; i<_shoots.max_size(); i++)
        {
            _shoots[i].set_sprite(shoot_sprite);
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
                        bn::fixed_point( clamp(shadow_sprites.at(i).position().x(), _pos.x(), _pos.x()+(i==2? 24 :i==1? 16 : 8)),
                                        clamp(shadow_sprites.at(i).position().y(), _pos.y(), _pos.y()+(i==2? 24 :i==1? 16 : 8)) )
                        );
                }
            }
        }
        if(shadow_delay > 0) shadow_delay--;
        // if( shadow_delay <= 0 && 
        //     shadow_sprites.at(2).position() != _pos){
        //     shadow_sprites.at(2).set_position(
        //             translate_pos_to(shadow_sprites.at(2).position(), _pos)
        //         );
        //     shadow_sprites.at(1).set_position(
        //             translate_pos_to(shadow_sprites.at(1).position(), _pos)
        //         );
        //     shadow_sprites.at(0).set_position(
        //             translate_pos_to(shadow_sprites.at(0).position(), _pos)
        //         );
        //     is_collapsing_shadow = true;
        // }
        for (int i = 0; i < shadow_sprites.size(); i++)
        {
            if( shadow_delay <= 0 && 
                shadow_sprites.at(i).position() != _pos){
                shadow_sprites.at(i).set_position(
                        translate_pos_to(shadow_sprites.at(i).position(), _pos)
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
        
        // if(shadow_sprites.at(2).position() == _pos){
        //     //defazer-se da shadow
        //     shadow_sprites.at(2).set_visible(false);
        //     is_collapsing_shadow = false;
        // }
        // if(shadow_sprites.at(1).position() == _pos){
        //     //defazer-se da shadow
        //     shadow_sprites.at(1).set_visible(false);
        // }
        // if(shadow_sprites.at(0).position() == _pos){
        //     //defazer-se da shadow
        //     shadow_sprites.at(0).set_visible(false);
        // }

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

    int Player::dir(bn::fixed this_axis, bn::fixed target_axis) {
        if(this_axis > target_axis){
            return -1;
        }
        else if(this_axis < target_axis){
            return 1;
        }
        return 0;
    };

    //funciona apenas no Update()
    bn::fixed_point Player::translate_pos_to(bn::fixed_point owner_pos, const bn::fixed_point& target_pos)
    {
        const bn::array<bn::fixed, 2> vector_pos_magnetude = {
            (target_pos.x() - owner_pos.x()>0)?target_pos.x() - owner_pos.x():-(target_pos.x() - owner_pos.x()),
            (target_pos.y() - owner_pos.y()>0)?target_pos.y() - owner_pos.y():-(target_pos.y() - owner_pos.y())};
        
        const int x_dir = dir(owner_pos.x(), target_pos.x());
        const int y_dir = dir(owner_pos.y(), target_pos.y());
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
        return bn::fixed_point ( owner_pos.x() + (x_dir*mx*_speed).round_integer(), 
                                owner_pos.y() + (y_dir*my*_speed).round_integer());
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
        // shadow_sprites.at(0).set_position(bn::fixed_point(_pos.x()+8,_pos.y()));
        // shadow_sprites.at(1).set_position(bn::fixed_point(_pos.x()+16,_pos.y()));
        // shadow_sprites.at(2).set_position(bn::fixed_point(_pos.x()+24,_pos.y()));
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