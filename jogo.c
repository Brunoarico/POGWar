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
#define FPS 120


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
    double last, atual, delta;
    float ratio;
    int width, height;
    GLFWwindow* window;
    double stime, interval = 0.0001;
    Object tmp;

    /* adicionar objetos */
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, 500, 0, 0, 1000);
    tmp->shape = shape2d_circle (100, 3);

    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, -500, 0, 0, 1000);
    tmp->shape = shape2d_circle (100, 3);

    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.49833235e+16, 0, 0, 0, 0);
    tmp->shape = shape2d_circle (100, 4);
/*
    tmp = obj_get(obj_new ());
    tmp->body = body2d_new (1.498334e+12, 300, 0, 0, -400);
    tmp->shape = shape2d_circle ( 20, 10);

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

    last = glfwGetTime();


    while (!glfwWindowShouldClose(window)) {
        atual = glfwGetTime();
        delta = atual-last;
        /* printf("%lf \n",delta); */

        if (delta > 1.0/FPS) {
            
            stime = delta;
            while (stime > 0) {
                if (stime < interval)
                    moviments_update (stime);
                else 
                    moviments_update (interval);
                stime -= interval;
            }
            BSP ();

            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float) height;
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            glScalef(.001f, .001f, 1.f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            /*glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);*/

            draw_objects ();

            glfwSwapBuffers(window);
            glfwPollEvents();
            last = atual;
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    
    obj_delete_all ();

    return 0;
}


