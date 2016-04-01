#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#define G 6.67E-11
#include "body.h"



void up_velocity(corpo *C, float dt) {
  C->vel[0] += C->a[0]*dt;
  C->vel[1] += C->a[1]*dt;
}

void up_position(corpo *C, float dt) {
  C->pos[0] += C->vel[0] * dt + 0.5 * C->a[0] * pow(dt,2);
  C->pos[1] += C->vel[1] * dt + 0.5 * C->a[1] * pow(dt,2);
}

float orbtVel (float r, float M) { //velocidade de orbita
    return sqrt (G * M/r);
}
    
    
