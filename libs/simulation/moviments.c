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
            vector2D_rotate (tmp, -1*tmpobjj->body->ang_position->data[0]);
            body_add_force (tmpobjj->body, tmp, zero);
            vector_delete (tmp);
        }
    }
    vector_delete (zero);
}

void moviments_act (double interval) {
    int i;
    Vector turbine_force = NULL;
    Vector frontal = NULL;
    Vector force = NULL;

    for (i = 0; i < obj_numberof (); i++) {
        if (obj_get (i) == NULL) continue;
        if (obj_get (i)->type == SHIP) { /* verifica turbina */
            turbine_force = vector_zeros (2);
            frontal = vector_zeros (2);
            force = vector_zeros (2);
            turbine_force->data[1] = 100*PROPELLANT_MASSRATE*PROPELLANT_SPEED;
            frontal->data[1] = -80*PROPELLANT_MASSRATE*PROPELLANT_SPEED;
            if (obj_get (i)->body->bbody.mass > INI_MASS*MIN_MASS) {
                if (obj_get (i)->info.ship->jet1 && obj_get (i)->info.ship->jet2) {
                    force->data[0] = 0;
                    force->data[1] = 0;
                    body_add_force (obj_get (i)->body, turbine_force, force);
                    body_add_force (obj_get (i)->body, turbine_force, force);
                    obj_get (i)->body->bbody.mass -= 2*PROPELLANT_MASSRATE*interval;
                } else {
                    if (obj_get (i)->info.ship->jet1) {
                        force->data[0] = 5;
                        force->data[1] = 40;
                        body_add_force (obj_get (i)->body, turbine_force, force);
                        obj_get (i)->body->bbody.mass -= PROPELLANT_MASSRATE*interval;
                    }else if (obj_get (i)->info.ship->jet2) {
                        force->data[0] = -5;
                        force->data[1] = 40;
                        body_add_force (obj_get (i)->body, turbine_force, force);
                        obj_get (i)->body->bbody.mass -= PROPELLANT_MASSRATE*interval;
                    }
                    if (obj_get (i)->info.ship->jet3) {
                        force->data[0] = 0;
                        force->data[1] = -40;
                        body_add_force (obj_get (i)->body, frontal, force);
                        obj_get (i)->body->bbody.mass -= PROPELLANT_MASSRATE*interval;
                    }
                }
            }      
            vector_delete(frontal);
            vector_delete(turbine_force);
            vector_delete(force);

           /* printf("%d\t", obj_get (i)->info.ship->jet1);
            printf("%d\t", obj_get (i)->info.ship->jet2);
            printf("%d\t", obj_get (i)->info.ship->jet3);*/
        }
        act_force (obj_get (i)->body, interval);
    }
    /*printf("\n");*/
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
