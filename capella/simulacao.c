#include <stdio.h>
#include "physics.h"
#include "moviments.h"

Body body_add2d (double mass, double x, double y, double vx, double vy) ;

int main (int argc, char *argv[]) {
    double planet_size, stime; /* duracao da simulacao */
    double shotlife;
    int shotnumbers, i;
    double mass, x, y, vx, vy;
    double interval;
    char nave1, nave2;
    Body corpos[256];
    int N = 0;

    sscanf(argv[1], "%lf", &interval);

    scanf ("%lf %lf %lf", &planet_size, &mass, &stime);
    corpos[0] = body_add2d (mass, 0, 0, 0, 0);

    scanf ("%s %lf %lf %lf %lf %lf", &nave1, &mass, &x, &y, &vx, &vy);
    corpos[1] = body_add2d (mass, x, y, vx, vy);

    scanf ("%s %lf %lf %lf %lf %lf", &nave2, &mass, &x, &y, &vx, &vy);
    corpos[2] = body_add2d (mass, x, y, vx, vy);
    N = 3;

    scanf ("%d %lf", &shotnumbers, &shotlife);
    for (i = 0; i < shotnumbers; i++) {
        scanf ("%s %lf %lf %lf %lf %lf", &nave2, &mass, &x, &y, &vx, &vy);
        corpos[3 + i] = body_add2d (mass, x, y, vx, vy);
        N = 4 + i;
    }

    while (stime > 0) {
        moviments_update (corpos, N, interval);
        stime -= interval;
    }

    for (i = 0; i < N; i++) {
        if (argc == 2) {
            printf("m: %e \t", corpos[i]->mass);
            printf("x: %e \t", corpos[i]->lin_position->data[0]);
            printf("y: %e \t", corpos[i]->lin_position->data[1]);
            printf("vx: %e \t", corpos[i]->lin_speed->data[0]);
            printf("vy: %e \n", corpos[i]->lin_speed->data[1]);
        }

        printf("%lf ", corpos[i]->lin_position->data[0]);
        printf("%lf\n", corpos[i]->lin_position->data[1]);
    }

    return 0;
}

Body body_add2d (double mass, double x, double y, double vx, double vy) {
    Vector position, speed, acel;
    Body b;
    b = body_new();
    speed = vector_zeros (2);
    position = vector_zeros (2);
    acel = vector_zeros (2);
    position->data[0] = x;
    position->data[1] = y;
    speed->data[0] = vx;
    speed->data[1] = vy;
    b->mass = mass;
    b->lin_position = position;
    b->lin_speed = speed;
    b->lin_acel = acel;
    return b;
}

