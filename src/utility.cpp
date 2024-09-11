#include "..\include\utility.h"

namespace adonai
{
    bn::fixed dot_product(bn::fixed_point point_a, bn::fixed_point point_b)
    {
        return (point_a.x() * point_b.x()) + (point_a.y() * point_b.y());
    }

    bn::fixed length_sqr(bn::fixed_point point)
    {
        return (point.x() * point.x()) + (point.y() * point.y());
    }

    bn::fixed length(bn::fixed_point point)
    {
        return bn::sqrt(length_sqr(point));
    }

    bn::fixed aprox_length(bn::fixed_point point)
    {
        return abs(point.x()) + abs(point.y());
    }

    bn::fixed_point normalize(bn::fixed_point point)
    {
        bn::fixed len = length(point);
        if(len == 0)
            return bn::fixed_point(0, 0);
        return point / len;
    }

    // int clamp(int i, int min, int max)
    // {
    //     if(i < min)
    //         return min;
    //     if(i > max)
    //         return max;
    //     return i;
    // }

    // bn::fixed clamp(bn::fixed i, bn::fixed min, bn::fixed max)
    // {
    //     if(i < min)
    //         return min;
    //     if(i > max)
    //         return max;
    //     return i;
    // }

    bn::fixed move_towards(bn::fixed current, bn::fixed target, bn::fixed offset)
    {
        bn::fixed diff = target - current;
        if(abs(diff) <= offset)
        {
            return target;
        }
        else
        {
            if(diff < 0)
            {
                return current - offset;
            }
            else
            {
                return current + offset;
            }
        }
    }

    bn::fixed_point move_towards(bn::fixed_point point_a, bn::fixed_point point_b, bn::fixed offset)
    {
        bn::fixed_point aToB = point_b - point_a; //vec2 aToB = b - a

        bn::fixed lengthSqr = length_sqr(aToB);

        bool reached = lengthSqr == bn::fixed(0) || (offset >= bn::fixed(0) && lengthSqr <= offset * offset);
        if(reached)
        {
            return point_b;
        }
        else
        {
            //para obter apenas a direção normalize o vector2D
            //normalizar = (aToBx/length, aToBy/length)
            bn::fixed_point aToB_dir = normalize(aToB);
            bn::fixed_point offsetVec = aToB_dir * offset;

            //Mover o vetor a partir do ponto inicial 'point_a' em uma quantidade definida por offset
            return bn::fixed_point(point_a + offsetVec);
        }
    }
    bn::fixed_point move_towards_direction(bn::fixed_point point_a, bn::fixed_point point_b, bn::fixed offset)
    {
        bn::fixed_point aToB = point_b - point_a; //vec2 aToB = b - a

        //para obter apenas a direção normalize o vector2D
        //normalizar = (aToBx/length, aToBy/length)
        bn::fixed_point aToB_dir = normalize(aToB);
        bn::fixed_point offsetVec = aToB_dir * offset;

        //Mover o vetor a partir do ponto inicial 'point_a' em uma quantidade definida por offset
        return bn::fixed_point(point_a + offsetVec);
    }
    
    bn::fixed move_towards_angle(bn::fixed current, bn::fixed target, bn::fixed maxDelta)
    {
        bn::fixed total_rotation = target - current;
        while (total_rotation < -180) total_rotation += 360;
        while ( total_rotation >  180) total_rotation -= 360;
        return current + bn::min(maxDelta, bn::max(-maxDelta,total_rotation));
    }

}