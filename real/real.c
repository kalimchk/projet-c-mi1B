#include "real.h"
#include "avl/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run_real(char *input_csv, char *output_file){
    if (input_csv == NULL || output_file == NULL){
        return 1;
    }

    FILE *in = fopen(input_csv, "r");
    if (in == NULL){
        fprintf(stderr, "Erreur ouverture %s\n", input_csv);
        return 2;
    }

    FILE *out = fopen(output_file, "w");
    if (out == NULL){
        fclose(in);
        fprintf(stderr, "Erreur creation %s\n", output_file);
        return 3;
    }

    fprintf(out, "identifier;real_volume(M.m3.year-1)\n");

    avl *a = NULL;
    char line[512];

    while (fgets(line, sizeof(line), in)){
        char *col1 = strtok(line, ";");
        char *col2 = strtok(NULL, ";");
        char *col3 = strtok(NULL, ";");
        char *col4 = strtok(NULL, ";");
        char *col5 = strtok(NULL, ";");

        if (!col1 || !col3 || !col4 || !col5){
            continue;
        }

        if (strcmp(col1, "-") == 0){
            double volume = atof(col4);
            double fuite = atof(col5);
            double real = volume * (1.0 - fuite / 100.0);
            real = real / 1000.0;

            a = avl_insert(a, col3, real);
        }
    }

    avl_reverse_inorder(a, out);
    avl_free(a);

    fclose(in);
    fclose(out);

    return 0;
}