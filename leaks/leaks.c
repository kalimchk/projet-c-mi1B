#include "leaks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parsing/parser.h"

// run_leaks : calcule les fuites d'une usine et écrit le résultat dans leaks.dat
int run_leaks(char *input_csv, char *factory_id) {
    if (input_csv == NULL || factory_id == NULL){
        return 1;
    }

    FILE *in = fopen(input_csv, "r");
    if (in==NULL) {
        fprintf(stderr, "Erreur ouverture %s\n", input_csv);
        return 2;
    }

    char line[512];
    double total_leaks = 0.0;
    int found = 0;

    while (fgets(line, sizeof(line), in)) {
        if (is_usine_line(line)) { // ignore les lignes invalides
            char *id_usine = NULL;
            float volume_Mm3 = 0;

            if (parse_usine_line(line, &id_usine, &volume_Mm3)) {
                // compare l'ID de l'usine
                if (strcmp(id_usine, factory_id) == 0) {
                    found = 1;

                    // récupérer la colonne fuite (colonne 5)
                    char *copy = strdup(line);
                    if (copy) {
                        char *tmp = strtok(copy, ";"); // col1
                        for (int i = 0; i < 4; i++){
                            tmp = strtok(NULL, ";");  // col5 = tmp
                        }if (tmp) {
                            double fuite = atof(tmp);
                            total_leaks += volume_Mm3 * fuite; // volume déjà en Mm³
                        }
                        free(copy);
                    }
                }
                free(id_usine);
            }
        }
    }

    fclose(in);

    if (found==0){
        return -1;
    }
    // écrire le résultat
    FILE *out = fopen("leaks.dat", "a");
    if (out) {
        fprintf(out, "%s;%.3f\n", factory_id, total_leaks);
        fclose(out);
    }

    return 0;
}