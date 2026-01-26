# BigBinary – Manipulation de Grands Entiers en C

Badges à ajouter ici (build, license, language…)

---

## Description

Implémentation d’une bibliothèque en C permettant la manipulation d’entiers binaires en **précision arbitraire** : addition, soustraction, comparaisons, PGCD binaire, modulo, exponentiation modulaire et RSA simplifié.


Les entiers standards du langage C ne permettent pas de représenter correctement des valeurs dépassant 64 bits.
Ce projet introduit une structure dédiée, BigBinary, permettant de gérer des entiers de taille arbitraire, avec :
* stockage bit par bit (Tdigits)
* indication du signe (Signe)
* gestion dynamique de la taille (Taille)

Il s’agit d'une implémentation pédagogique conduisant progressivement vers des algorithmes fondamentaux de la cryptographie.

Le projet suit les trois phases définies dans le sujet officiel .

---

## Pour commencer

Clonez le dépôt puis compilez avec `make` ou via votre IDE.

### Pré-requis

* Un compilateur C (GCC / Clang)
* `<stdlib.h>`, `<stdio.h>`, `<stdbool.h>`
* Connaissance de la structure `BigBinary` (Tdigits, Taille, Signe) 

---

## Démarrage

Pour exécuter les tests :

```bash
./bigbinary
```

Le programme lit les données, applique les opérations (addition, soustraction, PGCD, modulo, exp. modulaire) puis affiche les résultats au format demandé dans les fichiers de test.

---

## Fonctionnalités

### Phase 1 – Opérations de base

* Représentation d’un entier binaire dynamique
* Initialisation (vide ou depuis chaîne)
* Affichage
* Addition (algorithme naïf)
* Soustraction (A ≥ B)
* Comparaisons : `Egal(A,B)`, `Inferieur(A,B)`

### Phase 2 – Fonctionnalités avancées

* PGCD via l’algorithme binaire d’Euclide
* Calcul du modulo
* Multiplication Égyptienne
* Exponentiation modulaire rapide (exposant < 64 bits)
---

## Fabriqué avec

* **C**
* **Make** — automatisation de compilation
* **VSCode / CLion** — IDE

---

## Auteurs

* Geoffrey PREVOT
* Paul-Joseph Yamben
