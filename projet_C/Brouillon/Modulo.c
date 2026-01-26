#include <stdio.h>
#include <stdlib.h>
#include "BigBinary.h"

void bb_mod(const BigBinary *A, const BigBinary *B, BigBinary **out) {
    if (bb_is_zero(B)) {
        fprintf(stderr, "Erreur: division par zero dans bb_mod\n");
        exit(1);
    }

    // Si A < B → le reste est A
    if (bb_cmp(A, B) < 0) {
        *out = bb_clone(A);
        return;
    }

    BigBinary *R = bb_clone(A);
    BigBinary *Bn = bb_clone(B);

    // Calcul du décalage initial (aligner MSB de B sur celui de A)
    size_t shift = (R->nbits > Bn->nbits) ? (R->nbits - Bn->nbits) : 0;
    for (size_t i = 0; i < shift; i++)
        bb_lshift1(Bn); // Bn = B << shift

    // Division longue
    while (bb_cmp(R, B) >= 0) {
        if (bb_cmp(Bn, R) > 0) {
            bb_rshift1(Bn); // trop grand, on recule d’un cran
            if (shift > 0) shift--;
        } else {
            BigBinary *tmp = NULL;
            bb_sub(R, Bn, &tmp); // R = R - Bn
            bb_free(R);
            R = tmp;
        }
    }

    bb_normalize(R);
    *out = R;
    bb_free(Bn);
}
