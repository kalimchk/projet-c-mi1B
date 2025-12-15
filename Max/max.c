#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//determine si c'est une usine seul

int is_usine_line(char *line){
    if(line==NULL){
        return 0;
    }

    char *copy=strdup(line);
    if(copy==NULL){
        return 0;
    }
    char *elt;
    int i=0;

    char *cols[5]={NULL};

    elt =strtok(copy, ";"); //decoupage simple sur ;
    while(elt!=NULL && i<5){
        cols[i++]=elt;
        elt=strtok(NULL, ";");
    }
    if(i<5){
        free(copy);
        return 0;
    }

    int result= strcmp(cols[1],"-")!=0 && strcmp(cols[2],"-")==0 && strcmp(cols[3],"-")!=0 && strcmp(cols[4],"-\n")==0;
    free(copy);
    return result;

}

//idd usine + capacite max en m**3
int parse_usine_line(char *line, char **id_usine, double *capacite_Mm3){

    char *copy=strdup(line);
    if(copy==NULL){
        return 0;
    }
    char *elt;
    int i=0;

    if(line==NULL || id_usine==NULL || capacite_Mm3==NULL){
        return 0;
    }

    char *cols[5]={NULL};

    elt =strtok(copy, ";"); 

    while(elt!=NULL && i<5){
        cols[i++]=elt;
        elt=strtok(NULL, ";");
    }
    if(i<5){
        free(copy);
        return 0;
    }

    //copie de l'idd
    *id_usine=malloc(strlen(cols[1])+1);
    if(id_usine==NULL){
        free(copy);
        return 0;
    }
    strcpy(*id_usine,cols[1]);

    //convertion en volume
    double capacite_Km3;
    if(sscanf(cols[3],"%lf",&capacite_Km3)!=1){
        free(copy);
        return 0;
    }
    *capacite_Mm3=capacite_Km3/1000.0;
    return 1;
}