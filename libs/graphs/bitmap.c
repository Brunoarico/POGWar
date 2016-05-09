/* Baseado em 
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
https://github.com/olikraus/u8glib/wiki/fontsize
https://71squared.com/blog/what-is-a-bitmap-font
http://kvazars.com/littera/
*/
#include "bitmap.h"
Font initText2D (char * texturePath) {
    Font font;
    FILE *infofile;
    char img[256];
    int id, i;

    infofile = fopen(texturePath, "rb");
    fscanf(infofile, "%s", img);
    font = malloc (sizeof (struct font));
    printf("%s\n", img);
    font->img = image_create ("fonts/basic.png");
    printf("%s\n", font->img->filename);

    for (i = 0; i < 256; ++i) {
        font->x[i] = 0;
        font->y[i] = 0;
        font->height[i] = 0;
        font->width[i] = 0;
        font->xoffset[i] = 0;
        font->yoffset[i] = 0;
        font->xadvance[i] = 0;
    }

    while (fscanf(infofile, "\nchar id=%d", &id) > 0) {
        fscanf(infofile, " x=%d y=%d", &font->x[id], &font->y[id]);
        fscanf(infofile, " width=%d", &font->width[id]);
        fscanf(infofile, " height=%d", &font->height[id]);
        fscanf(infofile, " xoffset=%d", &font->xoffset[id]);
        fscanf(infofile, " yoffset=%d", &font->yoffset[id]);
        fscanf(infofile, " xadvance=%d", &font->xadvance[id]);
    }
    fclose (infofile);
    return font;
}

/* i e valor inteiro do caracter */
static void printletter (Font f, int i, double x, double y, double h) {
    double ax, ay, aw, ah;

    ax = f->x[i]/(float)f->img->w;
    ay = f->y[i]/(float)f->img->h;
    aw = f->width[i]/(float)f->img->w + ax;
    ah = f->height[i]/(float)f->img->h + ay;

    glPushMatrix();
    glTranslatef (x + f->xoffset[i]*h, y-f->yoffset[i]*h, 0.0);
    /* glRotatef(angle, 0, 0, 1); */
    glBegin(GL_POLYGON);

    glTexCoord2f(ax, ah); 
    glVertex2f(0, -h*f->height[i]);
    glTexCoord2f(aw, ah); 
    glVertex2f(h*f->width[i], -h*f->height[i]);
    glTexCoord2f(aw, ay); 
    glVertex2f(h*f->width[i], 0);
    glTexCoord2f(ax, ay); 
    glVertex2f(0, 0);
    
    glEnd();
    glFlush();
    glPopMatrix();
}

void printText2D (Font f, char * text, double x, double y, double h) {
    double tmpx, tmpy;
    int p = 0;
    tmpx = x;
    tmpy = y;
    if (f->img->w == 0) image_load (f->img);
    glEnable(GL_TEXTURE_2D);
    image_set_texture (f->img);
    glPushMatrix();
    while (text[p] != '\0') {
        if (text[p] == '\n') {
            tmpy += h;
            tmpx = x;
            continue;
        }
        printletter (f, (int)text[p], tmpx, tmpy, h);
        tmpx += f->xoffset[(int)text[p]]*h;
        tmpx += f->xadvance[(int)text[p]]*h;
        p++;
    }
    glDisable(GL_TEXTURE_2D);
}

