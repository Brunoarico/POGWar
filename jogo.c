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
#include "libs/physics/physics.h"
#include "libs/simulation/moviments.h"
#include "libs/graphs/shape.h"
#define FPS 120.0

struct object {
    struct body body;
    Shape inicial;
    Shape last;
};
typedef struct object *Object;

Body body_add2d (double mass, double x, double y, double vx, double vy) ;
void print_bodies (Body *corpos, int N);
void drawCircle(float radius, double x, double y, int n) ;

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main (int argc, char *argv[]) {
    Body corpos[5];
    int N = 3, i;
    double last, atual, delta;
    float ratio;
    int width, height;
    GLFWwindow* window;
    double stime, interval = 0.0001;

    corpos[0] = body_add2d (1.498334e+12, 100, 0, 0, 1000);
    corpos[1] = body_add2d (1.498334e+12, -100, 0, 0, -1000);
    corpos[2] = body_add2d (1.49833235e+16, 0, 0, 0, 0);
    corpos[3] = body_add2d (1.498334e+12, 300, 0, 0, -400);
    corpos[4] = body_add2d (1.498334e+12, -300, 0, 0, 400);

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
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
            /* printf("%d \n",glfwGetWindowAttrib(window, GLFW_VISIBLE)); */
            
            stime = delta;
            while (stime > 0) {
                if (stime < interval)
                    moviments_update (corpos, N, stime);
                else 
                    moviments_update (corpos, N, interval);

                stime -= interval;
            }

            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float) height;
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            /*glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);*/

            print_bodies (corpos, N);

            glfwSwapBuffers(window);
            glfwPollEvents();
            last = atual;
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    for (i = 0; i < N; i++) body_delete (corpos[i]);

    return 0;
}

Body body_add2d (double mass, double x, double y, double vx, double vy) {
    Vector position, speed, acel;
    Body b;
    b = body_new();
    speed = vector_zeros (2);
    position = vector_zeros (2);
    acel = vector_zeros (2);
    position->data[0] = x;
    position->data[1] = y;
    speed->data[0] = vx;
    speed->data[1] = vy;
    body_mass (b, mass);
    body_pos (b, position);
    body_spe (b, speed);
    body_acel (b, acel);
    return b;
}

void print_bodies (Body *corpos, int N) {
    int i;
    for (i = 0; i < N; i++) {
        if (corpos[i] == NULL) continue;
        /*printf("m: %e \t", corpos[i]->bbody.mass);
        printf("x: %e \t", corpos[i]->bbody.position->data[0]);
        printf("y: %e \t", corpos[i]->bbody.position->data[1]);
        printf("vx: %e \t", corpos[i]->bbody.speed->data[0]);
        printf("vy: %e \n", corpos[i]->bbody.speed->data[1]); */
        /*printf("%e ", corpos[i]->bbody.position->data[0]);
        printf("%e\n", corpos[i]->bbody.position->data[1]);*/
        drawCircle(0.01, corpos[i]->bbody.position->data[0], corpos[i]->bbody.position->data[1], 20);
    }
}

void drawCircle(float radius, double x, double y, int n) {
    int i;
    x /= 600;
    y /= 600;
    glPushMatrix();
    glTranslatef (x, y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < n; i++) {
        float degInRad = i * 3.14159 * 2.0/n;
        glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
    }
    glEnd();
    glPopMatrix();
}
