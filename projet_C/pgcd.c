#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BigBinary.h"

BigBinary pgcd_binaire(BigBinary a, BigBinary b){

    // 1) Cas triviaux
    if (isZero(&a)) {
        return b;  // copie par valeur
    }
    if (isZero(&b)) {
        return a;
    }

    // 2) Extraire le facteur 2 commun
    int k = 0;
    while (isEven(&a) && isEven(&b)) {
        shiftRight1(&a);
        shiftRight1(&b);
        k++;
    }

    // 3) Rendre A impair
    while (isEven(&a) && !isZero(&a)) {
        shiftRight1(&a);
    }


    // 4) Boucle principale
    while (!isZero(&b)) {
        // Rendre B impair
        while (isEven(&b) && !isZero(&b)) {
            shiftRight1(&b);
        }

        // Ordonner (A ≤ B)
        if (compareAbs(&a, &b) > 0) {
            // swap a et b
            BigBinary tmp = a;
            a = b;
            b = tmp;
        }

        // b ← b − a  (en valeur absolue, avec précondition |b| >= |a|)
        subAbs(&b, &a);
        normalize(&b);  // sécurité : garder représentation propre
    }

    // À ce stade, b == 0, a porte le PGCD "impair"

    // 5) Restaurer le facteur 2^k
    while (k > 0) {
        shiftLeft1(&a);
        k--;
    }

    normalize(&a);
    return a;
}

