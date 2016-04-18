/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/

#include "shape.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../math/vector.h"
#define M_PI 3.14159265358979323846

Shape Circle (double r, int n) {
    double i;
    int j;
	
    Shape circle = malloc (sizeof (Shape));
	 circle->N = n; 
	 circle->pontos = malloc (n * sizeof (Vector));

	 for (j = 0; j < n; j++)
		 circle->pontos[j] = vector_zeros (2);
    
    /*printf(" n = %d r = %f \n", n, r);*/
    
    for (i = 0, j = 0; i < 2 * M_PI  ; j++, i = i + 2 * M_PI / n) {
        circle->pontos[j]->data[0] = r * cos(i);
        circle->pontos[j]->data[1] = r * sin(i);
	 /*printf("%f %f %f\n",i*180/M_PI, circle->data[j][0], circle->data[j][1]);*/
    }
    return circle;
}

void rotate_shape (Shape s, int ang) {
	 int i;
	 for (i = 0; i < s->N; i++)
	 	  vector2D_rotate (s->pontos[i], ang);
}

void move_shape (Shape s, Vector desloc) {
	int i;
	for (i = 0; i < s->N; i++)
		vector_add (s->pontos[i], desloc);
}








