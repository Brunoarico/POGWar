/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface para manipular as imagens
 *
 ******************************************************************************/
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <GLFW/glfw3.h>
#include "../../config.h"

/* Estrutura criada para uma imagem e trabalhada nessa interface */
struct image {
    int w, h;
    GLuint texture;
    double zoom;
    char *filename;
};
typedef struct image *Image;

/* Inicializa a estrutura basica de uma imagem que representara o arquivo 
   de nome filename */
Image image_create (char *filename);

/* Carrega a estrutura img com as propriedades do arquivo de imagem */
void image_load (Image img);

/* Desaloca a estrutura img */
void image_delete (Image img);

/* Modifica o zoom referente a img para z */
void image_zoom (Image img, double z);

/* Seta a textura da imagem */
void image_set_texture (Image img);

#endif
