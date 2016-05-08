/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface para manipulacao de vertices
 *
 ******************************************************************************/

#ifndef _VERTICES_H
#define _VERTICES_H

#include <stdio.h>
#include <stdlib.h>
#include "../math/vector.h"
#include "../engine/object.h"

/* Estrutura que representa um vertice */
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

/* cria uma pilha de vertices */
Vertices vertices_new ();

/* insere um vertice em uma pilha */
void vertices_insert (Vertices stack, Vertice v);

/* retorna o tamanho de uma pilha de vertices */
int vertices_size (Vertices stack);

/* desaloca uma pilha de vertices */
void vertices_delete (Vertices v);

/* retorna um vertice de indice i em uma pilha de vertices */
Vertice vertices_get (Vertices stack, int i);

/* retorna um vertice composto pelos vetores a e b, alem do objeto o */
Vertice vertice_new (Vector a, Vector b, Object o);

/* desaloca um vertice */
void vertice_delete (Vertice v);

#endif
