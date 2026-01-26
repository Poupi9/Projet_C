#include "BigBinary.h"

BigBinary bb_expMod(BigBinary M, unsigned long long e, const BigBinary mod)
{
    // res = 1
    BigBinary res = FromString("1");

    // base = M mod mod
    BigBinary base = bb_mod(&M, &mod);

    while (e > 0) {

        // Si le bit LSB de e vaut 1
        if (e & 1ULL) {
            BigBinary tmp1 = bb_mul(res, base);   // <<< CORRECTION ICI
            libereBigBinary(&res);
            res = bb_mod(&tmp1, &mod);
            libereBigBinary(&tmp1);
        }

        // base = base^2 mod mod
        BigBinary tmp2 = bb_mul(base, base);      // <<< CORRECTION ICI
        libereBigBinary(&base);
        base = bb_mod(&tmp2, &mod);
        libereBigBinary(&tmp2);

        e >>= 1; // décale l'exposant
    }

    normalize(&res);
    libereBigBinary(&base);
    return res;
}
