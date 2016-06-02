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

/* Estrutura que representa uma nave */
struct ship {
    double fuel;
    double life;
    unsigned int id;
};
typedef struct ship *Ship;

/* Estrutura que representa um tiro */
struct shot {
    double disapear_time;
    double damage;
    int id_origem;
};
typedef struct shot *Shot;

/* Estrutura basica que representa qualquer objeto da cena */
struct object {
    Body body;
    Shape shape;
    Shot shot;
    Ship ship;
    Image img;
    int id;
};
typedef struct object *Object;

/* Cria um novo objeto retornando o seu id */
unsigned int obj_new ();

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

<<<<<<< HEAD
/* Verifica tempo de vida */
void object_lifetime (double last_time); 

/*Cria uma nave*/
Ship Ship_new (int life, double mass, double x, double y, double vx, double vy, double angspd, double begang, char type);

/*Deleta uma nave*/
void delete_ship (unsigned int id);

/*dispara uma "bala"*/
void bullet (Ship nave);

=======
>>>>>>> parent of 83dfd40... Modificacoes aleatorias
#endif
