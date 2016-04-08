/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Biblioteca para o calculo de formulas fisicas
 *  Vamos usar o mesmo principio da maca:
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
        total_mass_i += bodies[i]->mass;
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

Vector gravitational_force (Body a, Body b) {
    Vector res;
    double force, tmp;
    force = G * a->bbody.mass * b->bbody.mass;
    res = vector_zeros (a->bbody.position->size);
    vector_copy (res, a->bbody.position);
    vector_sub (res, b->bbody.position);

    tmp = vector_norm2 (res);
    if (tmp == 0) {
        fprintf (stderr, "gravitational_force: ");
        fprintf (stderr, "Division by zero.\n");
        exit(EXIT_FAILURE);
    }
    force /= tmp;
    vector_scale (res, force);
    return res;
}

void act_force (Body c, Vector f, double sec) {
    Vector at, v0;
    at = vector_zeros (f->size);

    /* Impoem aceleracao */
    vector_copy (at, f);
    vector_scale (at, 1.0/c->bbody.mass);
    vector_copy (c->bbody.acel, at);

    /* Calcula nova velocidade */
    v0 = vector_zeros (f->size);
    vector_copy (v0, c->bbody.speed);
    vector_copy (at, c->bbody.acel);
    vector_scale (at, sec);
    vector_add(c->bbody.speed, at);

    /* calcula nova posicao */
    vector_scale (v0, sec);
    vector_add(c->bbody.position, v0);
    vector_scale (at, sec/2.0);
    vector_add(c->bbody.position, at);

    vector_delete (at);
    vector_delete (v0);
}

void body_delete (Body a) {
    if (a != NULL) {
        vector_delete (a->bbody.position);
        vector_delete (a->bbody.speed);
        vector_delete (a->bbody.acel);
        free (a);
    }    
}

Body body_new () {
    Body new;
    new = malloc (sizeof (struct body));
    return new;
}


void body_mass (Body b, double m) {
    b->bbody.mass = m;
}

void body_pos (Body b, Vector p) {
    b->bbody.position = p;
}

void body_spe (Body b, Vector p) {
    b->bbody.speed = p;
}

void body_acel (Body b, Vector p) {
    b->bbody.acel = p;
}
