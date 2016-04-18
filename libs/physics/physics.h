/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca para o calculo de formulas fisicas
 *  Vamos usar o mesmo principio da maca:
 *  https://goo.gl/N8afFg
 *
 ******************************************************************************/

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "../math/vector.h"
#include "../graphs/shape.h"

#define G 6.67408e-11

struct basicbody {
    double mass;
    Vector position, speed, acel;
};
typedef struct basicbody *BasicBody;

struct body {
    struct basicbody bbody;
    Vector ang_position, ang_speed, ang_acel;
    /* Vector ang_speed;*/
    Shape shape;
};
typedef struct body *Body;

/* Retorna um novo vetor contendo a posicao do centro de 
 * massa */ 
Vector center_of_mass (Body a, Body b);

/* retorna o centro de massa de um vetor de corpos */
Vector center_of_mass_array (Body *bodies, int N);

/* Calcula a forca que o corpo b aplica em a,
 * Retorna um vetor de forcas */
Vector gravitational_force (Body a, Body b);

/* Calcula a aceleracao que o corpo b aplica em a,
 * Retorna um vetor de forcas. Aceleracao de a */
Vector gravitational_acel (Body a, Body b);

/* Realiza uma forca f no corpo c durante sec segundos
 * Atualiza o corpo. */
void act_force (Body c, Vector f, double sec);

/* Desaloca um corpo */
void body_delete (Body a);

/* aloca espaco para um corpo */
Body body_new ();

/* adiciona massa a um corpo */
void body_mass (Body b, double m);

/* adiciona a posicao a um corpo */
void body_pos (Body b, Vector p);

/* adiciona a velocidade a um corpo */
void body_spe (Body b, Vector p);

/* adiciona a aceleracao a um corpo */
void body_acel (Body b, Vector p);

#endif
