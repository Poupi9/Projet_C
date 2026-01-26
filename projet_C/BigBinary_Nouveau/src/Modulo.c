
#include <stdlib.h>
#include "Bigbinary.h"

// Copie profonde
static BigBinary bb_copy(const BigBinary *src)
{
    if (src == NULL || src->Tdigits == NULL || src->Taille <= 0) {
        return FromString("0");
    }

    BigBinary c = initBigBinary(src->Taille, src->Signe);
    for (int i = 0; i < src->Taille; ++i)
        c.Tdigits[i] = src->Tdigits[i];

    normalize(&c);
    return c;
}

// ------------------------------------------------------------
//       R = A mod B  (A,B ≥ 0)
// ------------------------------------------------------------
BigBinary bb_mod(const BigBinary *A, const BigBinary *B)
{
    if (A == NULL || isZero(A))
        return FromString("0");

    if (B == NULL || isZero(B))
        return bb_copy(A);

    // Si |A| < |B| → reste = copie(A)
    if (compareAbs(A, B) < 0)
        return bb_copy(A);

    BigBinary R = bb_copy(A);
    BigBinary Bnorm = bb_copy(B);

    normalize(&R);
    normalize(&Bnorm);

    while (!isZero(&R) && compareAbs(&R, &Bnorm) >= 0)
    {
        int shift = R.Taille - Bnorm.Taille;
        if (shift < 0) break;

        BigBinary Bshift = bb_copy(&Bnorm);
        shiftLeftK(&Bshift, shift);

        // Si trop grand, on recule d’un cran
        while (compareAbs(&Bshift, &R) > 0 && shift > 0) {
            shiftRight1(&Bshift);
            shift--;
        }

        if (compareAbs(&Bshift, &R) > 0) {
            libereBigBinary(&Bshift);
            break;
        }

        subAbs(&R, &Bshift);
        libereBigBinary(&Bshift);
    }

    libereBigBinary(&Bnorm);
    normalize(&R);
    return R;
}
