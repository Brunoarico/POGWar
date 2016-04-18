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


Shape Circle (double r, int n) {
    double i;
    int j;
	
    Shape circle = malloc (sizeof (Shape));
	 circle->N = n; 
	 circle->pontos = malloc (n * sizeof (Vector));

	 for (i = 0; i < n; i++)
		 pontos[i] = vector_zeros (2);
    
    //printf(" n = %d r = %f \n", n, r);
    circle->pontos = n;
    for (i = 0, j = 0; i < 2 * M_PI  ; j++, i = i + 2 * M_PI / n) {
        circle->data[j][0] = r * cos(i);
        circle->data[j][1] = r * sin(i);
	 //printf("%f %f %f\n",i*180/M_PI, circle->data[j][0], circle->data[j][1]);
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








