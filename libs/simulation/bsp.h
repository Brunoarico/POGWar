/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/

#ifndef _BSP_H
#define _BSP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../math/vector.h"
#include "../physics/physics.h"
#include "../graphs/shape.h"
#include "../simulation/vertices.h"
#include "../engine/object.h"

/* Essa função recebe um ponteiro de uma função e o chama.
   Essa função chamada recebe dois inteiros (ids) dos objetos
   colididos. 
*/ 
void BSP(void (*impact)());

#endif
