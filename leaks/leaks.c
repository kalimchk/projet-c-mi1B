#define _POSIX_C_SOURCE 200809L
#include "leaks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parsing/parser.h"

static char *my_strdup(const char *s){
    if (!s){
        return NULL;
    }
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (!p){
        return NULL;
    }
    memcpy(p, s, len);
    return p;
}

// run_leaks : calcule les fuites d'une usine et écrit le résultat dans leaks.dat
int run_leaks(char *input_csv, char *factory_id) {
    if (!input_csv || !factory_id)
        return 1;

    FILE *in = fopen(input_csv, "r");
    if (!in)
        return 2;

    char line[512];
    double total_leaks_km3 = 0.0;
    double treated_volume_km3 = -1.0;
    int found_usine = 0;
    int found_aval = 0;

    while (fgets(line, sizeof(line), in)) {

        char *copy = my_strdup(line);
        if (!copy)
            continue;

        char *cols[5] = {0};
        char *tok = strtok(copy, ";");
        for (int i = 0; i < 5 && tok; i++) {
            cols[i] = tok;
            tok = strtok(NULL, ";");
        }

        /* Ligne USINE : volume traité MAXIMUM */
        if (cols[1] &&
            strcmp(cols[1], factory_id) == 0 &&
            cols[3] &&
            strcmp(cols[3], "-") != 0)
        {
            treated_volume_km3 = atof(cols[3]);
            found_usine = 1;
        }

        /* Tronçons aval uniquement */
        if (cols[0] &&
            strcmp(cols[0], factory_id) == 0 &&
            cols[4] &&
            strcmp(cols[4], "-") != 0 &&
            treated_volume_km3 > 0)
        {
            double percent = atof(cols[4]) / 100.0;
            total_leaks_km3 += treated_volume_km3 * percent;
            found_aval = 1;
        }

        free(copy);
    }

    fclose(in);

    /* Usine inexistante */
    if (!found_usine){
        return -1;
    }
    /* Usine sans réseau aval */
    if (!found_aval){
        total_leaks_km3 = 0.0;
    }
    double total_leaks_Mm3 = total_leaks_km3 / 1000.0;
    // écrire le résultat
    FILE *out = fopen("leaks.dat", "a");
    if (out) {
        fprintf(out, "%s;%.3f\n", factory_id, total_leaks_Mm3);
        fclose(out);
    }

    return 0;
}