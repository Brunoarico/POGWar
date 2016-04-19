/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "../math/vector.h"
#include "../graphs/shape.h"
#include "../engine/object.h"

void draw2d_shape (Shape s, Vector position);

void draw_objects ();

#endif
