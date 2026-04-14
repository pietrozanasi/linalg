#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "../include/matrix.h"
#include "../include/vector.h"

// printer
void v_print(vector* v) {
    int n = v->n;
    printf("\n%d-DIMENSIONAL VECTOR :\n", n);
    printf("[  ");
    for(int i = 0; i < n; i++) {
        printf("%f  ", v->data[i]);
    }
    printf("]\n");
}

void m_print(matrix* m) {
    int n = m->n;
    printf("\n%d x %d MATRIX :\n", n, n);
    for(int f = 0; f < n*n; f++) {
        printf("%f  ", m_at(m, f/n, f%n));
        if(!((f+1)%n)) printf("\n");
    }
    printf("END\n");
}

// initializers

void v_zero_init(vector* v, int n) {
    v->n = n;
    v->data = (double*)calloc(n, sizeof(double));
}

void v_rand_init(vector* v, int n, double min, double max) {
    v->n = n;
    v->data = (double*)malloc(n * sizeof(double));
    for(int i = 0; i < n; i++)
        v->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
}

void m_zero_init(matrix* m, int n) {
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
}

void m_rand_init(matrix* m, int n, double min, double max) {
    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));

    for(int i = 0; i < n * n; i++)
        m->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
}

void m_id_init(matrix* m, int n) {
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
    for(int i = 0; i < n; i++)
        m_set(m, i, i, 1.0);
}

void m_rand_lower_init(matrix* m, int n, double min, double max) {
    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    double num;

    for(int f = 0; f < n * n; f++) {
        if(f/n<f%n) num = 0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }
}

void m_rand_upper_init(matrix* m, int n, double min, double max) {
    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    int num;

    for(int f = 0; f < n * n; f++) {
        if(f/n>f%n) num = 0.0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }
}

void m_rand_diag_init(matrix* m, int n, double min, double max) {
    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));
    double num;

    for(int f = 0; f < n * n; f++) {
        if(f/n!=f%n) num = 0.0;
        else num = min + (max - min) * rand() / (double)RAND_MAX;
        
        m_set(m, f/n, f%n, num);
    }
}

// getters and setters

int v_at(vector* v, int i) {
    if(i>= v->n) {
        fprintf(stderr, "v_at::Index %d out of bound %d\n", i, v->n);
        exit(1);
    }
    return v->data[i];
}

double m_at(matrix* m, int i, int j) {
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "m_at::Index %d or %d out of bounds %d\n", i, j, m->n);
        exit(1);
    }
    return m->data[i * m->n + j];
}

void v_set(vector* v, int i, double x) {
    if(i >= v->n) {
        fprintf(stderr, "v_set::Index %d out of bounds %d\n", i, v->n);
        exit(1);
    }
    v->data[i] = x;
}

void m_set(matrix* m, int i, int j, double x) {
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "m_set::Index %d or %d out of bound %d\n", i, j, m->n);
        exit(1);
    }
    m->data[i * m->n + j] = x;
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

void v_scalar_mult(vector* v, double c) {
    int n = v->n;
    for(int i = 0; i < n; i++) {
        v->data[i] *= c;
    }
}

void v_mult(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n) {
        fprintf(stderr, "v_mult::Different vector dimension: %d and %d\n", v1->n, v2->n);
        exit(1);
    }

    int n = v1->n;
    v_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] * v2->data[i];
    }
}

void v_add(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n) {
        fprintf(stderr, "v_add::Different vector dimensions: %d and %d\n", v1->n, v2->n);
        exit(1);
    }

    int n = v1->n;
    v_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] + v2->data[i];
    }
}

// matrix operations

void m_mult(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n) {
        fprintf(stderr, "m_mult::Different matrix dimensions: %d and %d\n", m1->n, m2->n);
        exit(1);
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
}

void m_add(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n) {
        fprintf(stderr, "m_add::Different matrix dimensions: %d and %d\n", m1->n, m2->n);
        exit(1);
    }

    int n = m1->n;
    m_zero_init(out, n);

    for(int i = 0; i < n * n; i++)
        out->data[i] = m1->data[i] + m2->data[i];
}

// matrix-vector multiplication

void mv_mult(matrix* m, vector* v, vector* out) {
    if(m->n != v->n ) {
        fprintf(stderr, "mv_mult::Incompatible dimensions for matrix-vector multiplication\n");
        exit(1);
    }

    int n = m->n;
    double sum;
    v_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        sum = 0.0;
        for(int j = 0; j < n; j++)
            sum += m_at(m, i, j) * v_at(v, j);

        v_set(out, i, sum);
    }
}

// matrix manipulation

void m_swap_rows(matrix* m, int r1, int r2) {
    if(r1 >= m->n || r2 >= m->n) {
        fprintf(stderr, "Row index out of bounds\n");
        exit(1);
    }

    int n = m->n;
    double temp;

    for(int j = 0; j < n; j++) {
        temp = m_at(m, r1, j);
        m_set(m, r1, j, m_at(m, r2, j));
        m_set(m, r2, j, temp);
    }
}

void m_transpose(matrix* m, matrix* out) {
    if(m->n != out->n) {
        fprintf(stderr, "Incompatible dimensions for transpose\n");
        exit(1);
    }
    
    int n = m->n;
    m_zero_init(out, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            m_set(out, j, i, m_at(m, i, j));
        }
    }
}

void m_remove_cross(matrix* m, int row, int col, matrix* out) {
    if(row >= m->n || col >= m->n) {
        fprintf(stderr, "m_remove_cross::Indices %d, %d out of bounds %d\n", row, col, m->n);
        exit(1);
    }

    int n = m->n;
    int g = 0;
    m_zero_init(out, n-1);

    for(int f=0; f<n*n; f++) {
        if(f/n!=row && f%n!=col)
            out->data[g++] = m->data[f];
    }
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
void solve_diag(matrix* A, vector* x, vector* b) {
    if(A->n != x->n || A->n != b->n) {
        fprintf(stderr, "solve_diag::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return;
    }

    int n = A->n;
    for(int i = 0; i < n; i++) {
        if(m_at(A, i, i) == 0.0) {
            fprintf(stderr, "solve_diag::Zero diagonal element at index %d\n", i);
            return;
        }
        v_set(x, i, v_at(b, i) / m_at(A, i, i));
    }
}

// solve Ax = b where A is orthogonal, that is: A^T A = I, which implies that A^T = A^-1
// therefore, x = A^-1 b = A^T b
void solve_orthogonal(matrix* A, vector* x, vector* b) {
    if(A->n != x->n || A->n != b->n) {
        fprintf(stderr, "solve_orthogonal::Incompatible dimensions. A:%d, b:%d\n", A->n, b->n);
        return;
    }

    int n = A->n;
    matrix A_T;
    m_transpose(A, &A_T);
    mv_mult(&A_T, b, x);
    free(A_T.data);
}

// solve Ax = b where A is lower triangular, using forward substitution. invariant:
// x_i = (b_i - sum_{j=0}^{i-1} A_{ij} x_j) / A_{ii}
void solve_lower_triangular(matrix* A, vector* x, vector* b) {
    int n = A->n;
    for(int i = 0; i < n; i++) {
        double sum = 0.0;
        for(int j = 0; j < i; j++) {
            sum += m_at(A, i, j) * v_at(x, j);
        }
        v_set(x, i, (v_at(b, i) - sum) / m_at(A, i, i));
    }
}

// solve Ax = b where A is upper triangular, using backward substitution. invariant:
// x_i = (b_i - sum_{j=i+1}^{n-1} A_{ij} x_j) / A_{ii}
void solve_upper_triangular(matrix* A, vector* x, vector* b) {
    int n = A->n;
    for(int i = n-1; i >= 0; i--) {
        double sum = 0.0;
        for(int j = i+1; j < n; j++) {
            sum += m_at(A, i, j) * v_at(x, j);
        }
        v_set(x, i, (v_at(b, i) - sum) / m_at(A, i, i));
    }
}