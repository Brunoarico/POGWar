/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
#include "bsp.h"
#define MAX_DEPTH 10
#define MIN_LEAF_SIZE 1
#define PLANE_THICKNESS_EPSILON 0.01
#define FLT_MAX 10

typedef enum {
    POSITIVE,
    NEGATIVE,
    COLINEAR,
    INTERSECTION
} status;

struct line {
    double a, b, c; /* ax+by+c = 0 */
};
typedef struct line Line;

struct node {
    Vertices vertices;
    struct node *right, *left;
    Line line;
};
typedef struct node *BSPNode;

BSPNode bsp_new (Vertices vertices) {
    BSPNode n = malloc (sizeof (struct node));
    n->vertices = vertices;
    n->right = NULL;
    n->left = NULL;
    return n;
}

status ClassifyPointToLine (double x, double y, Line linea) {
    double dist = linea.a * x + linea.b * y + linea.c;
    if (dist > PLANE_THICKNESS_EPSILON) return POSITIVE;
    if (dist < -PLANE_THICKNESS_EPSILON) return NEGATIVE;
    return INTERSECTION;
}

status ClassifyVerticeToline (Vertice v, Line linea) {
    status s1 = ClassifyPointToLine (v->a->data[0], v->a->data[1], linea);
    status s2 = ClassifyPointToLine (v->b->data[0], v->b->data[1], linea);

    if (s1 == INTERSECTION && s2 == INTERSECTION) return COLINEAR;
    if (s1 == POSITIVE && s2 == NEGATIVE) return INTERSECTION;
    if (s1 == NEGATIVE && s2 == POSITIVE) return INTERSECTION;

    if (s1  != INTERSECTION) return s1;
    return s2;
}

Line GetLineFromVertice (Vertice v) {
    Line line;
    line.a =  v->a->data[1] - v->b->data[1];
    line.b = v->b->data[0] - v->a->data[0];
    line.c =  v->a->data[0] * v->b->data[1] - v->a->data[1] * v->b->data[0];
    return line;
}

Vector LineInter (Line la, Line lb) {
    /* la.a = A1, la.b = B1, lb.a = A2, lb.b = B2 */
    Vector nv;
    double det;
    nv = vector_zeros (2);
    det = la.a * lb.b - lb.a * la.b;
    nv->data[0] = (la.b * lb.c - lb.b * la.c)/det;
    nv->data[1] = (lb.a * la.c - la.a * lb.c)/det;
    return nv;
}

void BSPTree_delete (BSPNode node) {
    if (node == NULL) return;
    BSPTree_delete (node->right);
    BSPTree_delete (node->left);
    vertices_delete (node->vertices);
    
    free (node);
}

Line PickSplittingLine (Vertices vertices) {
    int i, j;
    float score;
    int numInFront;
    int numBehind;
    int numStraddling;
    float bestScore;
    Line line;
    Vertice vert;
    /* Blend factor for optimizing for balance or splits (should be tweaked) */
    const float K = 0.8f;
    /* Variables for tracking best splitting line seen so far */
    Line bestline;
    bestScore = FLT_MAX;
    /* Try the line of each polygon as a dividing line */
    for (i = 0; i < vertices_size (vertices); i++) {
        numInFront = 0;
        numBehind = 0;
        numStraddling = 0;
        vert = vertices_get (vertices, i);
        line = GetLineFromVertice (vert);

        /* printf("(%lf,%lf) (%lf,%lf)\n", vert->a->data[0], vert->a->data[1], vert->b->data[0], vert->b->data[1]); */
        /* printf("%lf * x + %lf * y + %lf = 0\n", line.a, line.b, line.c); */
        
        /* Test against all other vertices */
        for (j = 0; j < vertices_size (vertices); j++) {
            /* Ignore testing against self */
            if (i == j) continue;
            /* Keep standing count of the various poly-line relationships */ 
            switch (ClassifyVerticeToline (vertices_get (vertices, j), line)) {
                case COLINEAR:
                /* Coplanar vertices treated as being in front of line */
                case POSITIVE:
                    numInFront++;
                    break;
                case NEGATIVE:
                    numBehind++;
                    break;
                case INTERSECTION:
                    numStraddling++;
                    break;
            }
        }
        /* Compute score as a weighted combination (based on K, with K in range */
        /* 0..1) between balance and splits (lower score is better) */
        score = K * numStraddling + (1.0f - K) * abs(numInFront - numBehind); 
        if (score < bestScore) {
            bestScore = score;
            bestline = line;
        }
        /* printf("%lf\n", score); */
    }
/*
    printf("%lf * x + %lf * y + %lf = 0\n", bestline.a, bestline.b, bestline.c);
    glLineWidth(1); 
    glBegin(GL_LINES);
    glVertex2f(-1000,(1000*bestline.a-bestline.c)/bestline.b);
    glVertex2f(1000,(-1000*bestline.a-bestline.c)/bestline.b);
    glEnd();
*/

    return bestline;
}

Vertice SplitVerticeF (Vertice vertice, Line line) {
    Line n;
    Vector k; 
    Vertice v;
    n = GetLineFromVertice (vertice);
    k = LineInter (n, line);
    v = vertice_new (vertice->a, k,vertice->o);
    return v;
}

Vertice SplitVerticeB (Vertice vertice, Line line) {
    Line n;
    Vector k; 
    Vertice v;
    n = GetLineFromVertice (vertice);
    k = LineInter (n, line);
    v = vertice_new (k, vertice->b, vertice->o);
    return v;
}

/* Constroi a arvore bst com um vetor de vertices */
BSPNode BuildBSPTree(Vertices vertices, int depth) {
    BSPNode newnode;
    Vertice tmp, tmpa;
    Vertices frontPart, backPart;
    Line line;
    int i, size;

    size = vertices_size (vertices);
    /*printf("%d\n", size);*/

    if (size == 0) return NULL;

    newnode = malloc (sizeof (struct node));
    newnode->vertices = NULL;
    newnode->right = NULL;
    newnode->left = NULL;

    /* É uma folha */
    if (depth >= MAX_DEPTH || size <= MIN_LEAF_SIZE) {
       newnode->vertices = vertices;
       return newnode;
    }

    line = PickSplittingLine (vertices);
    frontPart = vertices_new ();
    backPart = vertices_new ();

    for (i = 0; i < size; i++) {
        /* Keep standing count of the various poly-line relationships */
        tmp = vertices_get (vertices, i);
        switch (ClassifyVerticeToline (tmp, line)) {
            case COLINEAR:
            /* Coplanar vertices treated as being in front of line */
            case POSITIVE:
                vertices_insert (frontPart, tmp);
                break;
            case NEGATIVE:
                vertices_insert (backPart, tmp);
                break;
            case INTERSECTION: 
                /*printf("-----\n" );
                printf("(%lf,%lf) (%lf,%lf)\n", tmp->a->data[0], tmp->a->data[1], tmp->b->data[0], tmp->b->data[1]);*/

                tmpa = SplitVerticeF (tmp, line);
                /*printf("(%lf,%lf) (%lf,%lf)", tmpa->a->data[0], tmpa->a->data[1], tmpa->b->data[0], tmpa->b->data[1]);*/
                vertices_insert (frontPart, tmpa);

                tmpa = SplitVerticeB (tmp, line);
                /*printf("(%lf,%lf) (%lf,%lf)\n", tmpa->a->data[0], tmpa->a->data[1], tmpa->b->data[0], tmpa->b->data[1]);*/
                vertices_insert (backPart, tmpa);

                break;
        }
    }
    /*
    printf("-> %d - frontPart %d, backPart %d\n", depth, vertices_size(frontPart), vertices_size(backPart));
*/
    if (depth != 0) {
        free (vertices->vertices);
        free (vertices);
    }
    if (vertices_size(frontPart) == 0) {
        vertices_delete (frontPart);
        newnode->vertices = backPart;
        return newnode;
    }
    if (vertices_size(backPart) == 0) {
        vertices_delete (backPart);
        newnode->vertices = frontPart;
        return newnode;
    }

    newnode->line = line;
    newnode->right = BuildBSPTree (frontPart, depth + 1);
    newnode->left = BuildBSPTree (backPart, depth + 1);
    return newnode;
}

Object Collision (Vertice vertice, BSPNode node) {
    /* Não é folha */
    Vertice tmpb;
    Object obj;
    int i;

    if (vertice == NULL || node == NULL) return NULL;
    if (node->vertices != NULL) {
        for (i = 0; i < vertices_size (node->vertices); i++) {
            tmpb = vertices_get(node->vertices, i);
            if (tmpb->o == vertice->o) continue;
            if (ClassifyVerticeToline (vertice, GetLineFromVertice (tmpb))
                == INTERSECTION) return tmpb->o;
        }
    }

    /*printf("%e , %e, %e\n", node->line.a, node->line.b, node->line.c);*/
    switch (ClassifyVerticeToline (vertice, node->line)) {
        case COLINEAR:
        /* Coplanar vertices treated as being in front of line */
        case POSITIVE:
            return  Collision (vertice, node->right);
            break;
        case NEGATIVE:
            return   Collision (vertice, node->left);
            break;
        case INTERSECTION:
            /* printf("%e\n", atual->line.a*vertice->a->data[0] +atual->line.b*vertice->a->data[1]+ atual->line.c); */

              /*  printf("(%lf,%lf) (%lf,%lf)\n", vertice->a->data[0], vertice->a->data[1], vertice->b->data[0], vertice->b->data[1]);*/
            
            tmpb = SplitVerticeF (vertice, node->line);
            obj = Collision (tmpb, node->right);
            if (obj != NULL) {
                free (vertice);
                return obj;
            }
            tmpb = SplitVerticeB (vertice, node->line);
            obj = Collision (tmpb, node->left);
            if (obj != NULL) {
                free (vertice);
                return obj;
            }
            break;
    }
    return NULL;
}

void BSP () {
    Vertices vertices;
    Vertice vertmp;
    Object tmp;
    BSPNode tree;
    Shape stmp;
    int i, j, k;
    vertices = vertices_new ();
    for (i = 0; i < obj_numberof (); i++) {
        tmp = obj_get (i);
        if (tmp == NULL) continue;
        stmp = tmp->shape;
        if (tmp->shape == NULL) continue;
        stmp = shape_copy (tmp->shape);
        shape_rotate (stmp, 0.0);
        shape_move (stmp, body_posg (tmp->body));
        for (j = 0; j < stmp->size; j++) {
            k = (j + 1) % stmp->size;
            vertmp = vertice_new (stmp->points[j], stmp->points[k], tmp);
            vertices_insert (vertices, vertmp); 
        }
        free (stmp->points); 
        free (stmp); 
    }
    
    tree = BuildBSPTree(vertices, 0);

    for (i = 0; i < vertices_size(vertices) ; i++) {
        vertmp = vertices_get (vertices, i);
        tmp = Collision (vertmp, tree);
        if (tmp != NULL) {
            printf("%d, %d\n", tmp->id, vertmp->o->id); 
            obj_delete (vertmp->o->id); 
        }
    }
    free (vertices->vertices);
    free (vertices);
    BSPTree_delete (tree);
}
