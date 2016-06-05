/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Segunda fase: geracao de imagens.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "libs/graphs/shape.h"
#include "libs/physics/physics.h"
#include "libs/simulation/moviments.h"
#include "libs/graphs/draw.h"
#include "libs/graphs/bitmap.h"
#include "libs/simulation/bsp.h"
#include "libs/engine/object.h"
#include "libs/engine/controls.h"
#include "config.h"

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void add_objects () {
    Object tmp;

    /* adicionar objetos */
    tmp = obj_get(obj_new (SHIP));
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
    control_set_ship1(tmp->info.ship);


    tmp = obj_get(obj_new (SHIP));
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
    control_set_ship2(tmp->info.ship);

    tmp = obj_get(obj_new (PLANET));
    tmp->body = body2d_new (1.49833235e+16, 0, 0, 0, 0);
    tmp->shape = shape2d_circle (200, 10);
    tmp->img = image_create ("img/DeathStar.png");
    image_zoom (tmp->img, 200);

    /*int i;
    for (i = 0 ; i < 10; i++) {
        tmp = obj_get(obj_new ());
        tmp->body = body2d_new (0, 10*i, 0, 100, 0);
        tmp->shape = shape2d_circle (1, 2);
    }*/

}

GLFWwindow * create_window () {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "POGWar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, control_callback);
    return window;
}

int main (int argc, char *argv[]) {
    double lastgravidade, lastfps, atual, deltagravidade, deltafps;
    float ratio;
    int width, height;
    GLFWwindow* window;
    double stime;
    char buffer [50];
    Font basic, font2;

    add_objects ();
    window = create_window ();


    basic = initText2D ("fonts/basic.txt");
    font2 = initText2D ("fonts/title.txt");

    lastfps = glfwGetTime();
    lastgravidade = lastfps;


    while (!glfwWindowShouldClose(window)) {
        atual = glfwGetTime();
        deltagravidade = atual - lastgravidade;
        deltafps = atual - lastfps;
        stime = deltagravidade;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        while (stime > 0 && !control_stade ()) {
            if (stime < MIN_INTERVAL) 
                moviments_update (stime);
            else 
                moviments_update (MIN_INTERVAL);
            /* verifica margem */
            check_screen_edges (OPENGL_SCALE*ratio, OPENGL_SCALE);
            stime -= MIN_INTERVAL;
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
            obj_validate ();
            object_lifetime (atual);


            draw_back ();       /* Desenha fundo */
            draw_objects ();    /* Desenha objetos */
            printText2D (font2, "POGWar", -OPENGL_SCALE*ratio+20, OPENGL_SCALE-20, 1);
            sprintf(buffer, "%3.2f fps", 1.0/deltafps);
            printText2D (basic, buffer, -OPENGL_SCALE*ratio+20, OPENGL_SCALE-150, 1);

            glfwSwapBuffers(window);
            glfwPollEvents();
            lastfps = atual;

            if (control_restart ()) {
                obj_delete_all ();
                add_objects ();
            }
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    
    obj_delete_all ();
    deleteText2D (basic);
    deleteText2D (font2);

    return 0;
}


