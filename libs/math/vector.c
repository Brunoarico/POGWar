/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca destinada a operacoes vetoriais 
 *
 ******************************************************************************/


#include "vector.h"

double vector_norm2 (Vector a) {
    int i;
    double sum = 0.0; 
    for (i = 0; i < a->size; i++)
        sum += a->data[i] * a->data[i];
    return sum;
}

double vector_norm (Vector a) {
    return sqrt (vector_norm2 (a));
}

void vector_sub (Vector a, Vector b) {
    int i;    
    for (i = 0; i < a->size; i++)
        a->data[i] -= b->data[i];
}

void vector_add (Vector a, Vector b) {
    int i;    
    for (i = 0; i < a->size; i++)
        a->data[i] += b->data[i];
}

void vector_mul (Vector a, Vector b) {
    int i;    
    for (i = 0; i < a->size; i++)
        a->data[i] *= b->data[i];
}

void vector_scale (Vector a, double x) {
    int i;    
    for (i = 0; i < a->size; i++)
        a->data[i] *= x;
}

Vector vector_zeros (int size) {
    int i;
    double *data;
    Vector tmp;
    tmp = malloc (sizeof (struct vector));
    data = malloc (sizeof (double) * size);
    tmp->data = data;
    tmp->size = size;
    for (i = 0; i < size; i++) data[i] = 0;
    return tmp;
}

void vector_delete (Vector a) {
    if (a != NULL) { 
        free (a->data);
        free (a);
    }
}

void vector_copy (Vector a, Vector b) {
   int i;
   for (i = 0; i < a->size; i++)
        a->data[i] = b->data[i]; 
}

void vector2D_rotate (Vector a, double ang) {
    double x = a->data[0]; 
    double y = a->data[1];
    a->data[0] = cos (ang) * x - sin (ang) * y;
    a->data[1] = sin (ang) * x + cos (ang) * y;
}
