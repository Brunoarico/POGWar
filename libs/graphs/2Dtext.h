/* Baseado em 
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
https://github.com/olikraus/u8glib/wiki/fontsize
*/
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "../graphs/image.h"
struct font {
    Image img;
    int x[256];
    int y[256];
    int height[256];
    int width[256];
};
typedef struct font *Fonte;

void initText2D (char * texturePath);
void printText2D (char * text, double x, double y, double h);
