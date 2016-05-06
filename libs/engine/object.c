/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Manipula objetos da cena
 *
 *  Contem um vetor de objetos que indicam todos os objetos da cena
 *
 ******************************************************************************/

#include "object.h"

/* Vetor de ponteiros para objetos que guardam todos os objetos da cena */
static Object *AllObjects;

/* n numero de objetos, N tamanho de vetor */
static n = 0, N = 0;

static Object obj_add () {
    Object a;
    a = malloc (sizeof (struct object));
    a->shape = NULL;
    a->body = NULL;
    a->shot = NULL;
    a->ship = NULL;
    a->img = NULL;
    return a;
}

unsigned int obj_new () {
    int i;
    /* verifica a existencia de lugares vazios no vetor */
    for (i = 0; i < n; i++) {
        if (AllObjects[i] == NULL) {
            AllObjects[i] = obj_add ();
            return i;
        }
    }
    n += 1;
    if (n > N) {
        if (n == 1) N = 1;
        else N *= 2;
        AllObjects = realloc(AllObjects, N * sizeof (Object));
    }
    AllObjects[n - 1] = obj_add ();
    AllObjects[n - 1]->id = n - 1;
    return n - 1;
}

Object obj_get (int i) {
    return AllObjects[i];
}

void obj_delete (int i) {
    if (AllObjects[i] == NULL) return;
    shape_delete (AllObjects[i]->shape);
    body_delete (AllObjects[i]->body);
    image_delete (AllObjects[i]->img);
    free (AllObjects[i]);
    AllObjects[i] = NULL;
}

unsigned int obj_numberof () {
    return n;
}

void obj_delete_all () {
    int i;
    for (i = 0; i < obj_numberof (); i++)
        obj_delete (i);
    free (AllObjects);
}
