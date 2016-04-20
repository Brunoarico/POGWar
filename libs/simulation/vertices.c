/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#include "vertices.h"

/* Pilha de vertices */
Vertices vertices_new () {
    Vertices v;
    v = malloc(sizeof(struct vertices));
    v->vertices = malloc(sizeof(Vertice) * 2);
    v->N = 2;
    v->n = 0;
    return v;
}

void vertices_insert (Vertices stack, Vertice v) {
    if (v == NULL) return;
    stack->n += 1;
    if (stack->n > stack->N) {
        stack->N *= 2;
        stack->vertices = realloc(stack->vertices, stack->N * sizeof (Vertice));
    }
    stack->vertices[stack->n - 1] = v;
}

int vertices_size (Vertices stack) {
    if (stack == NULL) return 0;
    return stack->n;
}

Vertice vertices_get (Vertices stack, int i) {
    if (stack == NULL) return NULL;
    if (stack->vertices == NULL) return NULL;
    if (i < stack->n) return stack->vertices[i];
    return NULL;
}

Vertice vertice_new (Vector a, Vector b, Object o) {
    Vertice v;
    v = malloc(sizeof(struct vertice));
    v->o = o;
    v->a = a;
    v->b = b;
    return v;
}

void vertice_delete (Vertice v) {
    if (v == NULL) return;
    vector_delete (v->a);
    free (v);
}

void vertices_delete (Vertices v) {
    int i;
    if (v == NULL) return;
    for (i = 0; i < v->n; i++) {
        if (v->vertices[i] != NULL) 
            vertice_delete (v->vertices[i]);
        v->vertices[i] == NULL;
    }
    free (v->vertices);
    free (v);
}

