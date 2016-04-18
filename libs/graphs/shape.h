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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../math/vector.h"
#define M_PI 3.14159265358979323846

struct shape {
    Vector *pontos;
    int N; /* Numero de pontos */
};
typedef struct shape *Shape;

/* n eh a resolucao do circulo */
Shape Circle (double r, int n);

/* adiciona um ponto a v */
void add_point (Shape s, Vector v);

#endif
