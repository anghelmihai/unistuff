
void point_double(mpq_t *x, mpq_t *y, mpq_t x0, mpq_t y0, mpq_t a);

void point_add(mpq_t *x, mpq_t *y, mpq_t x1, mpq_t y1, mpq_t x2, mpq_t y2, mpq_t a, mpq_t b);

int point_order(mpq_t x0, mpq_t y0, mpq_t a, mpq_t b);

int good_curve(int a, int b);
