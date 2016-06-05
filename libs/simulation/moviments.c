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

void moviments_update () {
    Vector tmp, zero;
    int i, j;
    Object tmpobji, tmpobjj;
    zero = vector_zeros (2);

    for (i = 0; i < obj_numberof (); i++) {
        tmpobji = obj_get (i);

        if (tmpobji == NULL || tmpobji->body == NULL) continue;
        if (tmpobji->body->bbody.mass == 0.0) continue;

        for (j = 0; j < obj_numberof (); j++) {
            tmpobjj = obj_get (j);
            if (i == j || tmpobjj == NULL) continue;
            if (tmpobjj->body == NULL) continue;
            tmp = gravitational_force (tmpobji->body, tmpobjj->body);
            body_add_force (tmpobjj->body, tmp, zero);
            vector_delete (tmp);
        }
    }
    vector_delete (zero);
}

void moviments_act (double interval) {
    int i;
    Vector tmp;
    for (i = 0; i < obj_numberof (); i++) {
        if (obj_get (i) == NULL) continue;
        if (obj_get (i)->type == SHIP) { /* verifica turbina */
            if (obj_get (i)->info.ship->jet1 && 
                    obj_get (i)->body->bbody.mass > INI_MASS*MIN_MASS) {
                obj_get (i)->body->ang_position->data[0] += interval * PROPELLANT_SPEED;
                obj_get (i)->body->bbody.mass -= PROPELLANT_MASSRATE*interval;
            }
            if (obj_get (i)->info.ship->jet2 && 
                    obj_get (i)->body->bbody.mass > INI_MASS*MIN_MASS) {
                obj_get (i)->body->ang_position->data[0] -= interval * PROPELLANT_SPEED;
                obj_get (i)->body->bbody.mass -= PROPELLANT_MASSRATE*interval;
            }
            if (obj_get (i)->info.ship->jet3 && 
                    obj_get (i)->body->bbody.mass > INI_MASS*MIN_MASS) {
                tmp = vector_zeros (2);
                tmp->data[1] = interval * PROPELLANT_SPEED * 100;
                vector2D_rotate (tmp, obj_get (i)->body->ang_position->data[0]);
                vector_add(obj_get (i)->body->bbody.position, tmp);
                obj_get (i)->body->bbody.mass -= 2*PROPELLANT_MASSRATE*interval;
            }
        }
        act_force (obj_get (i)->body, interval);
    }
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
            *bx = -*bx;
        }
        if (*by > y || *by < -y) {
            *by = -*by;
        }
    }
}