typedef struct {
	int n;
	double* data;
} matrix;

int m_zero_init(matrix* m, int n);
int m_rand_init(matrix* m, int n, double min, double max);
int m_rand_lower_init(matrix* m, int n, double min, double max);
int m_rand_upper_init(matrix* m, int n, double min, double max);
int m_rand_diag_init(matrix* m, int n, double min, double max);
int m_id_init(matrix* m, int n);
int m_copy_init(matrix* in, matrix* out);

double m_at(matrix* m, int i, int j);
int m_set(matrix* m, int i, int j, double x);

int m_print(matrix* m);

int m_mult(matrix* m1, matrix* m2, matrix* out);
int m_add(matrix* m1, matrix* m2, matrix* out);

int m_swap_rows(matrix* m, int r1, int r2);
int m_transpose(matrix* m, matrix* out);

int lu_decomp(matrix* m, matrix* L, matrix* U, matrix *P);
int m_remove_cross(matrix* m, int row, int col, matrix* out);
