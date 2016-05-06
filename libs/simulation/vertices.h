/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/

#ifndef _VERTICES_H
#define _VERTICES_H

#include <stdio.h>
#include <stdlib.h>
#include "../math/vector.h"
#include "../engine/object.h"

struct vertice {
    Vector a, b;
    Object o;
};
typedef struct vertice *Vertice;

struct vertices {
    Vertice *vertices;
    int n, N;
};
typedef struct vertices *Vertices;

Vertices vertices_new ();
void vertices_insert (Vertices stack, Vertice v);
int vertices_size (Vertices stack);
void vertices_delete (Vertices v);

Vertice vertices_get (Vertices stack, int i);
Vertice vertice_new (Vector a, Vector b, Object o);
void vertice_delete (Vertice v);

#endif
