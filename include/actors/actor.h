#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"
#include "bn_rect.h"
#include "bn_sprite_ptr.h"

namespace adonai
{
    class actor
    {
        public:

            // //TENTANDO NOVO MOVE TO
            // //move_to recebe uma posição que será alterada entre dois pontos constantes(durante a operação)
            // //e retorna o valor da nova posição. Ocorre durante o Update.
            // //
            // //target_point : a posição a ser alterada.
            // //point_a : posição de partida. Não usar a posição do alvo a ser movido. Usar constantes.
            // //point_b : posição de chegada. Não usar a posição do alvo a ser movido. Usar constantes.
            // bn::fixed_point move_to(bn::fixed_point target_point, const bn::fixed_point point_a, const bn::fixed_point point_b)
            // {
            //     // vec2 atob = b-a;
            //     // vec2 atobDir = atob.normalized; 'normalize' => atobDir = vec2( (atob.x/length), (atob.y/length) )
            //     // //lenght -> raiz quadrada de (x^2) + (y^2) //ou bn::sqrt((x*x)+(y*y))
            //     // vec2 offsetVec = atobDir*offset(ou velocity ou time ou time*velocity) // o offset é aonde varia para mudar a posição
            //     // vec2 currentPos = a + offsetVec;
            //     ;
            // }
        
            virtual void update();
        private:

        protected:
            actor();// = default;

            bn::sprite_ptr _sprite;
            bn::fixed_point _pos;
            bn::rect _col = bn::rect( 0, 0, 0, 0 );
    };
}
