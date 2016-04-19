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
    stack->n += 1;
    if (stack->n > stack->N) {
        stack->N *= 2;
        stack->vertices = realloc(stack->vertices, stack->N * sizeof (Vertice));
    }
    stack->vertices[stack->n - 1] = v;
}

int vertices_size (Vertices stack) {
    return stack->n;
}

Vertice vertices_get (Vertices stack, int i) {
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
    free (v);
}

void vertices_delete (Vertices v) {
    free (v);
}

