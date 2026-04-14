typedef struct {
	int n;
	double* data;
} matrix;

void m_zero_init(matrix* m, int n);
void m_rand_init(matrix* m, int n, double min, double max);
void m_rand_lower_init(matrix* m, int n, double min, double max);
void m_rand_upper_init(matrix* m, int n, double min, double max);
void m_rand_diag_init(matrix* m, int n, double min, double max);
void m_id_init(matrix* m, int n);

double m_at(matrix* m, int i, int j);
void m_set(matrix* m, int i, int j, double x);

void m_print(matrix* m);

void m_mult(matrix* m1, matrix* m2, matrix* out);
void m_add(matrix* m1, matrix* m2, matrix* out);

void m_swap_rows(matrix* m, int r1, int r2);
void m_transpose(matrix* m, matrix* out);

void lu_decomp(matrix* m, matrix* L, matrix* U, matrix *P);
void m_remove_cross(matrix* m, int row, int col, matrix* out);