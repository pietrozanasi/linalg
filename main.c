#include "src/ops.c"
#include "time.h"

int main() {
	srand(time(NULL));
	printf("____linalg CLI____\n");

	int n = 5;

	matrix A;
	m_rand_diag_init(&A, n, 0.0, 10.0);
	m_print(&A);
}
