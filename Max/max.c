#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "max.h"
#include "parsing/parser.h"
#include"avl/avl.h"

//ecrire la premiere ligne du fichier de sortie
void write_header(FILE *f){
    if(f==NULL){
        return;
    }
    fprintf(f,"identifier,max_volume(M.m3)\n");
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