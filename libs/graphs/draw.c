/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Desenho de elementos na cena
 *
 ******************************************************************************/

#include "draw.h"

/* imagem de background */
static Image back = NULL;
static Image logo = NULL;
static Image right = NULL;
static Image left = NULL;
static Image life_bar = NULL;
static Image fuel_bar = NULL;
static Image speed_bar = NULL;
static Image pause = NULL;
static Image over1 = NULL;
static Image over2 = NULL;
static Image both = NULL;

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
        zoom = img->zoom;

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
        if (tmp != NULL && tmp->shape != NULL && tmp->body != NULL) {
            ang = body_ang_position_degrees (tmp->body);
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

void draw_over1 () {
    Vector tmp;
    tmp = vector_zeros (2);
    if (over1 == NULL) {
        over1 = image_create (LOST1_IMAGE);
        image_load (over1);
        image_zoom (over1, 50);
    }
    tmp->data[0] = 0;
    tmp->data[1] = -OPENGL_SCALE/2;
    draw2d_image (over1, tmp, 0);
    vector_delete(tmp);
}

void draw_over2 () {
    Vector tmp;
    tmp = vector_zeros (2);
    if (over2 == NULL) {
        over2 = image_create (LOST2_IMAGE);
        image_load (over2);
        image_zoom (over2, 50);
    }
    tmp->data[0] = 0;
    tmp->data[1] = -OPENGL_SCALE/2;
    draw2d_image (over2, tmp, 0);
    vector_delete(tmp);
}

void draw_both () {
    Vector tmp;
    tmp = vector_zeros (2);
    if (both == NULL) {
        both = image_create (BOTH_LOST_IMAGE);
        image_load (both);
        image_zoom (both, 50);
    }
    tmp->data[0] = 0;
    tmp->data[1] = -OPENGL_SCALE/2;
    draw2d_image (both, tmp, 0);
    vector_delete(tmp);
}

void draw_pause () {
    Vector tmp;
    tmp = vector_zeros (2);
    if (pause == NULL) {
        pause = image_create (PAUSE_IMAGE);
        image_load (pause);
        image_zoom (pause, 25);
    }
    tmp->data[0] = 0;
    tmp->data[1] = -OPENGL_SCALE/2;
    draw2d_image (pause, tmp, 0);
    vector_delete(tmp);
}

void draw_logo () {
    if (logo == NULL) {
        logo = image_create (LOGO_IMAGE);
        image_load (logo);
    }
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    image_set_texture (logo);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-logo->w/2, OPENGL_SCALE-logo->h+15);
    glTexCoord2f(1.0, 1.0); glVertex2f(+logo->w/2, OPENGL_SCALE-logo->h+15);
    glTexCoord2f(1.0, 0.0); glVertex2f(+logo->w/2, OPENGL_SCALE+15);
    glTexCoord2f(0.0, 0.0); glVertex2f(-logo->w/2, OPENGL_SCALE+15);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glFlush();
    glPopMatrix();
}

void draw_painel (float width, float height,
    double life1, double fuel1, double speed1,
    double life2, double fuel2, double speed2,
    Image ship1, double ang1, Image ship2, double ang2) {
    double x, y;
    double l = width/height*OPENGL_SCALE;
    Vector tmp;
    tmp = vector_zeros (2);
    if (left == NULL) {
        right = image_create (RIGHT_PANEL_IMAGE);
        image_load (right);
        left = image_create (LEFT_PANEL_IMAGE);
        image_load (left);

        life_bar = image_create (LIFE_BAR_IMAGE );
        image_load (life_bar);
        fuel_bar = image_create (FUEL_BAR_IMAGE);
        image_load (fuel_bar);
        speed_bar = image_create (SPEED_BAR_IMAGE);
        image_load (speed_bar);
    }

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    image_set_texture (left);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-10-l, -OPENGL_SCALE);
    glTexCoord2f(1.0, 1.0); glVertex2f(-10-l+left->w, -OPENGL_SCALE);
    glTexCoord2f(1.0, 0.0); glVertex2f(-10-l+left->w, -OPENGL_SCALE+left->h);
    glTexCoord2f(0.0, 0.0); glVertex2f(-10-l, -OPENGL_SCALE+left->h);
    glEnd();

    image_set_texture (right);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(+10+l-right->w, -OPENGL_SCALE);
    glTexCoord2f(1.0, 1.0); glVertex2f(+10+l, -OPENGL_SCALE);
    glTexCoord2f(1.0, 0.0); glVertex2f(+10+l, -OPENGL_SCALE+right->h);
    glTexCoord2f(0.0, 0.0); glVertex2f(+10+l-right->w, -OPENGL_SCALE+right->h);
    glEnd();

    x = 420;
    y = 129;
    image_set_texture (life_bar);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-l+x, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*life1, 1.0); glVertex2f(-l+x+(life_bar->w*life1), -OPENGL_SCALE+y);
    glTexCoord2f(1.0*life1, 0.0); glVertex2f(-l+x+(life_bar->w*life1), -OPENGL_SCALE+life_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-l+x, -OPENGL_SCALE+life_bar->h+y);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-x+l, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*life2, 1.0); glVertex2f(-x+l-(life_bar->w)*life2, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*life2, 0.0); glVertex2f(-x+l-(life_bar->w)*life2, -OPENGL_SCALE+life_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-x+l, -OPENGL_SCALE+life_bar->h+y);
    glEnd();

    x = 420;
    y = 68;
    image_set_texture (fuel_bar);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-l+x, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*fuel1, 1.0); glVertex2f(-l+x+(fuel_bar->w*fuel1), -OPENGL_SCALE+y);
    glTexCoord2f(1.0*fuel1, 0.0); glVertex2f(-l+x+(fuel_bar->w*fuel1), -OPENGL_SCALE+fuel_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-l+x, -OPENGL_SCALE+fuel_bar->h+y);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-x+l, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*fuel2, 1.0); glVertex2f(-x+l-(fuel_bar->w)*fuel2, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*fuel2, 0.0); glVertex2f(-x+l-(fuel_bar->w)*fuel2, -OPENGL_SCALE+fuel_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-x+l, -OPENGL_SCALE+fuel_bar->h+y);
    glEnd();

    x = 420;
    y = 7;
    image_set_texture (speed_bar);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-l+x, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*speed1, 1.0); glVertex2f(-l+x+(speed_bar->w*speed1), -OPENGL_SCALE+y);
    glTexCoord2f(1.0*speed1, 0.0); glVertex2f(-l+x+(speed_bar->w*speed1), -OPENGL_SCALE+speed_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-l+x, -OPENGL_SCALE+speed_bar->h+y);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 1.0); glVertex2f(-x+l, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*speed2, 1.0); glVertex2f(-x+l-(speed_bar->w)*speed2, -OPENGL_SCALE+y);
    glTexCoord2f(1.0*speed2, 0.0); glVertex2f(-x+l-(speed_bar->w)*speed2, -OPENGL_SCALE+speed_bar->h+y);
    glTexCoord2f(0.0, 0.0); glVertex2f(-x+l, -OPENGL_SCALE+speed_bar->h+y);
    glEnd();

    tmp->data[0] = -l+160;
    tmp->data[1] = -OPENGL_SCALE+165;
    draw2d_image (ship1, tmp, ang1);

    tmp->data[0] = l-160;
    tmp->data[1] = -OPENGL_SCALE+165;
    draw2d_image (ship2, tmp, ang2);

    glDisable(GL_TEXTURE_2D);

    glFlush();
    glPopMatrix();
    vector_delete(tmp);
}

void draw_bar (double x, double y, double width, double height, double cr,
              double cg, double cb, double p) {
    int m = 5;

    glBegin(GL_QUADS);
    glColor4f(1,1,1, 0.5);
    glVertex2f (x,y);
    glVertex2f (x + width, y);
    glVertex2f (x + width, y + height);
    glVertex2f (x, y + height);
    glEnd ();

    if (p > 0) {
        glBegin(GL_QUADS);
        glColor4f(cr,cg,cb, 0.8);
        glVertex2f(x+m,y+m);
        glVertex2f(x+p*width - m + 1, y + m);
        glVertex2f(x+p*width - m + 1, y + height - m + 1);
        glVertex2f(x + m, y+height - m + 1);
        glEnd();
    }
    glColor4f(1,1,1,1);

}

void draw_nbar (double x, double y, double width, double height, int val, 
                int max) {

    double m = 5, sum;
    int i;

    glBegin(GL_QUADS);
    glColor4f(1,1,1, 0.5);
    glVertex2f (x,y);
    glVertex2f (x + width, y);
    glVertex2f (x + width, y + height);
    glVertex2f (x, y + height);
    glEnd ();

    sum = x + m;
    width = width - m - 1;

    for (i = 0; i < val; i++) {
        glBegin(GL_QUADS);
        glColor4f(0,0,1, 0.8);
        glVertex2f(sum, y + m - 1);
        glVertex2f(sum+width/max - 3, y + m - 1);
        glVertex2f(sum+width/max - 3, y + height - m + 1);
        glVertex2f(sum, y + height - m + 1);
        glColor4f(1,1,1,1);
        glEnd();
        sum += width/max;
    }

}
