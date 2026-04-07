typedef struct {
	int n;
	double* data;
} matrix;

void m_zero_init(matrix* m, int n);

void m_rand_init(matrix* m, int n, double min, double max);

double m_at(matrix* m, int i, int j);

void m_set(matrix* m, int i, int j, double x);

void m_print(matrix* m);

void m_mult(matrix* m1, matrix* m2, matrix* out);