#include <stdio.h>
#include "real.h"


int main()
{
    int ret;

    printf("=== TEST run_real ===\n");

    ret = run_real("test.dat", "real.csv");

    if (ret == 0)
        printf("run_real OK\n");
    else
        printf("run_real ERREUR (%d)\n", ret);

    return 0;
}
