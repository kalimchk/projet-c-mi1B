#ifndef SRC_H
#define SRC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_MAX_LEN 20

typedef struct AVL{
    char id[ID_MAX_LEN];
    int volume_src;
    int height;
    struct AVL *left;
    struct AVL *right;
} AVL;

// lance le traitement histo src
int run_src( char *input_csv, char *output_file);

// insere ou met a jour une usine dans l'AVL
AVL *AVL_insert(AVL *root,  char *id, int volume);

// recherche une usine dans l'AVL
AVL *AVL_find(AVL *root, char *id);

// parcourt l'AVL en ordre alphabetique inverse et ecrit dans un fichier
void AVL_reverse_inorder(AVL *root, FILE *out);

// libere toute la memoire de l'AVL
void AVL_free(AVL *root);

#endif