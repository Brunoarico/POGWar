#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phisics.h"
#include "utils.h"
#include "body.h"

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
    
    printf("%d %f %f\n", j, planet->pt[j][0], planet->pt[j][1]);
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


int main () {
  int tempo, n = 5, i;
  corpo **necrot;
  float MP, RP, m1, m2, x1, x2, y1, y2, vx1, vx2, vy1, vy2;
  char na1, na2;

  for (i = 0; i < n; i++)
    necrot = malloc (n * sizeof(corpo*));
  
  scanf("%f", &RP);
  scanf("%f", &MP);
  
  necrot[0] = newPlanet ( RP, MP);
 
  scanf("%d", &tempo);
  
  scanf("%c", &na1);
  scanf("%f", &m1);
  scanf("%f", &x1);
  scanf("%f", &y1);
  scanf("%f", &vx1);
  scanf("%f", &vy1);
  
  necrot[1] = newShip (na1, x1, y1, vx1, vy1, m1);
  
  scanf("%c", &na2);
  scanf("%f", &m2);
  scanf("%f", &x2);
  scanf("%f", &y2);
  scanf("%f", &vx2);
  scanf("%f", &vy2);
  
  necrot[2] = newShip (na2, x2, y2, vx2, vy2, m2);
  
  
  return EXIT_SUCCESS;
  
}  
