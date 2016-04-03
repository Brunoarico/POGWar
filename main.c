#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "phisics.h"
#include "utils.h"
#include "body.h"
#include <GL/glut.h>

int k = 3;
corpo **ne;

void drawplanet (corpo *c) {
    glPushMatrix();
    glTranslatef (c->pos[0], c->pos[1], 0);
    glColor3f(1,0.8,0);
    glutSolidSphere(0.2,40,40);
    glPopMatrix();
    
}

void drawship (corpo *s){
    glPushMatrix ();
    glTranslatef (s->pos[0], s->pos[1], 0);
    glBegin (GL_POLYGON);	
    glColor3f (1, 0, 0);
    glVertex3f (0, -0.05, -1);
    glVertex3f (0, 0.05, -1);
    glVertex3f (0.05, 0, -1);
    glEnd ();
    glPopMatrix ();
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

void display() {
    int i;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
    glClearColor(0,0,1,0);

    drawship(ne[1]);
    
    drawship(ne[2]);
   
    drawplanet(ne[0]);
    
    update (ne, k, 0.01);
    printf("%f\n",orbtVel(0.5,500000));
    
    glutSwapBuffers();

   
}

int main (int narg, char* args[]) {
  int tempo, i;
  char na1, na2;

  for (i = 0; i < k; i++)
    ne = malloc (k * sizeof(corpo*));

  ne[0] = newPlanet(, 500000);

  ne[1] = newShip('A', -0.5, 0, 0, orbtVel(0.5,500000), 500000);

  ne[2] = newShip('B', 0.5, 0, 0, -orbtVel(0.5,500000), 500000);
      

  glutInit (&narg, args);

  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

  glutInitWindowSize (700,700);
    
  glutCreateWindow ("Teste");

  glutDisplayFunc (display);

  glutIdleFunc(display);

  glutMainLoop();

  

  return EXIT_SUCCESS;
  
}  
