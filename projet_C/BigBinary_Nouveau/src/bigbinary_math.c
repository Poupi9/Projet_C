#include "BigBinary.h"



// Teste si x représente 0
bool isZero(const BigBinary *x) {
    if (x == NULL) {
        return true;
    }

    // Si normalize est toujours appelé après chaque opération,
    // on peut considérer que le zéro a Signe == 0.
    if (x->Signe == 0) {
        return true;
    }

    // Sécurité supplémentaire au cas où :
    if (x->Taille == 0 || x->Tdigits == NULL) {
        return true;
    }

    if (x->Taille == 1 && x->Tdigits[0] == 0) {
        return true;
    }

    return false;
}

// Comparaison en valeur absolue
// < 0 si |a| < |b|
// = 0 si |a| == |b|
// > 0 si |a| > |b|
int compareAbs(const BigBinary *a, const BigBinary *b)
{
    if (a == NULL || isZero(a)) {
        if (b == NULL || isZero(b)) {
            return 0;
        }
        return -1;
    }
    if (b == NULL || isZero(b)) {
        return 1;
    }

    // On part du principe que normalize(a) et normalize(b) ont été appelées

    // Comparer d'abord les tailles
    if (a->Taille < b->Taille) {
        return -1;
    }
    if (a->Taille > b->Taille) {
        return 1;
    }

    // Tailles égales : comparer bit à bit depuis le MSB
    for (int i = 0; i < a->Taille; ++i) {
        int abit = a->Tdigits[i];
        int bbit = b->Tdigits[i];
        if (abit < bbit) {
            return -1;
        } else if (abit > bbit) {
            return 1;
        }
    }

    // Tous les bits identiques
    return 0;
}


// a = |a| - |b|, avec précondition |a| >= |b|
void subAbs(BigBinary *a, const BigBinary *b)
{
    if (a == NULL || b == NULL) {
        return;
    }

    // On suppose que |a| >= |b| (à toi de le garantir avant l'appel)
    // Travail bit à bit du LSB vers le MSB
    int ia = a->Taille - 1;
    int ib = b->Taille - 1;
    int borrow = 0;

    while (ia >= 0) {
        int abit = a->Tdigits[ia];
        int bbit = (ib >= 0) ? b->Tdigits[ib] : 0;

        int diff = abit - bbit - borrow;
        if (diff < 0) {
            diff += 2;     // base 2
            borrow = 1;
        } else {
            borrow = 0;
        }

        a->Tdigits[ia] = diff;

        ia--;
        ib--;
    }

    // Ici, avoir borrow != 0 signifierait que la précondition |a| >= |b| n'était pas respectée

    // Normaliser pour enlever les zéros en tête et mettre Signe à jour
    normalize(a);
}
