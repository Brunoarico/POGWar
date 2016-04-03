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
    vector_add(res, tmp);
    vector_scale(res, total_mass_i);
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

