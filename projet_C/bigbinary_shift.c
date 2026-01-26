
#include "BigBinary.h"

bool isEven(const BigBinary *x)
{
    if (x == NULL) {          // pas "null" : en C c'est NULL
        return false;
    }

    // On considère 0 comme pair
    if (isZero(x)) {
        return true;
    }

    // LSB = Tdigits[Taille - 1]
    int lsb = x->Tdigits[x->Taille - 1];   // [] et pas ()
    return (lsb == 0);                     // ; à la fin
}


// Décale x d'un bit vers la droite (x = x / 2 en binaire)
void shiftRight1(BigBinary *x) {
    if (x == NULL || x->Tdigits == NULL) {
        return;
    }
    // cas 0/2 = 0
    if (x->Signe == 0 || x->Taille <= 1) {
        if (x->Taille >0) {
            x->Tdigits[0] = 0;
            x->Taille = 1;
        }
        x->Signe = 0;
        return;
    }

    //SInon, on perd l'ancienne LSB et recopie Taille-1 vers Taille-2

    for (int i = 0; i<x->Taille; i++) {
        x->Tdigits[i] = x->Tdigits[i+1];
    }

    x->Taille--;

    normalize(x);
}

// Décale x d'un bit vers la gauche (x = x * 2 en binaire)
void shiftLeft1(BigBinary *x) {
    if (x == NULL) {
        return;
    }

    // 0 * 2 = 0
    if (x->Signe == 0 || x->Taille <= 0 || x->Tdigits == NULL) {
        return;
    }

    int newSize = x->Taille + 1;

    int *newDigits = realloc(x->Tdigits, newSize * sizeof(int));
    if (newDigits == NULL) {
        // En cas d'échec de realloc, on ne modifie pas x
        return;
    }

    x->Tdigits = newDigits;
    // Les bits existants restent aux mêmes indices [0..Taille-1]
    // On ajoute un nouveau LSB à 0 à la fin
    x->Tdigits[newSize - 1] = 0;
    x->Taille = newSize;
}

// Décale x de k bits vers la gauche
void shiftLeftK(BigBinary *x, int k) {
    if (x == NULL || k <= 0) {
        return;
    }

    // Version simple : appeler shiftLeft1 k fois
    for (int i = 0; i < k; ++i) {
        shiftLeft1(x);
    }

}

// Retire tous les facteurs 2 de x, renvoie combien il y en avait
int stripFactorsOfTwo(BigBinary *x) {
    if (x == NULL) {
        return 0;
    }

    int count = 0;

    // Tant que x est non nul et pair, on décale
    while (!isZero(x) && isEven(x)) {
        shiftRight1(x);
        count++;
    }

    return count;
}


