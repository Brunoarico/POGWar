/* Biblioteca pa calculo de formulas fisicas */
/* Vamos usar o mesmo principio da maca:
 *  https://goo.gl/N8afFg
 */

#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define G 6.674E-11 
struct body {
    double mass;
    Vector lin_position, lin_speed, lin_acel;
    /* Vector ang_speed;
     * Shape shape; */
};
typedef struct body *Body;

/* Retorna um novo vetor contendo a posicao do centro de massa */ 
Vector center_of_mass (Body a, Body b);

/* Calcula a forca que que b corpo aplica em a,
 * Retorna um vetor de forcas */
Vector gravitational_force (Body a, Body b);
 
#endif
