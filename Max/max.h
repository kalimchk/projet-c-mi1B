#ifndef MAX_H
#define MAX_H

#include <stdio.h>

/* Structure AVL (déclarée ici, implémentée dans avl.c) */
typedef struct avl {
    char *key;
    float value;
    struct avl *fg;
    struct avl *fd;
} avl;

/* Fonctions AVL utilisées par max.c */
avl *avl_insert(avl *a, char *key, float value);
void avl_free(avl *a);

/* Fonction publique du module max */
int capacite_max(char *csv_path,char *output_path);

#endif