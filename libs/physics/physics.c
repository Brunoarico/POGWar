/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Calculo de formulas fisicas
 *  https://goo.gl/N8afFg
 *
 ******************************************************************************/

#include "physics.h"

Vector center_of_mass (Body a, Body b) {
    Vector tmp, res;
    double total_mass_i;
    total_mass_i = 1.0/(a->bbody.mass + b->bbody.mass);
    res = vector_zeros (a->bbody.position->size);
    tmp = vector_zeros (a->bbody.position->size);

    vector_copy (tmp, a->bbody.position);
    vector_scale (tmp, a->bbody.mass);
    vector_copy (res, b->bbody.position);
    vector_scale (res, b->bbody.mass);
    vector_add (res, tmp);
    vector_scale (res, total_mass_i);
    vector_delete (tmp);
    return res;
}

Vector center_of_mass_array (Body *bodies, int N) {
    Vector tmp, res;
    int i;
    double total_mass_i = 0.0;
    for (i = 0; i < N; i++)
        total_mass_i += bodies[i]->bbody.mass;
    total_mass_i = 1.0/(total_mass_i);
    res = vector_zeros (bodies[0]->bbody.position->size);
    tmp = vector_zeros (bodies[0]->bbody.position->size);
    
    for (i = 0; i < N; i++) {
        if (bodies[i] == NULL) continue;
        vector_copy (tmp, bodies[i]->bbody.position);
        vector_scale (tmp, bodies[i]->bbody.mass);
        vector_add (res, tmp);
    }

    vector_scale (res, total_mass_i);
    vector_delete (tmp); 
    return res;
}

Vector gravitational_acel (Body a, Body b) {
    Vector res;
    double force, tmp;
    force = G * b->bbody.mass;
    res = vector_zeros (a->bbody.position->size);
    vector_copy (res, a->bbody.position);
    vector_sub (res, b->bbody.position);

    tmp = vector_norm2 (res);
    if (tmp == 0) {
        fprintf (stderr, "gravitational_force: ");
        fprintf (stderr, "Division by zero.\n");
        /* exit(EXIT_FAILURE); */
        tmp = 0.00001;
    }
    force /= tmp;
    vector_scale (res, force);
    return res;
}

Vector gravitational_force (Body a, Body b) {
    Vector res;
    res = gravitational_acel (a, b);
    vector_scale (res, a->bbody.mass);
    return res;
}

void act_force (Body c, double sec) {
    Vector at, v0;
    double ang_at;
    at = NULL;

    /* para o caso linear */
    /* Impoem aceleracao */

    at = vector_zeros (c->force->size);
    if (c->bbody.mass > 0) {
        vector_copy (at, c->force);
        vector_scale (at, 1.0/c->bbody.mass);
        vector_copy (c->bbody.acel, at);
        vector_copy (c->force, vector_zeros (c->force->size));
    }

    /* Calcula nova velocidade */
    v0 = vector_zeros (c->force->size);
    vector_copy (v0, c->bbody.speed);
    vector_copy (at, c->bbody.acel);
    vector_scale (at, sec);
    vector_add(c->bbody.speed, at);

    /* calcula nova posicao */
    vector_scale (v0, sec);
    vector_add(c->bbody.position, v0);
    vector_scale (at, sec/2.0);
    vector_add(c->bbody.position, at);

    /* para o caso angular */
    /* Impoem aceleracao */
    /* Calcula nova velocidade */
    /* calcula nova posicao */

    vector_delete (at);
    at = vector_zeros (1);

    if (c->bbody.mass > 0) {
        ang_at = c->torque;
        ang_at /= M_PI/4.0*c->bbody.mass;
        c->ang_acel->data[0] = ang_at;
        at->data[0] = ang_at;
        c->torque = 0;
    }

    /* Calcula nova velocidade */
    vector_delete (v0);
    v0 = vector_zeros (1);
    vector_copy (v0, c->ang_speed);
    vector_copy (at, c->ang_acel);
    vector_scale (at, sec);
    vector_add(c->ang_speed, at);

    /* calcula nova posicao */
    vector_scale (v0, sec);
    vector_add(c->ang_position, v0);
    vector_scale (at, sec/2.0);
    vector_add(c->ang_position, at);

    vector_delete (at);
    vector_delete (v0);
}

void body_add_force (Body a, Vector f, Vector p) {
    /* vamos separar a linear da angular */
    Vector lin, ang, tmp;
    double norm;

    vector2D_rotate (p, a->ang_position->data[0]);

    tmp = vector_copy2 (p);
    norm = vector_norm (tmp);
    if (norm > 0) {
        vector_scale(tmp, 1.0/vector_norm (tmp));

        lin = vector_copy2 (tmp);

        vector_mul (lin, f); /* projecao em paralela a p */

        ang = vector_copy2 (f);
        vector_sub (ang, lin); /* projecao em perpendicular a p */

        a->torque -= p->data[0]*ang->data[1];
        a->torque += p->data[1]*ang->data[0];

        vector_delete (lin);
        vector_delete (ang);
    }
    vector_add(a->force, f);

    vector_delete (tmp);
}

void body_delete (Body a) {
    if (a != NULL) {
        vector_delete (a->bbody.position);
        vector_delete (a->bbody.speed);
        vector_delete (a->bbody.acel);
        vector_delete (a->ang_position);
        vector_delete (a->ang_speed);
        vector_delete (a->ang_acel);
        free (a);
    }    
}

Body body_new () {
    Body new;
    new = malloc (sizeof (struct body));
    new->ang_position = 0;
    return new;
}

void body_mass (Body b, double m) {
    b->bbody.mass = m;
}

void body_pos (Body b, Vector p) {
    b->bbody.position = p;
}

Vector body_posg (Body b) {
    return b->bbody.position;
}

void body_spe (Body b, Vector p) {
    b->bbody.speed = p;
}

void body_ang_spe (Body b, Vector p) {
    b->ang_speed = p;
}

void body_ang_spe2d (Body b, double p) {
    Vector a = vector_zeros (1);
    a->data[0] = p;
    vector_delete (b->ang_speed);
    b->ang_speed = a;
}

void body_acel (Body b, Vector p) {
    b->bbody.acel = p;
}

Body body2d_new (double mass, double x, double y, double vx, 
                 double vy) {
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
    body_mass (b, mass);
    body_pos (b, position);
    body_spe (b, speed);
    body_acel (b, acel);
    b->ang_position = vector_zeros (1);
    b->ang_acel = vector_zeros (1);
    b->force = vector_zeros (2);
    b->torque = 0;
    body_ang_spe(b, vector_zeros (1));
    return b;
}

double body_ang_position_degrees (Body b) {
    return b->ang_position->data[0]*180.0/M_PI;
}

void body_pos2d_degree (Body b, double p) {
    b->ang_position->data[0] = p*M_PI/180.0;
}
