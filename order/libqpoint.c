#include "gmp.h"

void point_double(mpq_t *x, mpq_t *y, mpq_t x0, mpq_t y0, mpq_t a)
{
    mpq_t slope;
    mpq_init(slope);

    mpq_t tmp3;
    mpq_init(tmp3);
    mpq_set_ui(tmp3, 3, 1);

    mpq_t tmp2;
    mpq_init(tmp2);
    mpq_set_ui(tmp2, 2, 1);

    mpq_t numerator;
    mpq_init(numerator);
    mpq_mul(numerator, x0, x0);
    mpq_mul(numerator, numerator, tmp3);
    mpq_add(numerator, numerator, a);

    mpq_t denominator;
    mpq_init(denominator);
    mpq_mul(denominator, y0, tmp2);

    mpq_div(slope, numerator, denominator);

    mpq_mul(*x, slope, slope);
    mpq_mul(tmp3, tmp2, x0);
    mpq_sub(*x, *x, tmp3);

    mpq_sub(tmp3, x0, *x);
    mpq_mul(tmp3, tmp3, slope);
    mpq_sub(*y, tmp3, y0);
}

void point_add(mpq_t *x, mpq_t *y, mpq_t x1, mpq_t y1, mpq_t x2, mpq_t y2, mpq_t a, mpq_t b)
{
    mpq_t slope;
    mpq_init(slope);

    mpq_t numerator;
    mpq_init(numerator);
    mpq_sub(numerator, y2, y1);
    mpq_t denominator;
    mpq_init(denominator);
    mpq_sub(denominator, x2, x1);
    mpq_div(slope, numerator, denominator);

    mpq_mul(*x, slope, slope);
    mpq_sub(*x, *x, x2);
    mpq_sub(*x, *x, x1);

    mpq_sub(*y, x2, *x);
    mpq_mul(*y, *y, slope);
    mpq_sub(*y, *y, y2);
}

int point_order(mpq_t x0, mpq_t y0, mpq_t a, mpq_t b)
{
    if (mpq_sgn(y0) == 0)
    {
        return 2;
    }

    mpq_t x;
    mpq_init(x);
    mpq_t y;
    mpq_init(y);

    point_double(&x, &y, x0, y0, a);
    if (mpq_cmp(x, x0) == 0)
    {
        return 3;
    }

    int ord = 3;

    mpq_t new_x;
    mpq_init(new_x);
    mpq_t new_y;
    mpq_init(new_y);

    while (1)
    {
        ord++;
        point_add(&new_x, &new_y, x0, y0, x, y, a, b);
        if (mpq_cmp(new_x, x0) == 0)
        {
            return ord;
        }
        else
        {
            mpq_set(x, new_x);
            mpq_set(y, new_y);
        }
    }
}

int good_curve(int a, int b)
{
    int d;
    d = 4 * a * a * a + 27 * b * b;

    if (d == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
