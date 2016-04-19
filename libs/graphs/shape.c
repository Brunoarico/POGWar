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

Shape shape2d_circle (double r, int n) {
    double i;
    int j;
    Vector tmp;
    Shape circle = shape_new ();
        
    for (i = 0, j = 0; i < 2 * M_PI  ; j++, i = i + 2 * M_PI / n) {
        tmp = vector_zeros (2);
        tmp->data[0] = r * cos(i);
        tmp->data[1] = r * sin(i);
        shape_add_point (circle, tmp);
    }
    return circle;
}

void shape_rotate (Shape s, int ang) {
    int i;
    for (i = 0; i < s->size; i++)
        vector2D_rotate (s->points[i], ang);
}

void shape_move (Shape s, Vector desloc) {
    int i;
    for (i = 0; i < s->size; i++)
        vector_add (s->points[i], desloc);
}

void shape_add_point (Shape s, Vector v) {
    s->size += 1;
    s->points = realloc(s->points, s->size * sizeof (Vector));
    s->points[s->size - 1] = v;
}

Shape shape_new () {
    Shape s = malloc (sizeof (Shape));
    s->size = 0; 
    s->points = NULL;
    return s;
}

void shape_delete (Shape s) {
    int i;
    for (i = 0; i < s->size; i++)
        vector_delete (s->points[i]);
    free (s->points);
    free (s);
}

Shape shape_copy (Shape s) {
    int i;
    Shape nova;
    nova = shape_new ();
    nova->points = malloc(s->size * sizeof (Vector));
    nova->size = s->size;
    for (i = 0; i < s->size; i++) 
        nova->points[i] = vector_copy2 (s->points[i]);
    return nova;
}
