/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface que manipula objetos da cena
 *
 *  object.c contem um vetor de objetos que indicam todos os objetos da cena
 *
 ******************************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "../math/vector.h"
#include "../graphs/shape.h"
#include "../graphs/image.h"
#include "../physics/physics.h"
#include "../../config.h"


/* Estrutura que representa uma nave */
struct ship {
    double fuel;
    double life;
    char jet1, jet2, jet3; /* armazena se o motor esta ligado*/
    char gum1; /* armazen se a arma 1 está lugada */
    double last_shot_gum1;
    Image shot_gum1;
};
typedef struct ship *Ship;

/* Estrutura que representa um tiro */
struct shot {
    double disapear_time;
    int id_origem;
};
typedef struct shot *Shot;

/* Estrutura basica que representa qualquer objeto da cena */
enum otype {SHOT, SHIP, PLANET};
typedef enum otype OType;

/* Estrutura basica que representa qualquer objeto da cena */
struct object {
    Body body;
    Shape shape;
    union {
        Shot shot;
        Ship ship;
    } info;
    OType type;
    Image img;
    int id;
    int kill; /* marca se um objeto deve ser destruido */
};
typedef struct object *Object;

/* Cria um novo objeto retornando o seu id */
unsigned int obj_new (OType type);

/* Retorna o objeto de id i */
Object obj_get (int i);

/* Desaloca o objeto de id i */
void obj_delete (int i);

/* Desaloca todos os objetos */
void obj_delete_all ();

/* Numero total de objetos */
unsigned int obj_numberof ();

/* Toma a atitude sobre os objetos que se tocaram. a e b são ids */
/* No momento só imprime na tela. */ 
void obj_impact (int a, int b);

/* determina de qual objeto vem o tiro */
void shot_origem (unsigned int origen, unsigned int shot);

/* Verifica tempo de vida e condicoes de existencia dos objetos*/
void obj_validate ();

#endif
