/* Biblioteca pa calculo de formulas fisicas */
/* Vamos usar o mesmo principio da maca:
 *  https://goo.gl/N8afFg
 */

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/* #define G 6.674E-11 */
#define G 1

struct body {
    double mass;
    Vector lin_position, lin_speed, lin_acel;
    /* Vector ang_speed;
     * Shape shape; */
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

/* Realiza uma forca f no corpo c durante sec segundos
 * Atualiza o corpo. */
void act_force (Body c, Vector f, double sec);

/* Desaloca um corpo */
void body_delete (Body a);

/* aloca espaco para um corpo */
Body body_new ();

#endif

