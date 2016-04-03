#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phisics.h"
#include "utils.h"
#include "body.h"
#include <GL/glut.h>

corpo *newPlanet (float r, float m) {
  float i, **pt;
  int j;
  corpo *planet;
  planet = mallocc (sizeof(corpo));
  planet->pt = allocM (100, 2);
  planet->pos[0] = planet->pos[1] = 0;
  planet->vel[0] = planet->vel[1] = 0;
  planet->a[0] = planet->a[1] = 0;
  planet->mass = m;
  
  for (i = 0, j = 0; i <= 2 * M_PI ; i = i + M_PI/50, j++) {
    
    planet->pt[j][0] = r * cos(i);
    planet->pt[j][1] = r * sin(i);
  }
  return planet;
}

corpo *newShip (char s, float x, float y, float vx, float vy, float m) {
  float i;
  int j;
  corpo *ship;
  ship = mallocc (sizeof(corpo));
  ship->name = s;
  ship->pos[0] = x, ship->pos[1] = y;
  ship->vel[0] = vx, ship->vel[1] = vy;
  ship->a[0] = ship->a[1] = 0;
  ship->mass = m;
  ship->pt = allocM (3, 2);
  ship->pt[0][0] = x, ship->pt[0][1] = 100+y;
  ship->pt[1][0] = x+50,  ship->pt[1][1] = -100+y;
  ship->pt[2][0] = x+50,  ship->pt[2][1] = 100+y;
  return ship;
}

void update (corpo **v, int n, float dt) {
    float **m, f, ang;
    int i, j;
    
    m = allocM (n, 2);
    
    for (i = 1; i < n; i++) 
	for(j = 0; j < n; j++) 
	    if(i != j) {
		f = gravit (v[i], v[j]);
		ang = atan2 (v[i]->pos[1] - v[j]->pos[1], v[i]->pos[0] - v[j]->pos[0]);
		m[i][0]  += -f * cos (ang);
		m[i][1]  += -f * sin (ang);
	    }
    for (i = 1; i < n; i++) {
	up_acel (v[i], m[i]);
	up_velocity (v[i], dt);
	up_position (v[i], dt);
    }
    FreeM(m, n, 2);
}


int main (int narg, char* args[]) {
    int tempo, i, j;
    int k = 3;
    corpo **ne;
 
    for (i = 0; i < k; i++)
	ne = malloc (k * sizeof(corpo*));

    ne[0] = newPlanet(atof(args[1]), atof(args[2])); //gera o planeta

    tempo = atoi(args[3]); //pega o tempo
    
    for (i = 0, j = 1; j < 3 ; i = i + 6, j++) {//gera duas naves

	ne[j] = newShip(args[4+i][0], atof(args[6+i]), atof(args[7+i]), atof(args[8+i]), atof(args[9+i]),atof(args[5+i]));

	printf("%c %f %f %f %f %f \n", ne[j]->name, ne[j]->pos[0],  ne[j]->pos[1],  ne[j]->vel[0], ne[j]->vel[1], ne[j]->mass);
    }
    for(i=0; i < tempo; i++)   
    update (ne, k, 0.1);
  
    return EXIT_SUCCESS;
  
}  
