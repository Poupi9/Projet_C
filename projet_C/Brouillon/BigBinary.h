#ifndef NOUS_H
#define NOUS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure principale
typedef struct {
    int *Tdigits;
    int Taille;
    int Signe;
} BigBinary;

// Fonctions déclarées dans Affichage.c
void normalize(BigBinary *nb);
void divisePar2(BigBinary *nb);
BigBinary initBigBinary(int taille, int signe);
void afficheBigBinary(BigBinary nb);
void libereBigBinary(BigBinary *nb);
BigBinary FromString(const char *s);
int Egal(BigBinary a, BigBinary b);
int Inferieur(BigBinary a, BigBinary b);
BigBinary add (BigBinary a, BigBinary b);
BigBinary sub(BigBinary a, BigBinary b);

//=====Helper : phase 2:

// Test zéro / parité
bool isZero(const BigBinary *x);
bool isEven(const BigBinary *x);

// Décalages élémentaires
void shiftRight1(BigBinary *x);    // x = x / 2 par décalage
void shiftLeft1(BigBinary *x);     // x = x * 2 par décalage

// Optionnel mais pratique : décalage multiple
void shiftLeftK(BigBinary *x, int k); // utile pour le modulo, à toi de l’implémenter

// Retirer les facteurs 2 : renvoie le nombre de décalages faits
int stripFactorsOfTwo(BigBinary *x);

// Comparaison / soustraction en valeur absolue
int compareAbs(const BigBinary *a, const BigBinary *b);      // <0 si a<b, 0 si =, >0 si a>b
void subAbs(BigBinary *a, const BigBinary *b);               // a = |a| - |b|, précondition |a|>=|b|

/* ========= Phase 2 : Algorithmes ========= */

// PGCD binaire (Stein)
BigBinary pgcd_binaire(BigBinary a, BigBinary b);

// Modulo (A mod B) via décalages + soustractions
BigBinary bb_mod(const BigBinary *A, const BigBinary *B);

// Multiplication naïve (add + shifts)
BigBinary bb_mul(const BigBinary *A, const BigBinary *B);

// Exponentiation modulaire rapide
BigBinary bb_expMod(const BigBinary *M, unsigned long long e, const BigBinary *mod);

#endif
