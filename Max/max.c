#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "max.h"

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

//recupere idd usine + capacite max en m**3
int parse_usine_line(char *line, char **id_usine, float *capacite_Mm3){

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
    if(*id_usine==NULL){
        free(copy);
        return 0;
    }
    strcpy(*id_usine,cols[1]);

    //convertion en Mm3
    float capacite_Km3;
    if(sscanf(cols[3],"%f",&capacite_Km3)!=1){
        free(copy);
        free(*id_usine);
        return 0;
    }
    *capacite_Mm3=capacite_Km3/1000.0;
    return 1;
}


//ecrire la premiere ligne du fichier de sortie
void write_header(FILE *f){
    if(f==NULL){
        return;
    }
    fprintf(f,"identifier,max_volume(M.m3)\n");
}



void write_AVL(FILE *f,avl *a){
    if(f==NULL || a==NULL){
        return;
    }
    write_AVL(f,a->fg);
    fprintf(f,"%s;%.3f\n",a->key,a->value);
    write_AVL(f,a->fd);
}

//lire le fichier csv ->generer un fichier de sortie avec capacité trier
int capacite_max(char *csv_path, char *output_path){
    if(csv_path==NULL || output_path==NULL){
        return 1;
    }
    FILE *csv=fopen(csv_path,"r");    
    if(csv==NULL){
        return 2;
    }
    avl *usine=NULL;
    char buffer[1024];


    // lire le fichier
    while(fgets(buffer,sizeof(buffer),csv)!=NULL){
        if(is_usine_line(buffer)){
            char *id=NULL;
            float cap=0.0;
            if(parse_usine_line(buffer,&id,&cap)){
                usine=avl_insert(usine,id,cap);
                free(id);
            }
        }
    }
    fclose(csv);
    FILE *out=fopen(output_path,"w");
    if(out==NULL){
        avl_free(usine);
        return 3;
    }
    //ecrire dans un fichier de sortie
    write_header(out);
    write_AVL(out, usine);

    fclose(out);
    avl_free(usine);

    return 0;
}