#include "BigBinary.h"
#include <string.h>
#include <stdlib.h>

// Copie profonde
static BigBinary copyBB(const BigBinary *src) {
    BigBinary out;
    out.Taille = src->Taille;
    out.Signe  = src->Signe;

    out.Tdigits = malloc(out.Taille * sizeof(int));
    memcpy(out.Tdigits, src->Tdigits, out.Taille * sizeof(int));

    return out;
}

// Multiplication égyptienne (méthode russe / halving-doubling)
BigBinary bb_mul(const BigBinary A, const BigBinary B)
{
    if (isZero(&A) || isZero(&B)) {
        return FromString("0");
    }

    BigBinary X = copyBB(&A);
    BigBinary Y = copyBB(&B);
    BigBinary result = FromString("0");

    while (!isZero(&Y)) {

        // Si Y impair → on ajoute X au résultat
        if (!isEven(&Y)) {
            BigBinary tmp = add(result, X);
            libereBigBinary(&result);
            result = tmp;
        }

        // X = X * 2 (shift left)
        shiftLeft1(&X);

        // Y = Y / 2 (shift right)
        shiftRight1(&Y);
    }

    // Nettoyage
    libereBigBinary(&X);
    libereBigBinary(&Y);

    normalize(&result);
    return result;
}

