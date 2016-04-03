/* Biblioteca para calcular posicao dos corpos apos t 
 * intervalode tempo. Veja mais informações sobre o
 * algoritmo em: http://arborjs.org/docs/barnes-hut */

#ifndef _MOVIMENTS_HUT_H
#define _MOVIMENTS_HUT_H

#include <stdio.h>
#include <stdlib.h>
#include "physics.h"
#include "vector.h"

void moviments_update (Body *bodies, int N, double interval);

#endif
