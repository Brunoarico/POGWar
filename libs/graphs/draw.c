#include "draw.h"

static Image back = NULL;

void draw2d_shape (Shape s, Vector position, double angle) {
	int i;
    double x, y;
    x = position->data[0];
    y = position->data[1];

    glPushMatrix();
    glTranslatef (x, y, 0.0);
    glRotatef(angle, 0, 0, 1);

    
    glBegin(GL_LINE_LOOP); 
    for (i = 0; i < s->size; i++) {
        glVertex2f(s->points[i]->data[0],s->points[i]->data[1]);
    }
    glEnd();
    
    glFlush();
    glPopMatrix();
}

void draw2d_image (Image img, Vector position, double angle) {
    double x, y, img_radio, zoom;

    x = position->data[0];
    y = position->data[1];

    if (img != NULL) {
        if (img->w == 0) {
            image_load (img);
        }
        img_radio = (img->w/(float)img->h);
        zoom = OPENGL_SCALE*img->zoom;

        glPushMatrix();
        glTranslatef (x, y, 0.0);
        glRotatef(angle, 0, 0, 1);
        glEnable(GL_TEXTURE_2D);
        image_set_texture (img);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 1.0); glVertex2f(-zoom*img_radio, -zoom);
        glTexCoord2f(1.0, 1.0); glVertex2f(zoom*img_radio, -zoom);
        glTexCoord2f(1.0, 0.0); glVertex2f(zoom*img_radio, zoom);
        glTexCoord2f(0.0, 0.0); glVertex2f(-zoom*img_radio, zoom);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    
        glFlush();
        glPopMatrix();
    }
}

void draw_objects () {
    int i;
    double ang;
    Object tmp;
    for (i = 0; i < obj_numberof (); i++) {
        tmp = obj_get (i);
        ang = body_ang_position_degress (tmp->body);
        if (tmp != NULL && tmp->shape != NULL && tmp->body != NULL) {
            if (SHOW_GL_LINE_LOOP || tmp->img == NULL) {
                draw2d_shape (tmp->shape, body_posg (tmp->body), ang);
            }
            draw2d_image (tmp->img, body_posg (tmp->body), ang);
        }
    }
}

void draw_back () {
    float img_radio;
    if (back == NULL) {
        back = image_create (BACKGROUD_IMAGE);
        image_load (back); 
    }
    img_radio = (back->w/(float)back->h);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, back->texture);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0*img_radio*OPENGL_SCALE, -1.0*OPENGL_SCALE);
    glTexCoord2f(1.0, 1.0); glVertex2f(1.0*OPENGL_SCALE*img_radio, -1.0*OPENGL_SCALE);
    glTexCoord2f(1.0, 0.0); glVertex2f(1.0*OPENGL_SCALE*img_radio, 1.0*OPENGL_SCALE);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0*OPENGL_SCALE*img_radio, 1.0*OPENGL_SCALE);

    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
   
}
