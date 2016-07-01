/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface para desenhar elementos na cena
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

/* Desenha o shape s no plano na posicao position (angle em radianos) */
void draw2d_shape (Shape s, Vector position, double angle);

/* Desenha a imagem img no plano na posicao position (angle em radianos) */
void draw2d_image (Image img, Vector position, double angle);

/* Desenha todos os objetos no plano */
void draw_objects ();

/* Desenha o background da cena */
void draw_back ();
void draw_logo (float width, float height);

void draw_nbar (double x, double y, double width, double height, int val, 
                int max);

void draw_bar (double x, double y, double width, double height, double cr,
               double cg, double cb, double p);

#endif
