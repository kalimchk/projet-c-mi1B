#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

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


int is_usine_line(char *line){
    if (line==NULL){
        return 0;
    }
    char *p = line + strlen(line) - 1;
    // supprime \n ou \r à la fin
    while(p >= line && (*p=='\n'||*p=='\r')){
        *p = '\0';
        p--;
    }
    char *copy = my_strdup(line);
    if (copy==NULL){
        return 0;
    }
    char *cols[5]={NULL};
    int i=0;
    char *elt=strtok(copy,";");
    while(elt && i<5){
        cols[i++]=elt;
        elt=strtok(NULL,";");
    }

// Vérifie que cols[1] et cols[3] existent et que cols[3] est un nombre
    if(i<4){
        return 0;
    }
    float tmp;
    free(copy);
    return (sscanf(cols[3],"%f",&tmp)==1);
}

//recupere idd usine + capacite max en m**3
int parse_usine_line(char *line, char **id_usine, float *capacite_Mm3)
{
    if (!line || !id_usine || !capacite_Mm3) {
        return 0;
    }

    char *p = line + strlen(line) - 1;
    while (p >= line && (*p == '\n' || *p == '\r')) {
        *p = '\0';
        p--;
    }

    char *copy = my_strdup(line);
    if (!copy) {
        return 0;
    }

    char *cols[5] = {NULL};
    int i = 0;

    char *elt = strtok(copy, ";");
    while (elt && i < 5) {
        cols[i++] = elt;
        elt = strtok(NULL, ";");
    }

    int ok = 0;
    if (i >= 4) {
        float cap;
        if (sscanf(cols[3], "%f", &cap) == 1) {
            *id_usine = my_strdup(cols[1]);
            if (*id_usine) {
                *capacite_Mm3 = cap / 1000.0f;
                ok = 1;
            }
        }
    }

    free(copy);  
    return ok;
}
