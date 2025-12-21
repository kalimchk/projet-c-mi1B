#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src.h"
#include "../parsing/parser.h"
#include"../avl/avl.h"

// fonction principale
int run_src(char *input_csv, char *output_file)
{
    FILE *in = fopen(input_csv, "r");
    if (in == NULL){
        fprintf(stderr, "Erreur : impossible d'ouvrir %s\n", input_csv);
        return 1;
    }
    FILE *out = fopen(output_file, "w");
    if (out == NULL){
        fclose(in);
        fprintf(stderr, "Erreur : impossible de creer %s\n", output_file);
        return 2;
    }
    fprintf(out, "identifier;source_volume(M.m3.year-1)\n");
    avl *a = NULL;
    char line[512];
    while (fgets(line, sizeof(line), in)){
        char *col1 = strtok(line, ";");
        char *col2 = strtok(NULL, ";");
        char *col3 = strtok(NULL, ";");
        char *col4 = strtok(NULL, ";");

        if (!col1 || !col3 || !col4){
            continue;
        }
        if (strcmp(col1, "-") == 0 && strcmp(col4, "-") != 0){
           
            double volume = atof(col4);
            avl* node = avl_find(a, col3);
            if (node != NULL){
                node->value += volume;
            }
            else{
                a = avl_insert(a, col3, volume);
            }
        }
    }
    avl_inorder(a, out,1);
    avl_free(a);
    fclose(in);
    fclose(out);

    return 0;
}