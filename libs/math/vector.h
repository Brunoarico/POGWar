/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca destinada a operacoes vetoriais
 *
 ******************************************************************************/

#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Estrutura que representa um vetor */
struct vector {
    double *data;
    unsigned int size;
};
typedef struct vector *Vector;

/* calcula o norma ao quadrado de a */
double vector_mag2 (Vector a);

/* Calcula o norma de um vetor */
double vector_mag (Vector a);

/* Realiza a = a - b */
void vector_sub (Vector a, Vector b);

/* Realiza a = a + b */ 
void vector_add (Vector a, Vector b);

/* Realiza a = x * a */
void vector_scale (Vector a, double x);

/* Multiplica componente por componente a = a * b */
void vector_mul (Vector a, Vector b);

/* Retorno um vetor de tamanho size de 0 */
Vector vector_zeros (int size);

/* Desaloca o vetor a */
void vector_delete (Vector a);

/* Copia b para a */
void vector_copy (Vector a, Vector b);

/* cria um elemento identico a a */
Vector vector_copy2 (Vector a);

/* Rotaciona o vetor a em ang radianos */
void vector2D_rotate (Vector a, double ang);

Vector vector2D_new (double x, double y);

/* Desloca o vetor a em desloc*/
void vector2D_move (Vector a, Vector desloc); 
 
#endif
