#include "leaks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_leaks(char *input_csv, char *factory_id){
    if (input_csv == NULL || factory_id == NULL){
        return 1;
    }

    FILE *in = fopen(input_csv, "r");
    if (in == NULL){
        fprintf(stderr, "Erreur ouverture %s\n", input_csv);
        return 2;
    }

    double total_leaks = 0.0;
    int found = 0;
    char line[512];

    while (fgets(line, sizeof(line), in)){
        char *col1 = strtok(line, ";");
        char *col2 = strtok(NULL, ";");
        char *col3 = strtok(NULL, ";");
        char *col4 = strtok(NULL, ";");
        char *col5 = strtok(NULL, ";");

        if (!col1 || !col5){
            continue;
        }

        if (strcmp(col1, factory_id) == 0){
            found = 1;

            if (col4 && strcmp(col4, "-") != 0){
                double volume = atof(col4);
                double fuite = atof(col5);
                total_leaks += volume * fuite / 100.0;
            }
        }
    }

    fclose(in);

    if (!found){
        return -1;
    }

    total_leaks = total_leaks / 1000.0;

    FILE *f = fopen("leaks.dat", "a");
    if (f != NULL){
        fprintf(f, "%s;%.3f\n", factory_id, total_leaks);
        fclose(f);
    }

    return 0;
}