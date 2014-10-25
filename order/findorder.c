#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gmp.h"
#include "libpoint.h"

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("USAGE: findorder a b 'field char' 'x coord' 'y coord'\n");
        return 1;
    }

    int a = strtol(argv[1], NULL, 10);
    int b = strtol(argv[2], NULL, 10);

    int car = strtol(argv[3], NULL, 10);

    int x0_int = strtol(argv[4], NULL, 10);
    x0_int = x0_int % car;

    int y0_int = strtol(argv[5], NULL, 10);
    y0_int = y0_int % car;

    printf("char = %d\n", car);
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("x0 = %d\n", x0_int);
    printf("y0 = %d\n", y0_int);

    mpz_t x0;
    mpz_init(x0);
    mpz_set_ui(x0, x0_int);
    mpz_t y0;
    mpz_init(y0);
    mpz_set_ui(y0, y0_int);

    if (!good_curve(a, b, car))
    {
        printf("singular curve, abort!");
        return 1;
    }
    printf("Computing order: %d\n", point_order(x0, y0, a, b, car));

    return 0;
}
