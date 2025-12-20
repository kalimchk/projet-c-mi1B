#include <stdio.h>

/* Prototype (pas de .h) */
int run_leaks(char *input_csv, char *factory_id);

int main()
{
    int ret;

    printf("=== TEST run_leaks ===\n");

    ret = run_leaks("test.dat", "Plant #OU300273S");

    if (ret == 0)
        printf("run_leaks OK\n");
    else if (ret == -1)
        printf("Usine non trouvee\n");
    else
        printf("run_leaks ERREUR (%d)\n", ret);

    return 0;
}
