/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Primeira fase: simulacao das orbitas.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "libs/graphs/shape.h"
#include "libs/physics/physics.h"
#include "libs/simulation/moviments.h"
#include "libs/graphs/draw.h"
#include "libs/simulation/bsp.h"
#include "libs/engine/object.h"
#include "config.h"

Body body_add2d (double mass, double x, double y, double vx, double vy, double r, double n) ;
void print_bodies (Body *corpos, int N);

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main (int argc, char *argv[]) {
    double lastgravidade, lastfps, atual, deltagravidade, deltafps;
    float ratio;
    int width, height;
    GLFWwindow* window;
    double stime, interval = 0.0001;
    Object tmp;

    /* adicionar objetos */
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, 500, 0, 0, 1000);
    tmp->shape = shape_new ();
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
    image_zoom (tmp->img, 100); 
    body_ang_spe2d (tmp->body, 2);


    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, -500, 0, 0, -1000);
    tmp->shape = shape_new ();
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
    image_zoom (tmp->img, 100);
    body_ang_spe2d (tmp->body, 2);
    body_pos2d_degree (tmp->body, 180);

    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.49833235e+16, 0, 0, 0, 0);
    tmp->shape = shape2d_circle (200, 30);
    tmp->img = image_create ("img/DeathStar.png");
    image_zoom (tmp->img, 200);
    /*
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.098334e+12, 900, 0, 100, -950);
    tmp->shape = shape2d_circle ( 40, 10);
    tmp->img = image_create ("img/mars.png");
    image_zoom (tmp->img, 40);
    */
    /*
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.49833235e+15, 1000, 200, 0, 0);
    tmp->shape = shape2d_circle ( 60, 10);
    tmp->img = image_create ("img/earth.png");
    image_zoom (tmp->img, 60);
    */
    /*
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, -300, 0, 0, 400);
    tmp->shape = shape2d_circle (20, 10);
    */

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "POGWar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    /* glfwSwapInterval(1); */

    glfwSetKeyCallback(window, key_callback);

    lastfps = glfwGetTime();
    lastgravidade = lastfps;


    while (!glfwWindowShouldClose(window)) {
        atual = glfwGetTime();
        deltagravidade = atual - lastgravidade;
        deltafps = atual - lastfps;
        stime = deltagravidade;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        while (stime > 0) {
            if (stime < interval) 
                moviments_update (stime);
            else 
                moviments_update (interval);
            /* verifica margem */
            check_screen_edges (OPENGL_SCALE*ratio, OPENGL_SCALE);
            stime -= interval;
        }
        lastgravidade = atual;

        if (deltafps >= 1.0/FPS) {

            glViewport(0, 0, width, height);
            
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            glScalef(1.0f/OPENGL_SCALE, 1.0f/OPENGL_SCALE, 1.f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            
            BSP (&obj_impact);   /* Verifica colisoes */
            draw_back ();       /* Desenha fundo */
            draw_objects ();    /* Desenha objetos */

            glfwSwapBuffers(window);
            glfwPollEvents();
            lastfps = atual;
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    
    obj_delete_all ();

    return 0;
}


