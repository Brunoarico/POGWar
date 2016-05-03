#include "draw.h"
#include "../engine/object.h"

static Image back = NULL;

void draw2d_shape (Shape s, Vector position, double angle) {
	int i;
    double x, y;
    x = position->data[0];
    y = position->data[1];
/*
    GLuint tex;
    GLint uniform_mytexture;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    float pixels[] = {
        5.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   5.0f, 0.0f, 0.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, 3,2,2, 0, GL_RGB, GL_FLOAT,pixels);
*/
/*
    if (img == NULL) {
        img = image_read ("img/teste.jpg"); 
    }*/

    glPushMatrix();
    glTranslatef (x, y, 0.0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_POLYGON); 
    /*glBindTexture(GL_TEXTURE_2D, tex);*/

    for (i = 0; i < s->size; i++) {
        if (i == 0) glTexCoord2d(0.0f, 0.0f);
        if (i == 1) glTexCoord2d(1.0f, 0.0f);
        if (i == 2) glTexCoord2d(1.0f, 1.0f);
        if (i == 3) glTexCoord2d(0.0f, 1.0f);
        glVertex2f(s->points[i]->data[0],s->points[i]->data[1]);
    }
   
    glEnd();
    glPopMatrix();
}

void draw_objects () {
    int i;
    Object tmp;
    for (i = 0; i < obj_numberof (); i++) {
        tmp = obj_get (i);
        if (tmp != NULL && tmp->shape != NULL && tmp->body != NULL) {
            draw2d_shape (tmp->shape, body_posg (tmp->body), 0);
        }
    }
}

void draw_back () {
    float img_radio;
    if (back == NULL) {
        back = image_read ("img/galaxy.jpg"); 
    }
    img_radio = (back->w/(float)back->h);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, back->texture);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-1000.0*img_radio, -1000.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(1000.0*img_radio, -1000.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(1000.0*img_radio, 1000.0);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1000.0*img_radio, 1000.0);

    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
   
}
