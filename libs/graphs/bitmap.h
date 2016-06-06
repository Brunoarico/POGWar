/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface para renderizar textos na tela
 *
 *   Baseado em 
 *   http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
 *   https://github.com/olikraus/u8glib/wiki/fontsize
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "../graphs/image.h"

/*struct que guarda propriedades de um elemento fonte na tela, um texto*/
struct font {
    Image img;
    int x[256];
    int y[256];
    int height[256];
    int width[256];
    int xoffset[256];
    int yoffset[256];
    int xadvance[256];
};
typedef struct font *Font;

/*inicializar um texto*/
Font initText2D (char * texturePath);

/*renderiza um texto*/
void printText2D (Font f, char * text, double x, double y, double h);

/*desaloca um texto*/
void deleteText2D (Font j);
