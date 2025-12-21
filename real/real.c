#include "real.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../avl/avl.h"

/* strdup maison (standard C) */
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

int run_real(char *input_csv, char *output_file)
{
    if (!input_csv || !output_file){
        return 1;
    }

    FILE *in = fopen(input_csv, "r");
    if (!in){
        return 2;
    }
    FILE *out = fopen(output_file, "w");
    if (!out) {
        fclose(in);
        return 3;
    }

    fprintf(out, "identifier;real_volume(M.m3.year-1)\n");

    avl *a = NULL;
    char line[512];

    while (fgets(line, sizeof(line), in)){
        char *copy = my_strdup(line);
        if (!copy){
            continue;
        }
        char *cols[5] = {NULL};
        char *tok = strtok(copy, ";");
        for (int i = 0; i < 5 && tok; i++) {
            cols[i] = tok;
            tok = strtok(NULL, ";");
        }
        if (cols[1] && cols[3] && cols[4] && strcmp(cols[3], "-") != 0 && strcmp(cols[4], "-") != 0){
            double volume = atof(cols[3]);
            double fuite = atof(cols[4]) / 100.0;
            double real = volume * (1.0 - fuite);

            avl *node = avl_find(a, cols[1]);
            if (node){
                node->value += real;
            }
            else{
                a = avl_insert(a, cols[1], real);
            }
        }

        free(copy);
    }

    avl_inorder(a, out, 1);
    avl_free(a);

    fclose(in);
    fclose(out);

    return 0;
}
