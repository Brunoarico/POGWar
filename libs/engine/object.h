/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "../math/vector.h"
#include "../graphs/shape.h"
#include "../physics/physics.h"

struct ship {
    double fuel;
    double life;
};
typedef struct ship *Ship;

struct shot {
    double disapear_time;
    double damage;
};
typedef struct shot *Shot;

struct object {
    Body body;
    Shape shape;
    Shot shot;
    Ship ship;
    int id;
};
typedef struct object *Object;

unsigned int obj_new ();

Object obj_get (int i);

void obj_delete (int i);

void obj_delete_all ();

/* Numero total de objetos */
unsigned int obj_numberof ();

#endif
