#include "draw.h"
#include "../engine/object.h"

void draw2d_shape (Shape s, Vector position) {
	int i;
    double x, y;
    x = position->data[0];
    y = position->data[1];
    glPushMatrix();
    glTranslatef (x, y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < s->size; i++) {
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
            draw2d_shape (tmp->shape, body_posg (tmp->body));
        }
    }
}
