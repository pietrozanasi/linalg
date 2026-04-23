#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "../include/matrix.h"
#include "../include/vector.h"

// printers

int v_print(vector* v) {
    if(v == NULL) {
        fprintf(stderr, "v_print::Null pointer\n");
        return 0;
    }
    int n = v->n;
    printf("\n%d-DIMENSIONAL VECTOR :\n", n);
    printf("[  ");
    for(int i = 0; i < n; i++) {
        printf("%f  ", v->data[i]);
    }
    printf("]\n\n");
    return 1;
}

int m_print(matrix* m) {
    if(m == NULL) {
        fprintf(stderr, "m_print::Null pointer\n");
        return 0;
    }
    int n = m->n;
    printf("\n%d x %d MATRIX :\n", n, n);
    for(int f = 0; f < n*n; f++) {
        printf("%f  ", m_at(m, f/n, f%n));
        if(!((f+1)%n)) printf("\n");
    }
    printf("END\n\n");
    return 1;
}

// initializers

int v_zero_init(vector* v, int n) {
    if(!v) {
        fprintf(stderr, "v_zero_init::Null pointer\n");
        return 0;
    }
    v->n = n;
    v->data = (double*)calloc(n, sizeof(double));
    return 1;
}

int v_rand_init(vector* v, int n, double min, double max) {
    if(!v) {
        fprintf(stderr, "v_rand_init::Null pointer\n");
        return 0;
    }
    v->n = n;
    v->data = (double*)malloc(n * sizeof(double));
    for(int i = 0; i < n; i++)
        v->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
    return 1;
}

int v_copy_init(vector* in, vector* out) {
    if(!in || !out) {
        fprintf(stderr, "v_copy_init::Null pointer\n");
        return 0;
    }

    int n = in->n;
    v_zero_init(out, n);
    for(int i = 0; i < n; i++)
        out->data[i] = in->data[i];
    return 1;
}

int m_zero_init(matrix* m, int n) {
    if(!m) {
        fprintf(stderr, "m_zero_init::Null pointer\n");
        return 0;
    }
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
    return 1;
}

int m_rand_init(matrix* m, int n, double min, double max) {
    if(!m) {
        fprintf(stderr, "m_rand_init::Null pointer\n");
        return 0;
    }

    if(min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));

    for(int i = 0; i < n * n; i++)
        m->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
    return 1;
}

int m_id_init(matrix* m, int n) {
    if(!m) {
        fprintf(stderr, "m_id_init::Null pointer\n");
        return 0;
    }
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
    for(int i = 0; i < n; i++)
        m_set(m, i, i, 1.0);
    return 1;
}

int m_rand_lower_init(matrix* m, int n, double min, double max) {
    if(!m) {
        fprintf(stderr, "m_rand_lower_init::Null pointer\n");
        return 0;
    }
    
    if(min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    double num;

    for(int f = 0; f < n * n; f++) {
        if(f/n<f%n) num = 0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }
    return 1;
}

int m_rand_upper_init(matrix* m, int n, double min, double max) {
    if(!m) {
        fprintf(stderr, "m_rand_upper_init::Null pointer\n");
        return 0;
    }
    
    if(min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    double num;

    for(int f = 0; f < n * n; f++) {
        if(f/n>f%n) num = 0.0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }
    return 1;
}

int m_rand_diag_init(matrix* m, int n, double min, double max) {
    if(!m) {
        fprintf(stderr, "m_rand_diag_init::Null pointer\n");
        return 0;
    }

    if(min > max) {
        double tmp = min;
        min = max;
        max = tmp;
    }

    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    double num;

    for(int f = 0; f < n * n; f++) {
        if(f/n!=f%n) num = 0.0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }

    return 1;
}

int m_copy_init(matrix* in, matrix* out) {
    if(!in || !out) {
        fprintf(stderr, "m_copy_init::Null pointer\n");
        return 0;
    }
    int n = in->n;
    m_zero_init(out, n);

    for(int i = 0; i < n * n; i++)
        out->data[i] = in->data[i];
    return 1;
}

// getters and setters

double v_at(vector* v, int i) {
    if(!v) {
        fprintf(stderr, "v_at::Null pointer\n");
        exit(1);
    }
    if(i>= v->n) {
        fprintf(stderr, "v_at::Index %d out of bound %d\n", i, v->n);
        exit(1);
    }
    return v->data[i];
}

double m_at(matrix* m, int i, int j) {
    if(!m) {
        fprintf(stderr, "m_at::Null pointer\n");
        exit(1);
    }
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "m_at::Index %d or %d out of bounds %d\n", i, j, m->n);
        exit(1);
    }
    return m->data[i * m->n + j];
}

int v_set(vector* v, int i, double x) {
    if(!v) {
        fprintf(stderr, "v_set::Null pointer\n");
        return 0;
    }
    if(i >= v->n) {
        fprintf(stderr, "v_set::Index %d out of bounds %d\n", i, v->n);
        return 0;
    }
    v->data[i] = x;
    return 1;
}

int m_set(matrix* m, int i, int j, double x) {
    if(!m) {
        fprintf(stderr, "m_set::Null pointer\n");
        return 0;
    }
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "m_set::Index %d or %d out of bound %d\n", i, j, m->n);
        return 0;
    }
    m->data[i * m->n + j] = x;
    return 1;
}

// norms and distances

double v_dist(vector* v1, vector* v2) {
    if(v1->n != v2->n) {
        fprintf(stderr, "v_dist::Different vector dimensions: %d and %d\n", v1->n, v2->n);
        exit(1);
    }

    int n = v1->n;
    double sum = 0.0;

    for(int i = 0; i < n; i++) {
        sum += (v1->data[i] - v2->data[i]) * (v1->data[i] - v2->data[i]);
    }

    return sqrt(sum);
}

double v_norm(vector* v) {
    double res;
    vector zero;
    v_zero_init(&zero, v->n);
    res = v_dist(v, &zero);
    free(zero.data);
    return res;
}

// vector operations

int v_scalar_mult(vector* v, double c) {
    if(!v) {
        fprintf(stderr, "v_scalar_mult::Null pointer\n");
        return 0;
    }
    int n = v->n;
    for(int i = 0; i < n; i++) {
        v->data[i] *= c;
    }
    return 1;
}

int v_mult(vector* v1, vector* v2, vector* out) {
    if(!v1 || !v2 || !out) {
        fprintf(stderr, "v_mult::Null pointer\n");
        return 0;
    }
    if(v1->n != v2->n) {
        fprintf(stderr, "v_mult::Different vector dimension: %d and %d\n", v1->n, v2->n);
        return 0;
    }

    int n = v1->n;
    v_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] * v2->data[i];
    }
    return 1;
}

int v_add(vector* v1, vector* v2, vector* out) {
    if(!v1 || !v2 || !out) {
        fprintf(stderr, "v_add::Null pointer\n");
        return 0;
    }
    if(v1->n != v2->n) {
        fprintf(stderr, "v_add::Different vector dimensions: %d and %d\n", v1->n, v2->n);
        return 0;
    }

    int n = v1->n;
    v_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] + v2->data[i];
    }
    return 1;
}

// matrix operations

int m_mult(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n) {
        fprintf(stderr, "m_mult::Different matrix dimensions: %d and %d\n", m1->n, m2->n);
        return 0;
    }

    if(out == m1 || out == m2) {
        matrix temp;
        m_mult(m1, m2, &temp);
        m_copy_init(&temp, out);
        free(temp.data);
        return 1;
    }

    int n = m1->n;
    double sum;

    m_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum = 0.0;
            for(int k = 0; k < n; k++)
                sum += m_at(m1, i, k) * m_at(m2, k, j);

            m_set(out, i, j, sum);
        }
    }
    return 1;
}

int m_add(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n) {
        fprintf(stderr, "m_add::Different matrix dimensions: %d and %d\n", m1->n, m2->n);
        return 0;
    }

    if(out == m1 || out == m2) {
        matrix temp;
        m_add(m1, m2, &temp);
        m_copy_init(&temp, out);
        free(temp.data);
        return 1;
    }

    int n = m1->n;
    m_zero_init(out, n);

    for(int i = 0; i < n * n; i++)
        out->data[i] = m1->data[i] + m2->data[i];
    return 1;
}

// matrix-vector multiplication

int mv_mult(matrix* m, vector* v, vector* out) {
    if(m->n != v->n ) {
        fprintf(stderr, "mv_mult::Incompatible dimensions for matrix-vector multiplication\n");
        return 0;
    }

    int n = m->n;
    double sum;
    v_zero_init(out, n);

    if(out == v) {
        vector temp;
        mv_mult(m, v, &temp);
        v_copy_init(&temp, out);
        free(temp.data);
        return 1;
    }

    for(int i = 0; i < n; i++) {
        sum = 0.0;
        for(int j = 0; j < n; j++)
            sum += m_at(m, i, j) * v_at(v, j);

        v_set(out, i, sum);
    }
    return 1;
}

int v_swap(vector* v, int i, int j) {
    if(!v) {
        fprintf(stderr, "v_swap::Null pointer\n");
        return 0;
    }
    if(i >= v->n || j >= v->n) {
        fprintf(stderr, "v_swap::Index %d or %d out of bounds %d\n", i, j, v->n);
        return 0;
    }

    double temp = v_at(v, i);
    v_set(v, i, v_at(v, j));
    v_set(v, j, temp);
    return 1;
}

// matrix manipulation

int m_swap_rows(matrix* m, int r1, int r2) {
    if(!m) {
        fprintf(stderr, "m_swap_rows::Null pointer\n");
        return 0;
    }
    if(r1 >= m->n || r2 >= m->n) {
        fprintf(stderr, "Row index out of bounds\n");
        return 0;
    }

    int n = m->n;
    double temp;

    for(int j = 0; j < n; j++) {
        temp = m_at(m, r1, j);
        m_set(m, r1, j, m_at(m, r2, j));
        m_set(m, r2, j, temp);
    }
    return 1;
}

int m_transpose(matrix* m, matrix* out) {
    if(!m || !out) {
        fprintf(stderr, "m_transpose::Null pointer\n");
        return 0;
    }
    if(m->n != out->n) {
        fprintf(stderr, "Incompatible dimensions for transpose\n");
        return 0;
    }
    
    int n = m->n;
    if(!m_zero_init(out, n)) {
        fprintf(stderr, "m_transpose::Failed to initialize output matrix\n");
        return 0;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            m_set(out, j, i, m_at(m, i, j));
        }
    }
    return 1;
}

int m_remove_cross(matrix* m, int row, int col, matrix* out) {
    if(row >= m->n || col >= m->n) {
        fprintf(stderr, "m_remove_cross::Indices %d, %d out of bounds %d\n", row, col, m->n);
        return 0;
    }

    int n = m->n;
    int g = 0;
    if(!m_zero_init(out, n-1)) {
        fprintf(stderr, "m_remove_cross::Failed to initialize output matrix\n");
        return 0;
    }

    for(int f=0; f<n*n; f++) {
        if(f/n!=row && f%n!=col)
            out->data[g++] = m->data[f];
    }
    return 1;
}

int m_swap(matrix* m, int i1, int j1, int i2, int j2) {
    if(!m) {
        fprintf(stderr, "m_swap::Null pointer\n");
        return 0;
    }
    if(i1 >= m->n || j1 >= m->n || i2 >= m->n || j2 >= m->n) {
        fprintf(stderr, "m_swap::Indices out of bounds. I1: %d, J1: %d, I2: %d, J2: %d, n=%d\n", i1, j1, i2, j2, m->n);
        return 0;
    }

    double temp = m_at(m, i1, j1);
    m_set(m, i1, j1, m_at(m, i2, j2));
    m_set(m, i2, j2, temp);
    return 1;
}

// determinants

double m_naive_det(matrix* m) {
    if(m->n == 1) return m_at(m, 0, 0);

    double det = 0.0;
    matrix minor;

    for(int i = 0; i < m->n; i++) {
        m_remove_cross(m, i, 0, &minor);
        det += m_at(m, i, 0) * m_naive_det(&minor);
        free(minor.data);
    }

    return det;
}

double m_triang_det(matrix* m) {
    double res = 1.0;
    int n = m->n;

    for(int i=0; i<n; i++)
        res *= m_at(m, i, i);

    return res;
}

// solvers

// solve Ax = b where A is diagonal
int solve_diag(matrix* A, vector* x, vector* b) {
    if(A->n != x->n || A->n != b->n) {
        fprintf(stderr, "solve_diag::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return 0;
    }

    int n = A->n;
    for(int i = 0; i < n; i++) {
        if(m_at(A, i, i) == 0.0) {
            fprintf(stderr, "solve_diag::Zero diagonal element at index %d\n", i);
            return 0;
        }
        if(!v_set(x, i, v_at(b, i) / m_at(A, i, i))) {
            fprintf(stderr, "solve_diag::Failed to set x[%d]\n", i);
            return 0;
        }
    }

    return 1;
}

// LU decomposition with permutation matrix
int lu_decomp(matrix* m, matrix* L, matrix* U, matrix *P) {
    int n = m->n;
    if(!m_id_init(L, n)) {
        fprintf(stderr, "lu_decomp::Failed to initialize L matrix\n");
        return 0;
    }
    if(!m_copy_init(m, U)) {
        fprintf(stderr, "lu_decomp::Failed to initialize U matrix\n");
        return 0;
    }
    if(!m_id_init(P, n)) {
        fprintf(stderr, "lu_decomp::Failed to initialize P matrix\n");
        return 0;
    }

    int p; 
    double Ujk, Upk, Lik, Ukk; // Upk è il valore sulla riga pivot
    // Uij e Ukj vanno dichiarate qui o dentro il ciclo

    for(int k = 0; k < n; k++) {
        // 1. Ricerca del Pivot
        p = k;
        for(int j = k + 1; j < n; ++j) {
            Ujk = m_at(U, j, k);
            Upk = m_at(U, p, k); // Confrontiamo sempre gli elementi sulla stessa colonna k
            if(fabs(Ujk) > fabs(Upk))
                p = j;
        }

        // 2. Scambio righe se necessario
        if(k != p) {
            if(!m_swap_rows(U, k, p)) {
                fprintf(stderr, "lu_decomp::Failed to swap rows in U matrix\n");
                return 0;
            }
            if(!m_swap_rows(P, k, p)) {
                fprintf(stderr, "lu_decomp::Failed to swap rows in P matrix\n");
                return 0;
            }
            for(int j = 0; j < k; j++) {
                // Assumendo che m_swap scambi elementi singoli (m, r1, c1, r2, c2)
                if(!m_swap(L, k, j, p, j)) {
                    fprintf(stderr, "lu_decomp::Failed to swap elements in L matrix\n");
                    return 0;
                }
            }
        }

        // 3. Eliminazione
        Ukk = m_at(U, k, k);
        if(fabs(Ukk) < 1e-15) { // Meglio un piccolo epsilon rispetto a 0.0 secco
            fprintf(stderr, "lu_decomp::Zero pivot element at index %d. Matrix is singular.\n", k);
            return 0;
        }

        for(int i = k + 1; i < n; ++i) {
            Lik = m_at(U, i, k) / Ukk;
            if(!m_set(L, i, k, Lik)) {
                fprintf(stderr, "lu_decomp::Failed to set element in L matrix\n");
                return 0;
            }
            if(!m_set(U, i, k, 0.0)) {
                fprintf(stderr, "lu_decomp::Failed to set element in U matrix\n");
                return 0;
            }

            for(int j = k + 1; j < n; ++j) {
                // IMPORTANTE: Questi valori devono essere aggiornati DENTRO il ciclo j
                double Ukj = m_at(U, k, j);
                double Uij = m_at(U, i, j);
                if(!m_set(U, i, j, Uij - Lik * Ukj)) {
                    fprintf(stderr, "lu_decomp::Failed to set element in U matrix\n");
                    return 0;
                }
            }
        }
    }
    return 1;
}


// solve Ax = b where A is orthogonal, that is: A^T A = I, which implies that A^T = A^-1
// therefore, x = A^-1 b = A^T b. returns 0 if A is not orthogonal, 1 otherwise.
int solve_orthogonal(matrix* A, vector* x, vector* b) {
    if(A->n != x->n || A->n != b->n) {
        fprintf(stderr, "solve_orthogonal::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return 0;
    }

    int n = A->n;
    matrix A_T;
    if(!m_transpose(A, &A_T)) {
        fprintf(stderr, "solve_orthogonal::Failed to transpose matrix A\n");
        return 0;
    }
    if(!mv_mult(&A_T, b, x)) {
        fprintf(stderr, "solve_orthogonal::Failed to multiply matrices\n");
        free(A_T.data);
        return 0;
    }
    free(A_T.data);
    return 1;
}

// solve Ax = b where A is lower triangular, using forward substitution. invariant:
// x_i = (b_i - sum_{j=0}^{i-1} A_{ij} x_j) / A_{ii}
int solve_lower_triangular(matrix* A, vector* x, vector* b) {
    if(A->n != b->n) {
        fprintf(stderr, "solve_lower_triangular::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return 0;
    }

    int n = A->n;
    double sum;
    v_zero_init(x, n);

    for(int i = 0; i < n; i++) {
        sum = 0.0;
        for(int j = 0; j < i; j++) {
            sum += m_at(A, i, j) * v_at(x, j);
        }
        v_set(x, i, (v_at(b, i) - sum) / m_at(A, i, i));
    }
    return 1;
}

// solve Ax = b where A is upper triangular, using backward substitution. invariant:
// x_i = (b_i - sum_{j=i+1}^{n-1} A_{ij} x_j) / A_{ii}
int solve_upper_triangular(matrix* A, vector* x, vector* b) {
        if(A->n != b->n) {
        fprintf(stderr, "solve_upper_triangular::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return 0;
    }

    int n = A->n;
    double sum;
    if(!v_zero_init(x, n)) {
        fprintf(stderr, "solve_upper_triangular::Failed to initialize vector x\n");
        return 0;
    }

    for(int i = n-1; i >= 0; i--) {
        sum = 0.0;
        for(int j = i+1; j < n; j++) {
            sum += m_at(A, i, j) * v_at(x, j);
        }
        if(!v_set(x, i, (v_at(b, i) - sum) / m_at(A, i, i))) {
            fprintf(stderr, "solve_upper_triangular::Failed to set element in vector x\n");
            return 0;
        }
    }
    return 1;
}

int solve_lu(matrix* A, vector* x, vector* b) {
    if(A->n != b->n) {
        fprintf(stderr, "solve_lu::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return 0;
    }

    matrix L, U, P;
    if(!lu_decomp(A, &L, &U, &P)) {
        fprintf(stderr, "solve_lu::Failed to decompose matrix A\n");
        return 0;
    }

    int res = 1;
    int n = A->n;
    vector y;
    vector Pb;
    if(!mv_mult(&P, b, &Pb)) {
        fprintf(stderr, "solve_lu::Failed to multiply matrices\n");
        res = 0;
    }

    if(!solve_lower_triangular(&L, &y, &Pb)) {
        fprintf(stderr, "solve_lu::Failed to solve lower triangular system\n");
        res = 0;
    }

    if(!solve_upper_triangular(&U, x, &y)) {
        fprintf(stderr, "solve_lu::Failed to solve upper triangular system\n");
        res = 0;
    }

    free(P.data);
    free(L.data);
    free(U.data);
    free(y.data);
    free(Pb.data);
    return res;
}

// uses cholesky to solve Ax = b where A is positive definite.
// decomposes into A = LL^T
int solve_posdef(matrix* A, vector* x, vector* b) {
    
}