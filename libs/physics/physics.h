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
#include "../../config.h"

/* Contante gravitacional */
#ifndef GRAV_CONST
 	#define G 6.67408e-11
#else
 	#define G GRAV_CONST
#endif

/* Estrutura que representa um corpo basico contem posicao, velocidade
   e aceleracao */
struct basicbody {
    double mass;
    Vector position, speed, acel;
};
typedef struct basicbody *BasicBody;

/* Estrutura que representa um corpo, possui alem de um corpo basico, 
   os vetores de posicao angular, velocidade angular e aceleracao angular */
struct body {
    struct basicbody bbody;
    Vector ang_position, ang_speed, ang_acel;
    Vector force;
    double torque;
};
typedef struct body *Body;

/* Retorna um novo vetor contendo a posicao do centro de 
 * massa entre dois corpos a e b */ 
Vector center_of_mass (Body a, Body b);

/* Retorna o centro de massa de um vetor de corpos bodies de tamanho N */
Vector center_of_mass_array (Body *bodies, int N);

/* Calcula a forca que o corpo b aplica em a,
 * Retorna um vetor de forcas */
Vector gravitational_force (Body a, Body b);

/* Calcula a aceleracao que o corpo b aplica em a,
 * Retorna um vetor de forcas. Aceleracao de a */
Vector gravitational_acel (Body a, Body b);

/* Realiza uma forca f no corpo c durante sec segundos
 * Atualiza o corpo. */
void act_force_center (Body c, Vector f, double sec);

/* Realiza uma forca f no corpo c durante sec segundos
 * Atualiza o corpo. Essa força é aplicada em p. Para
 * o caso gravitacional p = (0, 0) */
void act_force (Body c, double sec);
void body_add_force (Body a, Vector f, Vector p);

/* Desaloca um corpo a */
void body_delete (Body a);

/* Aloca espaco para um corpo retornando-o */
Body body_new ();

/* Modifica a massa do corpo b para m */
void body_mass (Body b, double m);

/* Modifica a posicao do corpo b para p */
void body_pos (Body b, Vector p);

/* Retorna a posicao do corpo b */
Vector body_posg (Body b);

/* Retorna a posicao angular de b em radianos */
double body_ang_position_degrees (Body b);

/* Modifica a velocidade do corpo b para p */
void body_spe (Body b, Vector p);

/* Modifica a velocidade angular do corpo b para vetor p */
void body_ang_spe (Body b, Vector p);

/* Modifica a velocidade angular do corpo b para p */
void body_ang_spe2d (Body b, double p);

/* Modifica a posicao angular do corpo b para p graus */
void body_pos2d_degree (Body b, double p);

/* Modifica a aceleracao do corpo b para p */
void body_acel (Body b, Vector p);

/* Retorna um corpo inicializado com massa mass, na posicao (x, y) com
   velocidade em x vx e velocidade em y vy */
Body body2d_new (double mass, double x, double y, double vx, 
                 double vy);

#endif
