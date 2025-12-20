#include "avl.h"
#include <stdlib.h>
#include <string.h>

// utilitaire
int max(int a, int b){ 
    return (a > b) ? a : b; 
}
int height(avl *n){ 
    return n ? n->height : 0; 
}

// crée un nouveau noeud
avl *avl_new_node(char *key, float value){
    avl *n = malloc(sizeof(avl));
    if (n==NULL){
        return NULL;
    } 
    n->key = strdup(key);
    if (!n->key) {
        free(n); 
        return NULL; 
    }
    n->value = value;
    n->fg = n->fd = NULL;
    n->height = 1;
    return n;
}

void write_avl(FILE *f, avl *a) {
    if (f == NULL || a == NULL) return;

    // Parcours sous-arbre droit
    if (a->fd) write_avl(f, a->fd);

    // Écriture du nœud courant
    fprintf(f, "%s;%.2f\n", a->key, a->value);

    // Parcours sous-arbre gauche
    if (a->fg) write_avl(f, a->fg);
}

// rotation droite
avl *rotate_right(avl *y){
    avl *x = y->fg;
    avl *T2 = x->fd;
    x->fd = y;
    y->fg = T2;
    y->height = max(height(y->fg), height(y->fd)) + 1;
    x->height = max(height(x->fg), height(x->fd)) + 1;
    return x;
}

// rotation gauche
avl *rotate_left(avl *x){
    avl *y = x->fd;
    avl *T2 = y->fg;
    y->fg = x;
    x->fd = T2;
    x->height = max(height(x->fg), height(x->fd)) + 1;
    y->height = max(height(y->fg), height(y->fd)) + 1;
    return y;
}

// facteur d'équilibre
int balance_factor(avl *n){ 
    return n ? height(n->fg) - height(n->fd) : 0; 
}

// insertion AVL avec équilibrage
avl *avl_insert(avl *a,char *key, float value){
    if (a==NULL){
        return avl_new_node(key, value);
    }
    int cmp = strcmp(key, a->key);
    if (cmp == 0){
        a->value = value;  // mise à jour
        return a;
    } else if (cmp < 0){
        a->fg = avl_insert(a->fg, key, value);
    }else{
        a->fd = avl_insert(a->fd, key, value);
    }
    a->height = 1 + max(height(a->fg), height(a->fd));
    int bf = balance_factor(a);

    if (bf > 1 && strcmp(key, a->fg->key) < 0){
        return rotate_right(a);
    } 
    if (bf < -1 && strcmp(key, a->fd->key) > 0){
        return rotate_left(a);
    }
    if (bf > 1 && strcmp(key, a->fg->key) > 0) {
        a->fg = rotate_left(a->fg);
        return rotate_right(a);
    }
    if (bf < -1 && strcmp(key, a->fd->key) < 0) {
        a->fd = rotate_right(a->fd);
        return rotate_left(a);
    }

    return a;
}

// recherche
avl *avl_find(avl *a,char *key){
    if (a==NULL){
        return NULL;
    }
    int cmp = strcmp(key, a->key);
    if (cmp == 0){
        return a;
    }
    return (cmp < 0) ? avl_find(a->fg, key) : avl_find(a->fd, key);
}

// parcours inorder (reverse si reverse=1)
void avl_inorder(avl *a, FILE *out, int reverse){
    if (a==NULL){
        return;
    }
    if (reverse) {
        avl_inorder(a->fd, out, 1);
        fprintf(out, "%s;%.3f\n", a->key, a->value);
        avl_inorder(a->fg, out, 1);
    } else {
        avl_inorder(a->fg, out, 0);
        fprintf(out, "%s;%.3f\n", a->key, a->value);
        avl_inorder(a->fd, out, 0);
    }
}

// libération
void avl_free(avl *a){
    if (a==NULL){
        return;
    }
    avl_free(a->fg);
    avl_free(a->fd);
    free(a->key);
    free(a);
}

