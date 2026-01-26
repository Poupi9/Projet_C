#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigBinary.h"
#define BASE 2  // La base du nombre (2 pour binaire)


// Initialisation manuelle d’un BigBinary vide (tout est à zéro)
BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; ++i) {
        nb.Tdigits[i] = 0;
    }
    return nb;
}

// Affichage du nombre binaire
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf("-");
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);
    }
    printf("\n");
}

// Division par 2
void divisePar2(BigBinary *nb) {
    if (nb->Signe == 0 || nb->Taille == 0) {
        return;
    }
    nb->Taille--;
    if (nb->Taille == 0) {
        nb->Taille = 1;
        nb->Tdigits[0] = 0;
        nb->Signe = 0;
    }
}

// Libération de la mémoire
void libereBigBinary(BigBinary *nb) {
    if (!nb) return;
    if (nb->Tdigits) {
        free(nb->Tdigits);
        nb->Tdigits = NULL;
    }
    nb->Taille = 0;
    nb->Signe  = 0;
}





// Représentation unique du zéro => Taille=1, bit 0, Signe=0
static void BB_setZero(BigBinary *nb) {
    if (!nb) return;
    // initialisation : libère l’ancien
    free(nb->Tdigits);
    nb->Tdigits = (int*)malloc(sizeof(int));
    if (!nb->Tdigits) { fprintf(stderr, "malloc a échoué\n"); exit(1); }
    nb->Tdigits[0] = 0;
    nb->Taille = 1;
    nb->Signe  = 0;
}

// supprime les zéros en tête (MSB) et fixe le signe
// zéro si que des zéro
void normalize(BigBinary *nb) {
    if (!nb) return;

    // chercher l'indice du premier 1 en partant de la gauche
    int first_one = -1;
    for (int i = 0; i < nb->Taille; ++i) {
        if (nb->Tdigits[i] == 1) { first_one = i; break; }
    }

    // si aucun 1 trouvé => le nombre est zéro
    if (first_one == -1) {
        BB_setZero(nb);
        return;
    }

    // si le premier bit utile est déjà à l'indice 0, c'est normalisé
    if (first_one == 0) {
        nb->Signe = +1;
        return;
    }

    // sinon on “coupe” les zéros en tête => on recopie dans un nouveau buffer
    int new_size = nb->Taille - first_one;
    int *newT = (int*)malloc(sizeof(int) * new_size);
    if (!newT) { fprintf(stderr, "malloc a échoué\n"); exit(1); }

    for (int i = 0; i < new_size; ++i) {
        newT[i] = nb->Tdigits[first_one + i];
    }

    free(nb->Tdigits);
    nb->Tdigits = newT;
    nb->Taille  = new_size;
    nb->Signe   = +1;
}




// construit un BigBinary à partir d'une chaîne (0001011").
// Règles : on garde seulement '0' et '1', puis on normalise (supprime les zéros en tête).
// Cas "tout zéros" ou chaîne sans 0/1 -> retourne le zéro (Taille=1, bit 0, Signe=0).
BigBinary FromString(const char *s) {
    // Sécurité : si s == NULL, on retourne le zéro
    if (s == NULL) {
        BigBinary z = initBigBinary(1, 0);
        z.Tdigits[0] = 0;
        return z;
    }

    size_t n = strlen(s);

    // 1) Compter les caractères valides (0 et 1) pour connaître la taille
    int count01 = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '0' || s[i] == '1') {
            count01++;
        }
    }

    // 2) Si la chaîne ne contient aucun 0/1 -> zéro
    if (count01 == 0) {
        BigBinary z = initBigBinary(1, 0);
        z.Tdigits[0] = 0;
        return z;
    }

    // 3) allouer un BigBinary de cette taille
    BigBinary x = initBigBinary(count01, +1);

    // 4) Copier les bits valides dans l'ordre
    int k = 0;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '0' || s[i] == '1') {
            x.Tdigits[k++] = (s[i] == '1') ? 1 : 0;
        }
    }

    // 5) Enlever les zéros en tête + gérer le cas tout-zéro
    normalize(&x);

    return x; // penser à libérer plus tard avec libereBigBinary(&x)
}


//fonction de comparaison
//retourne 1 si A == B, sinon 0

int Egal(BigBinary A, BigBinary B) {
    if (A.Signe == 0 && B.Signe == 0) return 1;
    if (A.Signe != B.Signe) return 0;
    if (A.Taille != B.Taille) return 0;
    for (int i = 0 ; i < A.Taille; ++i) {
        if (A.Tdigits[i] != B.Tdigits[i]) return 0;
    }
    return 1;
}

// Retourne 1 si A < B, sinon 0
int Inferieur(BigBinary A, BigBinary B) {
    // Égalité → A n'est pas < B
    if (Egal(A, B)) return 0;

    // Gestion des signes (en phase 1 : 0 ou +1)
    if (A.Signe == 0 && B.Signe == +1) return 1; // 0 < positif
    if (A.Signe == +1 && B.Signe == 0) return 0; // positif !< 0

    // Les deux sont positifs (ou déjà normalisés)
    // Tailles différentes → celui qui a le moins de bits est plus petit
    if (A.Taille != B.Taille) {
        return (A.Taille < B.Taille) ? 1 : 0;
    }

    // Même taille → comparer bit par bit (MSB -> LSB)
    for (int i = 0; i < A.Taille; ++i) {
        if (A.Tdigits[i] < B.Tdigits[i]) return 1;
        if (A.Tdigits[i] > B.Tdigits[i]) return 0;
        // sinon, bits égaux → on continue
    }
    // Si on arrive ici, ils sont égaux (mais on l'a déjà filtré)
    return 0;
}




// Addition naïve de deux BigBinary non négatifs (Signe 0 ou +1).
// Hypothèse: A et B sont normalisés (pas de zéros en tête).
// Résultat: nouveau BigBinary alloué -> à libérer avec libereBigBinary().
BigBinary add(BigBinary A, BigBinary B) {
    // Sécurité minimale Phase 1 : on ne gère pas les négatifs ici
    if (A.Signe < 0 || B.Signe < 0) {
        fprintf(stderr, "BB_add: nombres négatifs non gérés en phase 1\n");
        BigBinary z = initBigBinary(1, 0); // permet de renvoyer 0
        z.Tdigits[0] = 0;
        return z;
    }

    // Taille max + 1 pour la retenue finale éventuelle
    int nA = A.Taille;
    int nB = B.Taille;
    int nR = (nA > nB ? nA : nB) + 1;

    BigBinary R = initBigBinary(nR, +1);

    int i = nA - 1;         // index LSB de A
    int j = nB - 1;         // index LSB de B
    int k = nR - 1;         // index LSB du résultat
    int carry = 0;          // retenue (0 ou 1)

    // Parcours de droite à gauche (LSB -> MSB)
    while (k >= 0) {
        int a = (i >= 0) ? A.Tdigits[i] : 0;
        int b = (j >= 0) ? B.Tdigits[j] : 0;
        int sum = a + b + carry;

        R.Tdigits[k] = (sum & 1);   // bit résultat = sum % 2
        carry = (sum >> 1);         // nouvelle retenue = sum / 2 (en binaire, 0 ou 1)

        i--; j--; k--;
    }

    // Nettoyage des zéros en tête + signe correct
    normalize(&R);
    return R;
}


// Soustraction naïve de deux BigBinary positifs (A ≥ B).
// Hypothèse : A et B sont normalisés (pas de zéros en tête).
// Résultat : nouveau BigBinary alloué -> à libérer avec libereBigBinary().
BigBinary sub(BigBinary A, BigBinary B) {
    // Vérifie la précondition (A >= B)
    if (Inferieur(A, B)) {
        fprintf(stderr, "Erreur: BB_sub appelé avec A < B (non géré en Phase 1)\n");
        BigBinary z = initBigBinary(1, 0);
        z.Tdigits[0] = 0;
        return z;
    }

    int nA = A.Taille;
    int nB = B.Taille;
    int nR = nA; // taille du résultat = taille de A

    BigBinary R = initBigBinary(nR, +1);

    int i = nA - 1; // LSB de A
    int j = nB - 1; // LSB de B
    int k = nR - 1; // LSB du résultat

    int borrow = 0; // emprunt

    // Parcours de droite à gauche (LSB → MSB)
    while (k >= 0) {
        int a = (i >= 0) ? A.Tdigits[i] : 0;
        int b = (j >= 0) ? B.Tdigits[j] : 0;

        // on soustrait le bit + emprunt
        int diff = a - b - borrow;

        if (diff < 0) {
            diff += 2;  // emprunt d’un 1 => ajoute 2
            borrow = 1; // on garde un emprunt pour le prochain bit
        } else {
            borrow = 0; // pas d’emprunt
        }

        R.Tdigits[k] = diff;

        i--;
        j--;
        k--;
    }

    // Normalisation (enlève zéros en tête, gère le cas "0")
    normalize(&R);
    return R;
}
