#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define G 6.67E-11
#include "body.h"
#include "utils.h"

void up_velocity (corpo *C, float dt) {
  C->vel[0] += C->a[0] * dt;
  C->vel[1] += C->a[1] * dt;
  printf("v[0] = %.2f v[1] = %.2f \n", C->vel[0], C->vel[1]);
}

void up_position (corpo *C, float dt) {
  C->pos[0] += C->vel[0] * dt + 0.5 * C->a[0] * pow (dt, 2);
  C->pos[1] += C->vel[1] * dt + 0.5 * C->a[1] * pow (dt, 2);
  printf("s[0] = %.2f s[1] = %.2f \n", C->pos[0], C->pos[1]);
}

void up_acel (corpo *C, float *force) {
    printf("f[0] = %.2f f[1] = %.2f mass = %f \n", force[0], force[1], C->mass);
    C->a[0] = force[0]/C->mass;
    C->a[1] = force[1]/C->mass;
    printf("a[0] = %.2f a[1] = %.2f \n", C->a[0], C->a[1]);
}
    
float orbtVel (float r, float M) { //velocidade de orbita
    return sqrt (G * M/r);
}

float gravit (corpo *C1, corpo *C2) { //atração gravitacional
    //printf("M1 %f, M2 %f, dist %f result %f\n",C1->mass, C2->mass, distEucl (C1->pos, C2->pos), G * C1->mass * C2->mass/ pow (distEucl (C1->pos, C2->pos), 2));
    return G * C1->mass * C2->mass / pow (distEucl (C1->pos, C2->pos), 2);
}


    
    
