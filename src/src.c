#include "src.h"

// retourne le maximum entre deux entiers
int max(int a, int b){
    return (a > b) ? a : b;
}

// retourne la hauteur d'un noeud AVL
int height(AVL *n){
    if (n == NULL)
        return 0;
    return n->height;
}

// cree un nouveau noeud AVL pour une usine
AVL *new_node( char *id, int volume){
    AVL *n = malloc(sizeof(AVL));
    if (n == NULL)
        return NULL;

    strcpy(n->id, id);
    n->volume_src = volume;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;

    return n;
}

// effectue une rotation droite pour equilibrer l'AVL
AVL *rotate_right(AVL *y){
    AVL *x = y->left;
    AVL *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// effectue une rotation gauche pour equilibrer l'AVL
AVL *rotate_left(AVL *x){
    AVL *y = x->right;
    AVL *t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// calcule le facteur d'equilibrage d'un noeud AVL
int balance_factor(AVL *n){
    if (n == NULL){
        return 0;
    }
    return height(n->left) - height(n->right);
}

// insere une usine dans l'AVL et ajoute le volume capte
AVL *AVL_insert(AVL *root,  char *id, int volume){
    if (root == NULL){
        return new_node(id, volume);
    }
    int cmp = strcmp(id, root->id);
    if (cmp == 0){
        root->volume_src += volume;
        return root;
    }
    else if (cmp < 0){
        root->left = AVL_insert(root->left, id, volume);
    }
    else{
        root->right = AVL_insert(root->right, id, volume);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance_factor(root);
    if (bf > 1 && strcmp(id, root->left->id) < 0){
        return rotate_right(root);
    }
    if (bf < -1 && strcmp(id, root->right->id) > 0){
        return rotate_left(root);
    }
    if (bf > 1 && strcmp(id, root->left->id) > 0){
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (bf < -1 && strcmp(id, root->right->id) < 0){
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

// recherche une usine dans l'AVL a partir de son identifiant
AVL *AVL_find(AVL *root, char *id){
    if (root == NULL){
        return NULL;
    }
    int cmp = strcmp(id, root->id);
    if (cmp == 0){
        return root;
    }
    if (cmp < 0){
        return AVL_find(root->left, id);
    }
    return AVL_find(root->right, id);
}

// parcourt l'AVL en ordre inverse et ecrit les donnees
void AVL_reverse_inorder(AVL *root, FILE *out){
    if (root == NULL){
        return;
    }
    AVL_reverse_inorder(root->right, out);
    fprintf(out, "%s;%.3f\n", root->id, root->volume_src / 1000);
    AVL_reverse_inorder(root->left, out);
}

// libere toute la memoire allouee pour l'AVL
void AVL_free(AVL *root){
    if (root == NULL){
        return;
    }
    AVL_free(root->left);
    AVL_free(root->right);
    free(root);
}

// fonction principale du traitement src
int run_src(char *input_csv, char *output_file)
{
    FILE *in = fopen(input_csv, "r");
    if (in == NULL){
        fprintf(stderr, "Erreur : impossible d'ouvrir %s\n", input_csv);
        return 1;
    }
    FILE *out = fopen(output_file, "w");
    if (out == NULL){
        fclose(in);
        fprintf(stderr, "Erreur : impossible de creer %s\n", output_file);
        return 2;
    }
    fprintf(out, "identifier;source_volume(M.m3.year-1)\n");
    AVL *root = NULL;
    char line[512];
    while (fgets(line, sizeof(line), in)){
        char *col1 = strtok(line, ";");
        char *col2 = strtok(NULL, ";");
        char *col3 = strtok(NULL, ";");
        char *col4 = strtok(NULL, ";");

        if (!col1 || !col3 || !col4){
            continue;
        }
        if (strcmp(col1, "-") == 0 && strcmp(col4, "-") != 0){
            double volume = atof(col4);
            root = AVL_insert(root, col3, volume);
        }
    }
    AVL_reverse_inorder(root, out);
    AVL_free(root);
    fclose(in);
    fclose(out);

    return 0;
}