#include "balok.h"


namespace bangun_ruang
{
    double volume_balok(double p, double l, double t)
    {
        return p * l * t;
    }


    double luas_permukaan_balok(double p, double l, double t)
    {
        return 2 * (p * l + p * t + l * t);
    }
}

