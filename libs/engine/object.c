/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Manipula objetos da cena
 *
 *  Contem um vetor de objetos que indicam todos os objetos da cena
 *
 ******************************************************************************/

#include "object.h"

/* Vetor de ponteiros para objetos que guardam todos os objetos da cena */
static Object *AllObjects;

/* n numero de objetos, N tamanho de vetor */
static n = 0, N = 0;

static Ship chip_new () {
    Ship a;
    a = malloc (sizeof (struct ship));
    a->fuel = INI_FUEL;
    a->life = INI_LIFE;
    a->jet1 = 0;
    a->jet2 = 0;
    a->gum1 = 0;
    a->last_shot_gum1 = 0;
    return a;
}

static Shot shot_new () {
    Shot a;
    a = malloc (sizeof (struct shot));
    return a;
}

static Object obj_add (OType type, int id) {
    Object a;
    a = malloc (sizeof (struct object));
    a->type = type;
    a->shape = NULL;
    a->body = NULL;
    if (type == SHIP) {
        a->info.ship = chip_new ();
    } else if (type == SHOT) {
        a->info.shot = shot_new ();
    }
    a->img = NULL;
    a->id = id;
    a->kill = 0;
    return a;
}

void shot_origem (unsigned int origen, unsigned int shot) {
    if (obj_get(shot)->type == SHOT) {
        obj_get(shot)->info.shot->id_origem = origen;
        obj_get(shot)->info.shot->disapear_time= glfwGetTime()+SHOT_DURATION;
        if (obj_get(origen)->type == SHIP) {
            obj_get(origen)->info.ship->last_shot_gum1 = glfwGetTime();
        }
    }
}

unsigned int obj_new (OType type) {
    int i;
    /* verifica a existencia de lugares vazios no vetor */
    for (i = 0; i < n; i++) {
        if (AllObjects[i] == NULL) {
            AllObjects[i] = obj_add (type, i);
            return i;
        }
    }
    n += 1;
    if (n > N) {
        if (n == 1) {
            N = 1;
            AllObjects = malloc (N * sizeof (Object));
        } else {
            N *= 2;
            AllObjects = realloc(AllObjects, N * sizeof (Object));
        }
    }
    AllObjects[n - 1] = obj_add (type, n - 1);
    return n - 1;
}

Object obj_get (int i) {
    return AllObjects[i];
}

void obj_delete (int i) {
    if (AllObjects[i] == NULL) return;
    shape_delete (AllObjects[i]->shape);
    body_delete (AllObjects[i]->body);

    if (AllObjects[i]->type != SHOT)
        image_delete (AllObjects[i]->img);
    free (AllObjects[i]);
    AllObjects[i] = NULL;
}

unsigned int obj_numberof () {
    return n;
}

void obj_delete_all () {
    int i;
    for (i = 0; i < obj_numberof (); i++)
        obj_delete (i);
    n = 0;
    N = 0;
    free (AllObjects);
}

void obj_impact (int a, int b) {
    if (AllObjects[a] != NULL && AllObjects[b] != NULL
        && !AllObjects[a]->kill && !AllObjects[b]->kill) {
        if (AllObjects[a]->type == SHOT
            && AllObjects[b]->type == PLANET)
            AllObjects[a]->kill = 1;
        if (AllObjects[b]->type == SHOT
            && AllObjects[a]->type == PLANET)
            AllObjects[b]->kill = 1;

        if (AllObjects[a]->type == SHIP
            && AllObjects[b]->type == PLANET) {
            AllObjects[a]->info.ship->life = 0;
            AllObjects[a]->kill = 1;
        }
        if (AllObjects[b]->type == SHIP
            && AllObjects[a]->type == PLANET) {
            AllObjects[b]->info.ship->life = 0;
            AllObjects[b]->kill = 1;
        }

        if (AllObjects[b]->type == SHIP
            && AllObjects[a]->type == SHOT
            && AllObjects[b]->id != AllObjects[a]->info.shot->id_origem) {
            AllObjects[b]->info.ship->life -= SHOT_DEMAGE;
            AllObjects[a]->kill = 1;
        }
        if (AllObjects[a]->type == SHIP
            && AllObjects[b]->type == SHOT
            && AllObjects[a]->id != AllObjects[b]->info.shot->id_origem) {
            AllObjects[a]->info.ship->life -= SHOT_DEMAGE;
            AllObjects[b]->kill = 1;
        }
        if (AllObjects[a]->type == SHIP && AllObjects[b]->type == SHIP
            && AllObjects[a]->id != AllObjects[b]->info.shot->id_origem) {
            AllObjects[a]->info.ship->life = 0;
            AllObjects[b]->info.ship->life = 0;
        }
    }
}

void obj_validate () {
    int i, objid;
    Object entidade, tmp;
    double t = glfwGetTime();
    double delta;
    BasicBody rasc;
    Vector va, vb, vc;

    for (i = 0; i < n; i++) {
        entidade = AllObjects[i];
        if (entidade == NULL) continue;
        if (entidade->kill) {
            obj_delete (i);
            continue;
        }
        switch(entidade->type) {
            case SHOT:
                if (entidade->info.shot->disapear_time < t)
                    obj_delete (i);
                break; /* optional */
            
            case SHIP:
                if (entidade->info.ship->life <= 0) {
                    obj_delete (i);
                } else if (AllObjects[i]->info.ship->gum1) {
                    delta = t - AllObjects[i]->info.ship->last_shot_gum1;
                    if (delta > SHOT_INTERVAL) {
                        rasc = &AllObjects[i]->body->bbody;
                        vb = vector_zeros (2);
                        va = vector_copy2 (rasc->speed);
                        vc = vector_zeros (2);

                        vc->data[1] = SHOT_SPEED;
                        vector2D_rotate (vc, 
                            AllObjects[i]->body->ang_position->data[0]);
                        vector_add (va, vc);

                        vb->data[1] = 100;
                        vector2D_rotate (vb, 
                            AllObjects[i]->body->ang_position->data[0]);
                        vector_add (vb, rasc->position);

                        objid = obj_new (SHOT);
                        tmp = obj_get(objid);
                        tmp->body = body2d_new (
                            SHOT_MASS, 
                            vb->data[0], 
                            vb->data[1], 
                            va->data[0], 
                            va->data[1],
                            200);
                        tmp->shape = shape2d_circle (15, 3);
                        tmp->img = AllObjects[i]->info.ship->shot_gum1;
                        shot_origem (i, objid);
                        vector_delete (va);
                        vector_delete (vb);
                        vector_delete (vc);
                    }
                }
                break; /* optional */

            case PLANET:
                break; /* optional */

        }

       
    }
}
