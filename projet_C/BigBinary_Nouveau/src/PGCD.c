#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigBinary.h"

// Copie profonde d'un BigBinary
static BigBinary copyBB(const BigBinary *src) {
    BigBinary out;
    out.Taille = src->Taille;
    out.Signe  = src->Signe;

    out.Tdigits = malloc(sizeof(int) * out.Taille);
    if (!out.Tdigits) {
        fprintf(stderr, "Erreur malloc dans copyBB\n");
        exit(EXIT_FAILURE);
    }
    memcpy(out.Tdigits, src->Tdigits, out.Taille * sizeof(int));

    return out;
}

// PGCD binaire (Stein) sûr : NE MODIFIE PAS les BigBinary originaux
BigBinary pgcd_binaire(BigBinary a, BigBinary b)
{
    // Cas triviaux : on renvoie une COPIE
    if (isZero(&a)) return copyBB(&b);
    if (isZero(&b)) return copyBB(&a);

    // On travaille sur des copies locales A et B
    BigBinary A = copyBB(&a);
    BigBinary B = copyBB(&b);

    // 1) Extraire le facteur 2 commun
    int k = 0;
    while (isEven(&A) && isEven(&B)) {
        shiftRight1(&A);
        shiftRight1(&B);
        k++;
    }

    // 2) Rendre A impair
    while (isEven(&A) && !isZero(&A)) {
        shiftRight1(&A);
    }

    // 3) Boucle principale
    while (!isZero(&B)) {

        // Rendre B impair
        while (isEven(&B) && !isZero(&B)) {
            shiftRight1(&B);
        }

        // Ordonner A ≤ B
        if (compareAbs(&A, &B) > 0) {
            BigBinary tmp = A;  // ici c'est safe : A et B sont des BigBinary indépendants
            A = B;
            B = tmp;
        }

        // B ← B - A
        subAbs(&B, &A);
        normalize(&B);
    }

    // 4) À ce stade : B == 0, A contient le PGCD impair
    //    On peut libérer B (copie locale seulement, pas l'original)
    libereBigBinary(&B);

    // 5) Restaurer le facteur 2^k
    while (k-- > 0) {
        shiftLeft1(&A);
    }

    normalize(&A);
    // A est le PGCD, avec sa propre allocation
    return A;
}




