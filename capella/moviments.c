#include "moviments.h"
/* realiza o calculo das forcas que cada corpo sfre no sistema 
 * pela gravidade e move eles de acordo com essa forca. Recebe os
 * bodies e sua quantidade N e o intervalo de tempo de atuação da
 * forca */ 
void moviments_update (Body *bodies, int N, double interval) {
    Vector *forces;
    Vector tmp;
    int i, j;
    forces = malloc (sizeof (Vector) * N);
    for (i = 0; i < N; i++) {
        if (bodies[i] == NULL) continue;
        forces[i] = vector_zeros (2);
        for (j = 0; j < N; j++) {
            if (i == j || bodies[j] == NULL) continue;
            tmp = gravitational_force (bodies[j], bodies[i]);
            vector_add (forces[i], tmp);
        }
    }
    for (i = 0; i < N; i++)
        if (bodies[i] == NULL) continue;
        else act_force (bodies[i], forces[i], interval);
}
