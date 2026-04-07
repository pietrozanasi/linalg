#include<stdlib.h>
#include<stdio.h>
#include "../include/matrix.h"
#include "../include/vector.h"

// initializations

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
    for(int i = 0; i < v->n; i++) {
        v->data[i] *= c;
    }
}

void v_mult(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n || v1->n != out->n) {
        fprintf(stderr, "Incompatible vector dimensions\n");
        exit(1);
    }
    for(int i = 0; i < v1->n; i++) {
        out->data[i] = v1->data[i] * v2->data[i];
    }
}

void v_add(vector* v1, vector* v2, vector* out) {
    if(v1->n != v2->n || v1->n != out->n) {
        fprintf(stderr, "Incompatible vector dimensions\n");
        exit(1);
    }
    for(int i = 0; i < v1->n; i++) {
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
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double sum = 0.0;
            for(int k = 0; k < n; k++) {
                sum += m_at(m1, i, k) * m_at(m2, k, j);
            }
            m_set(out, i, j, sum);
        }
    }
}

void vm_mult(matrix* m, vector* v, vector* out) {
    if(m->n != v->n || m->n != out->n) {
        fprintf(stderr, "Incompatible dimensions for matrix-vector multiplication\n");
        exit(1);
    }
    int n = m->n;
    for(int i = 0; i < n; i++) {
        double sum = 0.0;
        for(int j = 0; j < n; j++) {
            sum += m_at(m, i, j) * v_at(v, j);
        }
        v_set(out, i, sum);
    }
}