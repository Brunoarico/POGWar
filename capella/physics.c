#include "physics.h"

Vector center_of_mass (Body a, Body b) {
    Vector tmp, res;
    double total_mass_i;
    total_mass_i = 1.0/(a->mass + b->mass);
    res = vector_zeros (a->lin_position->size);
    tmp = vector_zeros (a->lin_position->size);

    vector_copy (tmp, a->lin_position);
    vector_scale (tmp, a->mass);
    vector_copy(res, b->lin_position);
    vector_scale (res, b->mass);
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
    res = vector_zeros (bodies[0]->lin_position->size);
    tmp = vector_zeros (bodies[0]->lin_position->size);
    
    for (i = 0; i < N; i++) {
        if (bodies[i] == NULL) continue;
        vector_copy (tmp, bodies[i]->lin_position);
        vector_scale (tmp, bodies[i]->mass);
        vector_add (res, tmp);
    }

    vector_scale (res, total_mass_i);
    vector_delete (tmp); 
    return res;
}

Vector gravitational_force (Body a, Body b) {
    Vector res;
    double force;
    force = G * a->mass * b->mass;
    res = vector_zeros (a->lin_position->size);
    vector_copy (res, a->lin_position);
    vector_sub (res, b->lin_position);
    force /= vector_norm2 (res);
    vector_scale (res, force);
    return res;
}

void act_force (Body c, Vector f, double sec) {
    Vector at, v0;
    at = vector_zeros (f->size);

    /* Impoem aceleracao */
    vector_copy (at, f);
    vector_scale (at, 1.0/c->mass);
    vector_copy (c->lin_acel, at);

    /* Calcula nova velocidade */
    v0 = vector_zeros (f->size);
    vector_copy (v0, c->lin_speed);
    vector_copy (at, c->lin_acel);
    vector_scale (at, sec);
    vector_add(c->lin_speed, at);

    /* calcula nova posicao */
    vector_scale (v0, sec);
    vector_add(c->lin_position, v0);
    vector_scale (at, sec/2.0);
    vector_add(c->lin_position, at);
}

void body_delete (Body a) {
    if (a != NULL) {
        vector_delete (a->lin_position);
        vector_delete (a->lin_speed);
        vector_delete (a->lin_acel);
        free (a);
    }    
}

Body body_new () {
    Body new;
    new = malloc (sizeof (struct body));
    return new;
}


