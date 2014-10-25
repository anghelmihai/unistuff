int point_order(mpz_t x0, mpz_t y0, int a, int b, int car);

void point_add(mpz_t *x, mpz_t *y, mpz_t x1, mpz_t y1, mpz_t x2, mpz_t y2, int a, int b, int car);

void point_double(mpz_t *x, mpz_t *y, mpz_t x0, mpz_t y0, int a, int b, int car);

int good_curve(int a, int b, int car);
