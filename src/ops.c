#include<stdlib.h>
#include<stdio.h>
#include "../include/matrix.h"
#include "../include/vector.h"

// initializers

void v_zero_init(vector* v, int n) {
    v->n = n;
    v->data = (double*)calloc(n, sizeof(double));
}

void v_rand_init(vector* v, int n, double min, double max) {
    v->n = n;
    v->data = (double*)malloc(n * sizeof(double));
    for(int i = 0; i < n; i++) {
        v->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
    }
}

void m_zero_init(matrix* m, int n) {
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
}

void m_rand_init(matrix* m, int n, double min, double max) {
    m->n = n;
    m->data = (double*)malloc(n * n * sizeof(double));

    for(int i = 0; i < n * n; i++) {
        m->data[i] = min + (max - min) * rand() / (double)RAND_MAX;
    }
}

void m_id_init(matrix* m, int n) {
    m->n = n;
    m->data = (double*)calloc(n * n, sizeof(double));
    for(int i = 0; i < n; i++) {
        m_set(m, i, i, 1.0);
    }
}

// getters and setters

int v_at(vector* v, int i) {
    if(i>= v->n) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    return v->data[i];
}

double m_at(matrix* m, int i, int j) {
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    return m->data[i * m->n + j];
}

void v_set(vector* v, int i, double x) {
    if(i >= v->n) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    v->data[i] = x;
}

void m_set(matrix* m, int i, int j, double x) {
    if(i >= m->n || j >= m->n) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    m->data[i * m->n + j] = x;
}

// vector operations

void v_scalar_mult(vector* v, double c) {
    int n = v->n;
    for(int i = 0; i < n; i++) {
        v->data[i] *= c;
    }
}

void v_mult(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n || v1->n != out->n) {
        fprintf(stderr, "Incompatible vector dimensions\n");
        exit(1);
    }
    int n = v1->n;
    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] * v2->data[i];
    }
}

void v_add(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n || v1->n != out->n) {
        fprintf(stderr, "Incompatible vector dimensions\n");
        exit(1);
    }
    int n = v1->n;
    for(int i = 0; i < n; i++) {
        out->data[i] = v1->data[i] + v2->data[i];
    }
}

// matrix operations

void m_mult(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n || m1->n != out->n) {
        fprintf(stderr, "Incompatible matrix dimensions\n");
        exit(1);
    }
    int n = m1->n;
    double sum;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum = 0.0;
            for(int k = 0; k < n; k++) {
                sum += m_at(m1, i, k) * m_at(m2, k, j);
            }
            m_set(out, i, j, sum);
        }
    }
}

void m_add(matrix* m1, matrix* m2, matrix* out) {
    if(m1->n != m2->n || m1->n != out->n) {
        fprintf(stderr, "Incompatible matrix dimensions\n");
        exit(1);
    }
    int n = m1->n;
    for(int i = 0; i < n * n; i++) {
        out->data[i] = m1->data[i] + m2->data[i];
    }
}

// matrix-vector multiplication

void mv_mult(matrix* m, vector* v, vector* out) {
    if(m->n != v->n || m->n != out->n) {
        fprintf(stderr, "Incompatible dimensions for matrix-vector multiplication\n");
        exit(1);
    }
    int n = m->n;
    double sum;

    for(int i = 0; i < n; i++) {
        sum = 0.0;
        for(int j = 0; j < n; j++) {
            sum += m_at(m, i, j) * v_at(v, j);
        }
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
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            m_set(out, j, i, m_at(m, i, j));
        }
    }
}

