#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Modules */
#include "src/src.h"
#include "Max/max.h"
#include "real/real.h"
#include "leaks/leaks.h"

int main(int argc, char *argv[]){
    if (argc < 3) {
        fprintf(stderr,
            "Usage:\n"
            "  %s fichier.dat src|max|real fichier_sortie.dat\n"
            "  %s fichier.dat leaks ID_USINE\n",argv[0], argv[0]);
        return 1;
    }

    char *input = argv[1];
    char *mode  = argv[2];

    /* ---------- MODE SRC ---------- */
    if (strcmp(mode, "src") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Erreur : mode src attend un fichier de sortie\n");
            return 2;
        }
        return run_src(input, argv[3]);
    }

    /* ---------- MODE MAX ---------- */
    if (strcmp(mode, "max") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Erreur : mode max attend un fichier de sortie\n");
            return 3;
        }
        return capacite_max(input, argv[3]);
    }

    /* ---------- MODE REAL ---------- */
    if (strcmp(mode, "real") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Erreur : mode real attend un fichier de sortie\n");
            return 4;
        }
        return run_real(input, argv[3]);
    }

    /* ---------- MODE LEAKS ---------- */
    if (strcmp(mode, "leaks") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Erreur : mode leaks attend un identifiant d'usine\n");
            return 5;
        }
        return run_leaks(input, argv[3]);
    }

    /* ---------- MODE INCONNU ---------- */
    fprintf(stderr, "Erreur : mode inconnu '%s'\n", mode);
    return 6;
}
