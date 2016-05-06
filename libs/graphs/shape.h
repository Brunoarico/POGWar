/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface que manipula um shape (contorno de algum objeto)
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

/* Estrutura que representa um shape que e composto 
   por uma colecao de vetores */
struct shape {
    Vector *points;
    int size; /* Numero de pontos */
};
typedef struct shape *Shape;

/* Cria um Shape circular com raio r com resolucao n */
Shape shape2d_circle (double r, int n);

/* Inicializa a estrutura shape e retorna seu ponteiro */
Shape shape_new ();

/* Rotaciona o Shape s em ang radianos */
void shape_rotate (Shape s, int ang);

/* Realiza a translacao do Shape s no plano, onde desloc
   representa o vetor deslocamento */
void shape_move (Shape s, Vector desloc);

/* Adiciona o ponto representado pelo vetor 
   v ao Shape s */
void shape_add_point (Shape s, Vector v);

/* Desaloca a estrutura s */
void shape_delete (Shape s);

/* Copia um Shape s, retornando a copia */
Shape shape_copy (Shape s);

#endif
