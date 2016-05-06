/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca para calcular posicao dos corpos apos t 
 *  intervalo de tempo. Veja mais informações sobre o
 *  algoritmo em: http://arborjs.org/docs/barnes-hut 
 *  (EM CONSTRUCAO)
 *
 ******************************************************************************/

#ifndef _BURNES_HUT_H
#define _BURNES_HUT_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h> /* pegar tamanho double */
#include "physics.h"
#include "vector.h"

#define ALPHA 0.5

struct node {
    struct node *nodes[4];
    double bounds[5];
    struct body btmp;
    Body b;
    char has_children;
};
typedef struct node *Node;

void bh_moviments_update (Body *bodies, int N, double interval);

#endif
