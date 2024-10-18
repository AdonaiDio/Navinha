#include "obj.h"

adonai::Obj::Obj(bn::sprite_item sprite_item) :
    _sprite(sprite_item.create_sprite({0,0}))
{
        BN_LOG("OBJ constructor: FINISHED");
}
