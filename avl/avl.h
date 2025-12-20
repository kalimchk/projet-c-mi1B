#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct avl{
    char *key;         // identifiant de l'usine
    float value;       // valeur générique : float pour max, int converti pour src
    struct avl *fg;
    struct avl *fd;
    int height;
} avl;

// Fonctions AVL génériques
avl *avl_new_node(char *key, float value);
avl *avl_insert(avl *a,char *key, float value);
avl *avl_find(avl *a,char *key);
void write_avl(FILE *f, avl *a);
void avl_inorder(avl *a, FILE *out, int reverse);
void avl_free(avl *a);

#endif