typedef struct {
	double* data;
	int n;
} vector;

int v_print(vector* v);

int v_zero_init(vector* v, int n);
int v_rand_init(vector* v, int n, double min, double max);
int v_copy_init(vector* in, vector* out);

double v_at(vector* v, int i);
int v_set(vector* v, int i, double x);

int v_scalar_mult(vector* v, double c);
int v_mult(vector* v1, vector* v2, vector* out);
int v_add(vector* v1, vector* v2, vector* out);

double v_dist(vector* v1, vector* v2);
double v_norm(vector* v);