#ifndef MAX_H
#define MAX_H

#include<stdio.h>

typedef struct {
    char *id_usine;
    float capacite_max;
}usine;

typedef struct avl{
    char *key;
    float elt;
    struct avl *fg;
    struct avl *fd;
}avl;

avl *avl_insert( avl * a, char *key, float elt);
void free_avl(avl *a);

int is_usine_line(char *line);                             
int parse_usine_line(char *line, char **id_usine, float *capacite_Mm3);  
void write_header(FILE *f);                                
void write_AVL(FILE *f, avl *r);                       
int capacite_max(char *csv_path, char *output_path);

 #endif