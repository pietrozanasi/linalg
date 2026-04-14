typedef struct {
	double* data;
	int n;
} vector;

void v_print(vector* v);

void v_zero_init(vector* v, int n);
void v_rand_init(vector* v, int n, double min, double max);

int v_at(vector* v, int i);
void v_set(vector* v, int i, double x);

void v_scalar_mult(vector* v, double c);
void v_mult(vector* v1, vector* v2, vector* out);
void v_add(vector* v1, vector* v2, vector* out);

double v_dist(vector* v1, vector* v2);
double v_norm(vector* v);