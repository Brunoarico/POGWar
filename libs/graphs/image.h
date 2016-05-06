/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <GLFW/glfw3.h>

struct image {
    int w, h;
    GLuint texture;
    double zoom;
    char *filename;
};
typedef struct image *Image;

Image image_create (char *filename);

void image_load (Image img);

void image_delete (Image img);

void image_zoom (Image img, double z);

void image_set_texture (Image img);

#endif
