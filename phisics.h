#ifndef phisics
#define phisics

#include <stdio.h>
#include "body.h"

void up_velocity(corpo *C, float dt);

void up_position(corpo *C, float dt);

float orbtVel (float r, float M);

float gravit (corpo *C1, corpo *C2);

#endif
