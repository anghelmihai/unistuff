#include <stdlib.h>
#include <stdio.h>

#include "gmp.h"
#include "libqpoint.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("USAGE: findorder a b 'x coord' 'y coord'\n");
        return 1;
    }

    int a_int = strtol(argv[1], NULL, 10);
    int b_int = strtol(argv[2], NULL, 10);

    int x0_int = strtol(argv[3], NULL, 10);

    int y0_int = strtol(argv[4], NULL, 10);

    printf("a = %d\n", a_int);
    printf("b = %d\n", b_int);
    printf("x0 = %d\n", x0_int);
    printf("y0 = %d\n", y0_int);

    mpq_t x0;
    mpq_init(x0);
    mpq_set_si(x0, x0_int, 1);
    mpq_t y0;
    mpq_init(y0);
    mpq_set_si(y0, y0_int, 1);
    mpq_t a;
    mpq_init(a);
    mpq_set_si(a, a_int, 1);
    mpq_t b;
    mpq_init(b);
    mpq_set_si(b, b_int, 1);

    mpq_t x;
    mpq_init(x);
    mpq_t y;
    mpq_init(y);

    if (!good_curve(a_int, b_int))
    {
        printf("singular curve, abort!");
        return 1;
    }

    printf("order = %d\n", point_order(x0, y0, a, b));

    return 0;
}
