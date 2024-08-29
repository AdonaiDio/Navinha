#pragma once

#include "bn_fixed_point.h"
#include "bn_math.h"
#include "bn_string_view.h"

namespace adonai
{
    extern bn::fixed dot_product(bn::fixed_point a, bn::fixed_point b);

    extern bn::fixed length_sqr(bn::fixed_point a);

    extern bn::fixed length(bn::fixed_point a);

    extern bn::fixed aprox_length(bn::fixed_point a);

    extern bn::fixed_point normalize(bn::fixed_point a);

    extern bn::fixed move_towards(bn::fixed current, bn::fixed target, bn::fixed maxDistanceDelta);

    extern bn::fixed_point move_towards(bn::fixed_point current, bn::fixed_point target, bn::fixed maxDistanceDelta);

    extern bn::fixed move_towards_angle(bn::fixed current, bn::fixed target, bn::fixed maxDistanceDelta);

    // extern int clamp(int i, int min, int max);

    extern bn::fixed clamp(bn::fixed i, bn::fixed min, bn::fixed max);
}