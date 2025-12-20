#include <stdio.h>
#include "max.h"

int main(){
    int ret;

    ret = capacite_max("test.dat", "resultat.csv");

    if (ret != 0) {
        printf("Erreur lors du calcul\n");
        return 1;
    }

    printf("Calcul terminé avec succès\n");
    return 0;
}
