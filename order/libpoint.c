#include "gmp.h"

void point_double(mpz_t *x, mpz_t *y, mpz_t x0, mpz_t y0, int a, int b, int car)
{
    mpz_t slope;
    mpz_init(slope);

    mpz_t numerator;
    mpz_init(numerator);
    mpz_mul(numerator, x0, x0);
    mpz_mul_ui(numerator, numerator, 3);
    mpz_add_ui(numerator, numerator, a);
    mpz_tdiv_r_ui(numerator, numerator, car);

    mpz_t denominator;
    mpz_init(denominator);
    mpz_add(denominator, y0, y0);
    mpz_tdiv_r_ui(denominator, denominator, car);

    mpz_t car_t;
    mpz_init(car_t);
    mpz_set_ui(car_t, car);
    mpz_invert(slope, denominator, car_t);
    mpz_mul(slope, numerator, slope);
    mpz_tdiv_r_ui(slope, slope, car);

    mpz_mul(*x, slope, slope);
    mpz_mul_ui(numerator, x0, 2);
    mpz_sub(*x, *x, numerator);
    mpz_tdiv_r_ui(*x, *x, car);
    if (mpz_sgn(*x) == -1)
    {
        mpz_add_ui(*x, *x, car);
    }

    mpz_sub(numerator, x0, *x);
    mpz_mul(numerator, numerator, slope);
    mpz_sub(*y, numerator, y0);
    mpz_tdiv_r_ui(*y, *y, car);
    if (mpz_sgn(*y) == -1)
    {
        mpz_add_ui(*y, *y, car);
    }
}

void point_add(mpz_t *x, mpz_t *y, mpz_t x1, mpz_t y1, mpz_t x2, mpz_t y2, int a, int b, int car)
{
    mpz_t slope;
    mpz_init(slope);

    mpz_sub(*y, y2, y1);
    mpz_sub(*x, x2, x1);

    mpz_t car_t;
    mpz_init(car_t);
    mpz_set_ui(car_t, car);
    mpz_invert(slope, *x, car_t);
    mpz_mul(slope, *y, slope);
    mpz_tdiv_r_ui(slope, slope, car);

    mpz_mul(*x, slope, slope);
    mpz_sub(*x, *x, x2);
    mpz_sub(*x, *x, x1);
    mpz_tdiv_r_ui(*x, *x, car);
    if (mpz_sgn(*x) == -1)
    {
        mpz_add_ui(*x, *x, car);
    }

    mpz_sub(*y, x2, *x);
    mpz_mul(*y, slope, *y);
    mpz_sub(*y, *y, y2);
    mpz_tdiv_r_ui(*y, *y, car);
    if (mpz_sgn(*y) == -1)
    {
        mpz_add_ui(*y, *y, car);
    }
}

int point_order(mpz_t x0, mpz_t y0, int a, int b, int car)
{
    if (mpz_sgn(y0) == 0)
    {
        return 2;
    }

    mpz_t x;
    mpz_init(x);
    mpz_t y;
    mpz_init(y);

    point_double(&x, &y, x0, y0, a, b, car);

    if (mpz_cmp(x, x0) == 0)
    {
        return 3;
    }

    int ord = 3;

    mpz_t new_x;
    mpz_init(new_x);
    mpz_t new_y;
    mpz_init(new_y);

    while (1)
    {
        ord++;
        point_add(&new_x, &new_y, x0, y0, x, y, a, b, car);
        if (mpz_cmp(new_x, x0) == 0)
        {
            return ord;
        }
        else
        {
            mpz_set(x, new_x);
            mpz_set(y, new_y);
        }
    }
}

int good_curve(int a, int b, int car)
{
    int d;
    d = 4 * a * a * a + 27 * b * b;

    if (d % car == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
