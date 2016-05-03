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
#include <jpeglib.h>
#include "../math/vector.h"
#include "../graphs/shape.h"
#include "../graphs/image.h"
#include "../engine/object.h"
#include "../../config.h"

void draw2d_shape (Shape s, Vector position, double angle);

void draw2d_image (Image img, Vector position, double angle);

void draw_objects ();

void draw_back ();

#endif
