//butano
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_fixed_point_fwd.h"


//assets
#include "bn_sprite_items_nova.h"

//my code
#include "scene.h"
#include "scene_stage_1.h"
#include "scene_logo_studio.h"

#include "player.h"

int main()
{
    bn::core::init();
    //Inicar o player no main para o player sempre ser o mesmo durante o jogo.
    bn::sprite_ptr nave_sprite = bn::sprite_items::nova.create_sprite(0, 0);
    adonai::Player player = adonai::Player(nave_sprite);
    player.sprite().set_visible(false);
    // inciar a primeira cena
    adonai::Scene scene = adonai::Scene::LOGO_STUDIO;

    while(true)
    {
        // se o enum for stage_1 então criamos uma instancia da cena stage_1.
        // passamos para a cena atual(scene) a instancia de cena criada.
        if(scene == adonai::Scene::STAGE_1){
            adonai::Stage_1 stage_1 = adonai::Stage_1(player);
            scene = stage_1.execute(bn::fixed_point(0,0));
        }
        else if(scene == adonai::Scene::LOGO_STUDIO){
            adonai::Logo_Studio logo_studio = adonai::Logo_Studio();
            scene = logo_studio.execute();
        }
        
        bn::core::update();
    }

}

