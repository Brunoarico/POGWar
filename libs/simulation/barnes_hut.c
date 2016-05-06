/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Implementacao do calculo das forcas entre os corpos baseado no algoritmo
 *  barnes-hut (EM CONSTRUCAO)
 *
 ******************************************************************************/

#include "barnes_hut.h"

static Node new_with_body (Body b) {
    Node n;
    int i = 0;
    n = malloc (sizeof (struct node));
    n->b = b;
    n->mass = 0.0;
    n->center_mass = vector_zeros(b->lin_position->size);
    for (i = 0; i < 4; i++) n->nodes[i] = NULL;
    n->area[0] = n->area[1] = DBL_MIN;
    n->area[2] = n->area[3] = DBL_MAX;
    return n;
}

static int get_node (Body b, Node n) {
    int i = 0, j = 0;
    if (b->lin_position->data[0]>(n->area[0]+n->area[2])/2)
        i = 1;
    if (b->lin_position->data[1]>(n->area[1]+n->area[3])/2)
        j = 1;
    if (i && i) return 0;
    if (!i && !j) return 2;
    else return 1 + 2 * j;
}

static void bh_free (Node root) {
    int i;
    if (root == NULL) return;
    for (i = 0; i < 4; ++i) bh_free (root->nodes[i]);
    vector_delete (root->center_mass);
    free (root);
}

static Node bh_insert (Body b, Node root) {
    Vector tmp_vector;
    Body tmp_body;
    double new_mass = 0.0;
    int tmp;
    if (root == NULL) {
        root = new_with_body (b);
    } else if (root->b == NULL) {
        tmp_vector = vector_zeros (b->lin_position->size);
        new_mass = root->mass + b->mass;
        vector_scale (root->center_mass, root->mass);
        vector_scale (tmp_vector, b->mass);
        vector_add (root->center_mass, tmp_vector);
        vector_delete (tmp_vector);
        root->mass = new_mass;
        root->nodes[get_node (b, root)] = new_with_body (b);
    } else {/*
        tmp_body = root->b;
        root->b = NULL;
        tmp = get_node (tmp_body, root); 
        root->nodes[tmp] = new_with_body (tmp_body);
        tmp = get_node (b, root);
        root->nodes[tmp] = new_with_body (b);*/
    }
    printf("%e\n", root->mass);
    return root;
}

static Vector bh_act_force (Body b, Node root) {
    double s, d;
    int i;
    if (root->b != NULL && root->b != b) {
       return gravitational_force (b, root->b);   
    }
    s = root->area[0] - root->area[1];
    d = root->center_mass->data[0];
    printf("%e", s/d);
    return NULL;

}

void bh_moviments_update (Body *bodies, int N, double interval) {
    Node root = NULL;
    int i;
    printf ("%d", N);
    for (i = 0; i < N; i++)
        root = bh_insert (bodies[i], root);
    printf("--------\n");
    bh_free (root);
    //for (i = 0; i < N; i++)
    //    bh_act_force (bodies[i], root);
}

