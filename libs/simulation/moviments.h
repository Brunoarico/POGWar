/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface que cuida do calculo dos movimentos dos corpos
 *
 ******************************************************************************/

#ifndef _MOVIMENTS_HUT_H
#define _MOVIMENTS_HUT_H

#include <stdio.h>
#include <stdlib.h>
#include "../physics/physics.h"
#include "../math/vector.h"
#include "../engine/object.h"

/* Atualiza o movimento dos corpos apos um intervalo de tempo interval */
void moviments_update (double interval);

/* Recebe o tamanho máximo da tela */
void check_screen_edges (double x, double y);

#endif
