/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca para calcular posicao dos corpos apos t 
 *  intervalo de tempo. Veja mais informacoes sobre o
 *  algoritmo em: http://arborjs.org/docs/barnes-hut
 *
 ******************************************************************************/

#ifndef _MOVIMENTS_HUT_H
#define _MOVIMENTS_HUT_H

#include <stdio.h>
#include <stdlib.h>
#include "physics.h"
#include "vector.h"

void moviments_update (Body *bodies, int N, double interval);

#endif
