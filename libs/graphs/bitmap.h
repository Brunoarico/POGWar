/* Baseado em 
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
https://github.com/olikraus/u8glib/wiki/fontsize
*/
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "../graphs/image.h"

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

Font initText2D (char * texturePath);
void printText2D (Font f, char * text, double x, double y, double h);
void deleteText2D (Font j);
