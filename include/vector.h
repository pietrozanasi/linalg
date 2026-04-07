typedef struct {
	double* data;
	int n;
} vector;

void v_init(vector* v, int n);

int v_at(vector* v, int i);

void v_set(vector* v, int i, double x);


