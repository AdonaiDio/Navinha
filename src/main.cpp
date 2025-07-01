//butano
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"

#include "bn_log.h"

//assets
//#include "bn_sprite_items_nova.h"
#include "bn_sprite_items_gizmos_16x16.h"
#include "bn_sprite_items_shoot.h"

//my code
#include "globals.h"
#include "player.h"
#include "scene.h"
#include "scenes/scene_stage_1.cpp"
#include "scenes/scene_stage_1_boss.cpp"
#include "scenes/scene_test.cpp"
#include "scene_logo_studio.h"
#include "bn_display.h"

#include "shot.h"

int main()
{
    bn::core::init();
    
            BN_LOG("NONE-> Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
    //Inicar o player no main para o player sempre ser o mesmo durante o jogo.
    static adonai::Player player = adonai::Player( bn::sprite_items::nova,
                                            bn::fixed_point(120+16, 80+16), 
                                            bn::sprite_items::shoot );
                                            
            BN_LOG("Player-> Usados: ", bn::sprites::used_items_count());
            BN_LOG("Disponíveis: ", bn::sprites::available_items_count());
            BN_LOG("reservados: ", bn::sprites::reserved_handles_count());
    player.sprite().set_visible(false);
    //guardar referencia global
    adonai::GLOBALS::global_player = &player;
    // inciar a primeira cena
    adonai::Scene scene = adonai::Scene::STAGE_1_BOSS;

    while(true)
    {
        // se o enum for stage_1 então criamos uma instancia da cena stage_1.
        // passamos para a cena atual(scene) a instancia de cena criada.
        if(scene == adonai::Scene::TEST_SCENE){
            adonai::Test test_scene = adonai::Test();
            scene = test_scene.execute(bn::fixed_point(-104,0));
        }
        else if(scene == adonai::Scene::STAGE_1){
            adonai::Stage_1 stage_1 = adonai::Stage_1();
            scene = stage_1.execute(bn::fixed_point(-48,-11));
        }
        else if(scene == adonai::Scene::STAGE_1_BOSS){
            adonai::Stage_1_Boss stage_1_boss = adonai::Stage_1_Boss();
            scene = stage_1_boss.execute(bn::fixed_point(player.pos().x(),player.pos().y()));
        }
        else if(scene == adonai::Scene::LOGO_STUDIO){
            adonai::Logo_Studio logo_studio = adonai::Logo_Studio();
            scene = logo_studio.execute();
        }
        bn::core::update();
    }

}

