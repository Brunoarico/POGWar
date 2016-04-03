#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phisics.h"
#include "utils.h"
#include "body.h"

float ***Dmatrix(int m, int n, int k) {
    
    float ***mat;
    int i, j, a;
    mat = mallocc (m * sizeof (float***));
    for (i = 0; i < m; i++){
	mat[i] = mallocc (n * sizeof (float**));
	for (j = 0; j < n; j++)
	    mat[i][j] = mallocc (k * sizeof (float*));
    }
    return mat;
}

void engine (corpo **v, int n) {
    float ***m, f, ang;
    int i, j;
    
    m = Dmatrix (n, n, 2);
    
    for (i = 0; i < n; i++) {
	for(j = i; j < n; j++) {
	    if (i == j) { 
	    	m[i][j][0] = m[i][j][1] = 0;
	    }
	    else {
	
		f = gravit (v[i], v[j]);
		
		ang = atan2 (v[i]->pos[1] - v[j]->pos[1], v[i]->pos[0] - v[j]->pos[0]);
		printf("%d\n",f);
		m[i][j][0] = m[j][i][0] = f  ;
		m[i][j][1]= m[j][i][1] = f ;
	    }
	}
	   
    }

    for (i = 0; i < n; i++){ 
	for(j = 0; j < n; j++)
	    printf("   %f %f   ",m[i][j][0], m[i][j][1]);
	printf("\n");
    }
}

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
    
    //printf("%d %f %f\n", j, planet->pt[j][0], planet->pt[j][1]);
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


int main (int narg, char* args[]) {
  int tempo, k = 3, i;
  corpo **n;
  float MP, RP, m1, m2, x1, x2, y1, y2, vx1, vx2, vy1, vy2;
  char na1, na2;

  for (i = 0; i < k; i++)
    n = malloc (k * sizeof(corpo*));
  

  
  n[0] = newPlanet ( atof(args[1]), atof(args[2]));
  printf("%f\n",n[0]->mass);
  n[1] = newShip (args[4][0], atof(args[6]), atof(args[7]), atof(args[8]), atof(args[9]), atof(args[5]));
 
  n[2] = newShip (args[10][0], atof(args[12]), atof(args[13]), atof(args[14]), atof(args[15]) , atof(args[11]));

  engine(n, k);
  
  
  return EXIT_SUCCESS;
  
}  
