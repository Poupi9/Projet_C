cmake_minimum_required(VERSION 3.10)

project(untitled C)

set(CMAKE_C_STANDARD 11)

# IMPORTANT : ajouter le dossier include/
include_directories(include)

add_executable(untitled
        src/Affichage.c
        src/bigbinary_math.c
        src/bigbinary_shift.c
        src/PGCD.c
        src/Modulo.c
        src/bb_expoMod.c
        src/bigbinary_mul.c
        tests/Main.c
)
