// #include <bn_core.h>
// #include "bn_display.h"
// #include "bn_colors.h"
// #include "bn_fixed.h"
// #include "bn_bg_palette_ptr.h"

// #include "bg_fx.h"

// namespace adonai
// {
//     bn::span<bn::color> Bg_FX::bg_palette_hbe( bn::regular_bg_ptr r_bg )
//     {
//         //cores da paleta do bg
//         alignas(int) bn::color colors_bg_palette[5];
//         colors_bg_palette[0] = r_bg.palette().colors().at(1);
        
//         colors_bg_palette[1] = r_bg.palette().colors().at(2);
        
//         colors_bg_palette[2] = r_bg.palette().colors().at(3);
        
//         colors_bg_palette[3] = r_bg.palette().colors().at(4);
        
//         colors_bg_palette[4] = r_bg.palette().colors().at(5);
        

//         alignas(int) bn::color colors[bn::display::height()]; //cores de todas as linhas na tela
//         bn::fixed max_blue_dec(16);
        
//         // opera na metade do tempo de H-Blank pois vai espelhar as cores do meio da tela para
//         // as laterais. Vamos dividir a tela em 5 seções, 
//         int line_count = 0;
//         for (int i = 1, colors_count = 5; i <= colors_count; ++i)
//         {
//             for(int j = 0, amplitude = 32; j < amplitude; j++)
//             {
//                 colors[line_count] = colors_bg_palette[i];
//                 line_count++;
//             }
//         }

//         return colors;
//     }
// }