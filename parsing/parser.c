#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    char *copy = strdup(line);
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

    free(copy);

// Vérifie que cols[1] et cols[3] existent et que cols[3] est un nombre
    if(i<4){
        return 0;
    }
    float tmp;
    return (sscanf(cols[3],"%f",&tmp)==1);
}

//recupere idd usine + capacite max en m**3
int parse_usine_line(char *line, char **id_usine, float *capacite_Mm3){
    if(line == NULL || id_usine == NULL || capacite_Mm3 == NULL){
        return 0;
    }
    // supprime \n ou \r à la fin
    char *p = line + strlen(line) - 1;
    while(p >= line && (*p == '\n' || *p == '\r')) {
        *p = '\0';
        p--;
    }

    char *copy = strdup(line);
    if(copy == NULL){
        return 0;
    } 

    char *cols[5] = {NULL};
    int i = 0;
    char *elt = strtok(copy, ";");
    while(elt != NULL && i < 5){
        cols[i++] = elt;
        elt = strtok(NULL, ";");
    }
    if(i < 4){
        free(copy);
        return 0;
    }

    *id_usine = strdup(cols[1]);
    if(*id_usine == NULL){
        free(copy);
        return 0;
    }

    float cap;
    if(sscanf(cols[3], "%f", &cap) != 1){
        free(copy);
        free(*id_usine);
        return 0;
    }

    *capacite_Mm3 = cap / 1000.0f;  // conversion km³ → Mm³

    free(copy);
    return 1;
}