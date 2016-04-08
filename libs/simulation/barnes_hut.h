/* Biblioteca para calcular posicao dos corpos apos t 
 * intervalode tempo. Veja mais informações sobre o
 * algoritmo em: http://arborjs.org/docs/barnes-hut */

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
