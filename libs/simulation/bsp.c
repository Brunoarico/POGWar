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
#define PLANE_THICKNESS_EPSILON 0.0
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
    int isleaf;
};
typedef struct node *BSPNode;


BSPNode bsp_new (Vertices vertices) {
    BSPNode n = malloc (sizeof (struct node));
    n->vertices = vertices;
    n->right = NULL;
    n->left = NULL;
    return n;
}

status ClassifyPointToPlane(double x, double y, Line linea) {
    double dist = linea.a * x + linea.b * y + linea.c;
    if (dist > PLANE_THICKNESS_EPSILON) return POSITIVE;
    if (dist < PLANE_THICKNESS_EPSILON) return NEGATIVE;
    return INTERSECTION;
}

status ClassifyVerticeToline (Vertice v, Line linea) {
    int numInFront = 0, numBehind = 0;
    status s1 = ClassifyPointToPlane(v->a->data[0], v->a->data[1], linea);
    status s2 = ClassifyPointToPlane(v->b->data[0], v->b->data[1], linea);
    if (s1 == POSITIVE) numInFront++;
    if (s1 == NEGATIVE) numInFront--;
    if (s2 == POSITIVE) numInFront++;
    if (s2 == NEGATIVE) numInFront--;

    if (numBehind != 0 && numInFront != 0) return INTERSECTION;
    if (numInFront != 0) return POSITIVE;
    if (numBehind != 0) return NEGATIVE;
    return COLINEAR;
}

Line GetLineFromVertice (Vertice v) {
    Line line;
    line.a = v->a->data[0] - v->b->data[0];
    line.b = v->a->data[1] - v->b->data[1];
    line.c = - line.a - line.b;
    return line;
}

Vector LineInter (Line la, Line lb) {
    Vector nv;
    nv = vector_zeros (2);
    nv->data[0] = la.b * lb.c - lb.b * la.c;
    nv->data[1] = la.a * lb.c - lb.a * la.c;
    return nv;
}

Line PickSplittingPlane (Vertices vertices) {
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
    }/*
    glLineWidth(1); 
    glBegin(GL_LINES);
    glVertex2f(-1000,(1000*bestline.a-bestline.c)/bestline.b);
    glVertex2f(1000,(-1000*bestline.a-bestline.c)/bestline.b);
    glEnd();*/


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
    v = vertice_new (k, vertice->b,vertice->o);
    return v;
}

/* Controi a arvore bst com um vetor de vertices */
BSPNode BuildBSPTree(Vertices vertices, int depth) {
    BSPNode newnode;
    Vertice tmp, tmpa;
    Vertices frontPart, backPart;
    int i;
    if (vertices_size (vertices) == 0) return NULL;

    /* É uma folha */
    if (depth >= MAX_DEPTH || vertices_size (vertices) <= MIN_LEAF_SIZE)
        return bsp_new (vertices);

    newnode = malloc (sizeof (struct node));
    newnode->vertices = NULL;

    newnode->line = PickSplittingPlane(vertices);
    frontPart = vertices_new ();
    backPart = vertices_new ();

    for (i = 0; i < vertices_size (vertices); i++) {
        /* Keep standing count of the various poly-line relationships */
        tmp = vertices_get (vertices, i);
        switch (ClassifyVerticeToline (tmp, newnode->line)) {
            case COLINEAR:
            /* Coplanar vertices treated as being in front of line */
            case POSITIVE:
                vertices_insert (frontPart, tmp);
                break;
            case NEGATIVE:
                vertices_insert (backPart, tmp);
                break;
            case INTERSECTION:
                tmpa = SplitVerticeF (tmp, newnode->line);
                vertices_insert (frontPart, tmpa);
                tmpa = SplitVerticeB (tmp, newnode->line);
                vertices_insert (backPart, tmpa);
                break;
        }
    }

    newnode->right = BuildBSPTree(frontPart, depth + 1);
    newnode->left = BuildBSPTree(backPart, depth + 1);
    return newnode;
}

int Collision (Vertice vertice, BSPNode node) {
    /* Não é folha */
    Vertice tmpb, tmpa;
    while (node->vertices == NULL) {
        switch (ClassifyVerticeToline (vertice, node->line)) {
            case COLINEAR:
            /* Coplanar vertices treated as being in front of line */
            case POSITIVE:
                node = node->right;
                break;
            case NEGATIVE:
                node = node->left;
                break;
            case INTERSECTION:
                tmpa = SplitVerticeF (vertice, node->line);
                tmpb = SplitVerticeB (vertice, node->line);
                if (Collision (tmpa, node->right)) return 1;
                if (Collision (tmpb, node->left)) return 1;
                break;
            return 0;
        }
    }
    /* Now at a leaf, inside/outside status determined by solid flag */
    return 1;
}

void BSP () {
    Vertices vertices;
    Vertice vertmp;
    Object tmp;
    BSPNode tree;
    Shape stmp;
    int i, j;
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
            vertmp = vertice_new (stmp->points[j], stmp->points[j%stmp->size], tmp);
            vertices_insert (vertices, vertmp);
        }
    }
    tree = BuildBSPTree(vertices, 0);

    for (i = 0; i < vertices_size (vertices); i++) {
        vertmp = vertices_get (vertices, i);
        printf ("%d \n", Collision (vertmp, tree));
    }

}
