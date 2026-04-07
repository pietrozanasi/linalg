typedef struct {
	int n;
	double* data;
} matrix;

void m_init(matrix* m, int n);

double m_at(matrix* m, int i, int j);

void m_set(matrix* m, int i, int j, int x);

