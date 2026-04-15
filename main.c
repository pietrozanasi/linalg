#include "src/ops.c"
#include "time.h"

int main() {
    srand(time(NULL));
    int n = 5;

	matrix A;
	vector b;
    m_rand_init(&A, n, 0.0, 10.0);
	v_rand_init(&b, n, 0.0, 10.0);

	vector x;
	solve_lu(&A, &x, &b);
	printf("A:\n");
	m_print(&A);
	printf("b:\n");
	v_print(&b);
	printf("x:\n");
	v_print(&x);

    return 0;
}