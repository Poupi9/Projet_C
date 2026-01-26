#include <stdio.h>
#include "BigBinary.h"

// Petite fonction utilitaire
void printBB(const char *label, BigBinary x) {
    printf("%s = ", label);
    afficheBigBinary(x);
}

int main(void)
{
    printf("===== TESTS BIGBINARY — PHASE 1 & PHASE 2 =====\n\n");


    // =====================================================================
    // PHASE 1 — ADDITION
    // =====================================================================
    printf("--- PHASE 1 : ADDITION ---\n");

    BigBinary A1 = FromString("10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001");
    BigBinary B1 = FromString("11001011011111111000110000111010000000110101011000000100000010110101101001100011110001011000");

    BigBinary R1 = add(A1, B1);
    printBB("A1 + B1", R1);

    libereBigBinary(&A1);
    libereBigBinary(&B1);
    libereBigBinary(&R1);



    // =====================================================================
    // PHASE 1 — COMPARAISONS
    // =====================================================================
    printf("\n--- PHASE 1 : COMPARAISON ---\n");

    BigBinary A2 = FromString("11001110111000001101101111110100110000001010101010001000000110010010001110000100001110010011");
    BigBinary B2 = FromString("10110100101100011101100011110100101110111100000100111000110000001001000100110110100100110000");
    BigBinary C2 = FromString("11100001000100000000100110010110010010100100111011011100001100000110011101101000101010010000");

    printf("A2 == B2 ? %d\n", Egal(A2, B2));
    printf("A2 > C2 ? %d\n", (compareAbs(&A2, &C2) > 0));

    libereBigBinary(&A2);
    libereBigBinary(&B2);
    libereBigBinary(&C2);



    // =====================================================================
    // PHASE 2 — PGCD BINAIRE
    // =====================================================================
    printf("\n--- PHASE 2 : PGCD BINAIRE ---\n");

    BigBinary PGCD_A = FromString("11110001111000100111100100001010110100110010110000100111001100110010111001010111101101110");
    BigBinary PGCD_B = FromString("11100110011111011000000111111110110001110000011001111100111011011010101110110111000110111");

    BigBinary RES_GCD = pgcd_binaire(PGCD_A, PGCD_B);
    printBB("PGCD(A,B)", RES_GCD);

    libereBigBinary(&PGCD_A);
    libereBigBinary(&PGCD_B);
    libereBigBinary(&RES_GCD);



    // =====================================================================
    // PHASE 2 — MODULO
    // =====================================================================
    printf("\n--- PHASE 2 : MODULO ---\n");

    BigBinary MOD_A = FromString("11001110000111010001010110000101101001111000010001001110011100110100000110000010011011010");
    BigBinary MOD_B = FromString("11001001100000010001111000000101111110010111111011101010001000010100010001111111010011010");

    BigBinary RES_MOD = bb_mod(&MOD_A, &MOD_B);   // par valeur
    printBB("MOD_A mod MOD_B", RES_MOD);

    libereBigBinary(&MOD_A);
    libereBigBinary(&MOD_B);
    libereBigBinary(&RES_MOD);



    // =====================================================================
    // PHASE 2 — EXPONENTIATION MODULAIRE
    // =====================================================================
    printf("\n--- PHASE 2 : EXPONENTIATION MODULAIRE ---\n");

    BigBinary EXP_M = FromString("101100110000001100011011000000110010011101100100101001010111010010001011110110001001101100");
    unsigned long long EXP_EXP = 0b1001001000010111ULL;
    BigBinary EXP_MOD = FromString("101001110001111101100000111000110001110100000111111010001011100101101100101101101011000");

    BigBinary RES_EXP = bb_expMod(EXP_M, EXP_EXP, EXP_MOD);
    printBB("M^e mod mod", RES_EXP);

    libereBigBinary(&EXP_M);
    libereBigBinary(&EXP_MOD);
    libereBigBinary(&RES_EXP);



    printf("\n===== FIN DES TESTS =====\n");
    return 0;
}
