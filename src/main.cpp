//butano
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"

#include "bn_log.h"

//assets
//#include "bn_sprite_items_nova.h"
#include "bn_sprite_items_shoot.h"

//my code
#include "player.h"
#include "scene.h"
#include "scene_stage_1.h"
#include "scene_test.h"
#include "scene_logo_studio.h"

#include "ntt_list_stage_1.h"

#include "shot.h"

int main()
{
    bn::core::init();

    //Inicar o player no main para o player sempre ser o mesmo durante o jogo.
    adonai::Player player = adonai::Player( bn::sprite_items::nova,
                                            bn::fixed_point(0, 0), 
                                            bn::sprite_items::shoot );
                                            
    player.sprite().set_visible(false);
    //guardar referencia global
    adonai::GLOBALS::global_player = &player;
    // inciar a primeira cena
    adonai::Scene scene = adonai::Scene::STAGE_1;

    while(true)
    {
        // se o enum for stage_1 então criamos uma instancia da cena stage_1.
        // passamos para a cena atual(scene) a instancia de cena criada.
        if(scene == adonai::Scene::TEST_SCENE){
            adonai::Test test_scene = adonai::Test(player);
            scene = test_scene.execute(bn::fixed_point(-104,0));
        }
        else if(scene == adonai::Scene::STAGE_1){
            adonai::Stage_1 stage_1 = adonai::Stage_1(player);
            scene = stage_1.execute(bn::fixed_point(-104,0));
        }
        else if(scene == adonai::Scene::LOGO_STUDIO){
            adonai::Logo_Studio logo_studio = adonai::Logo_Studio();
            scene = logo_studio.execute();
        }
        
        bn::core::update();
    }

}

