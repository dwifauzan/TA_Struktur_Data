#include "lingkaran.h"
#define PI 3.14159f


namespace bangun_datar
{
    float luas_lingkaran(float r)
    {
        return PI * r * r;
    }


    float keliling_lingkaran(float r)
    {
        return 2 * PI * r;
    }
}

