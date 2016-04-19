/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#ifndef SHAPE_H
#define SHAPE_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../math/vector.h"

struct shape {
    Vector *points;
    int size; /* Numero de pontos */
};
typedef struct shape *Shape;

/* n eh a resolucao do circulo */
Shape shape2d_circle (double r, int n);

Shape shape_new ();

void shape_rotate (Shape s, int ang);

void shape_move (Shape s, Vector desloc);

/* adiciona um ponto a v  */
void shape_add_point (Shape s, Vector v);

void shape_delete (Shape s);

Shape shape_copy (Shape s);

#endif
