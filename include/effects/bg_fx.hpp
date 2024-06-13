// !!! CUIDADO !!!
// !!! CODIGO COLADO DIRETAMENTE NO ESCOPO !!!
#include "bn_regular_bg_ptr.h"
// criando macro para acessar parametros externos como numa função
#define BG_GRADIENT_FX(_bg) \
bn::regular_bg_ptr* r_bg = &_bg; \
alignas(int) bn::color palette_colors[6]; \
palette_colors[0] = r_bg->palette().colors().at(2); \
palette_colors[1] = r_bg->palette().colors().at(3); \
palette_colors[2] = r_bg->palette().colors().at(4); \
palette_colors[3] = r_bg->palette().colors().at(5); \
palette_colors[4] = r_bg->palette().colors().at(6); \
palette_colors[5] = r_bg->palette().colors().at(7); \
alignas(int) bn::color colors[bn::display::height()]; \
bn::fixed max_blue_dec(16); \
const int amplitude = (bn::display::height() /6)+1; \
int line_count = 0; \
 \
for (int colors_count = 6; colors_count > 0; --colors_count) \
{ \
    for(int j = 0; j < amplitude; j++) \
    { \
        colors[line_count] = palette_colors[colors_count-1]; \
        line_count++; \
    } \
} \
 \
bn::bg_palette_color_hbe_ptr colors_hbe = \
    bn::bg_palette_color_hbe_ptr::create(r_bg->palette(), 1, colors); \

//------------------