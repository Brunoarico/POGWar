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
static int n = 0, N = 0;

static Object obj_add () {
    Object a;
    a = malloc (sizeof (struct object));
    a->shape = NULL;
    a->body = NULL;
    a->shot = NULL;
    a->ship = NULL;
    a->img = NULL;
    a->dust = NULL;
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

void obj_impact (int a, int b) {
    printf ("%d, %d\n", a, b); 
}

Ship Ship_new (int life, double mass, double x, double y, double vx, double vy, double angspd, double begang, char type) {
    Ship nave;
    Object tmp;
    nave = malloc (sizeof (Ship));
    nave->id = obj_new ();
    nave->life = life;
    tmp = obj_get (nave->id);
    tmp->body = body2d_new (mass, x, y, vx, vy);
    tmp->shape = shape_new ();
    nave->fuel = 100;
    if (type == 'b'){
	shape_add_point (tmp->shape, vector2D_new (-100, -70));
	shape_add_point (tmp->shape, vector2D_new (-100, -55));
	shape_add_point (tmp->shape, vector2D_new (-28, 10));
	shape_add_point (tmp->shape, vector2D_new (-28, 45));
	shape_add_point (tmp->shape, vector2D_new (0, 100));
	shape_add_point (tmp->shape, vector2D_new (28, 45));
	shape_add_point (tmp->shape, vector2D_new (28, 10));
	shape_add_point (tmp->shape, vector2D_new (100, -55));
	shape_add_point (tmp->shape, vector2D_new (100, -70));
	shape_add_point (tmp->shape, vector2D_new (0, -100));
	tmp->img = image_create ("img/F6.png");
    }
    else if(type == 'c'){

	shape_add_point (tmp->shape, vector2D_new (-55, -80));
	shape_add_point (tmp->shape, vector2D_new (-55, -40));
	shape_add_point (tmp->shape, vector2D_new (-28, -10));
	shape_add_point (tmp->shape, vector2D_new (-28, 53));
	shape_add_point (tmp->shape, vector2D_new (0, 98));
	shape_add_point (tmp->shape, vector2D_new (28, 53));
	shape_add_point (tmp->shape, vector2D_new (28, -10));
	shape_add_point (tmp->shape, vector2D_new (55, -40));
	shape_add_point (tmp->shape, vector2D_new (55, -80));
	tmp->img = image_create ("img/F5.png");
    }
    image_zoom (tmp->img, 100);
    body_ang_spe2d (tmp->body, angspd);
    body_pos2d_degree (tmp->body, begang);
    return nave;
}

void delete_ship (unsigned int id) {
    free (AllObjects[id]->ship);
    obj_delete (id);
}

void bullet (Ship nave) {
    double ang;
    Object tmp;
    BasicBody obj; 
    Shot fire;
    fire = malloc (sizeof (Shot));
    fire->disapear_time = 100;
    fire->damage = 10;
    fire->id_origem = nave->id;
    tmp = obj_get (obj_new ());
    tmp->shape = shape2d_circle (25, 30);;
    tmp->img = image_create("img/bomb.png");
    image_zoom (tmp->img, 30);
    ang = M_PI*body_ang_position_degrees(obj_get (nave->id)->body)/180;
    obj = &obj_get (nave->id)->body->bbody;
    tmp->body = body2d_new (500, obj->position->data[0]-135*sin(ang), obj->position->data[1]+135*cos(ang), obj->speed->data[0], obj->speed->data[1]);

}

void object_lifetime (double last_time) {
    int i;
    for (i = 0; i < obj_numberof (); i++) {
        if (AllObjects[i] != NULL &&
            AllObjects[i]->dust != NULL) {
            if(AllObjects[i]->dust->disappear_time>=last_time)
                obj_delete (i);
        }
    }
}
