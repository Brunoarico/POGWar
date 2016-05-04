/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Realiza o calculo das forcas que cada corpo sofre no sistema 
 *  pela gravidade e move eles de acordo com essa forca. Recebe os
 *  bodies e sua quantidade N e o intervalo de tempo de atuacao da
 *  forca
 *
 ******************************************************************************/
 
#include "moviments.h"

void moviments_update (double interval) {
    Vector *forces;
    Vector tmp;
    int i, j;
    Object tmpobji, tmpobjj;

    forces = malloc (sizeof (Vector) * obj_numberof ());
    for (i = 0; i < obj_numberof (); i++) {
        tmpobji = obj_get (i);

        if (tmpobji == NULL || tmpobji->body == NULL || tmpobji->body->bbody.mass == 0.0)
            continue;
        forces[i] = vector_zeros (2);

        for (j = 0; j < obj_numberof (); j++) {
            tmpobjj = obj_get (j);
            if (i == j || tmpobjj == NULL) continue;
            if (tmpobjj->body == NULL) continue;
            tmp = gravitational_force (tmpobjj->body, tmpobji->body);
            vector_add (forces[i], tmp);
            vector_delete (tmp);
        }
    }
    for (i = 0; i < obj_numberof (); i++) {
        tmpobji = obj_get (i);
        if (tmpobji == NULL || tmpobji->body == NULL || tmpobji->body->bbody.mass == 0.0)
            continue;
        tmp = vector_zeros (2);
        act_force (tmpobji->body, forces[i], tmp, interval);
        vector_delete (forces[i]);
    }
    free (forces);
}

void check_screen_edges (double x, double y) {
    int i;
    double *bx, *by;
    Object tmpobj;
    for (i = 0; i < obj_numberof (); i++) {
        tmpobj = obj_get (i);
        if (tmpobj == NULL || tmpobj->body == NULL ) continue;
        bx = &tmpobj->body->bbody.position->data[0];
        by = &tmpobj->body->bbody.position->data[1];
        if (*bx > x || *bx < -x) {
            *bx = -x;
        }
        if (*by > y || *by < -y) {
            *by = -y;
        }
    }
}
