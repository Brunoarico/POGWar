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

/* fontes, vamos declarar como globais */
Font basic, font2;

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void add_objects () {
    Object tmp;
    Image fire;
    fire = image_create ("img/fire.png");
    image_zoom (fire, 13); 

    /* deixar as naves como primeiros objetos */
    /* adicionar objetos */
    tmp = obj_get(obj_new (SHIP));
    /*tmp->body = body2d_new (INI_MASS, 500, 0, 0, 100);*/
    tmp->body = body2d_new (INI_MASS, 500, 0, 0, 10000, INI_INERCIA);
    tmp->shape = shape_new ();
    shape_add_point (tmp->shape, vector2D_new (-50, -35));
    shape_add_point (tmp->shape, vector2D_new (-50, -27.5));
    shape_add_point (tmp->shape, vector2D_new (-14, 5));
    shape_add_point (tmp->shape, vector2D_new (-14, 22.5));
    shape_add_point (tmp->shape, vector2D_new (0, 50));
    shape_add_point (tmp->shape, vector2D_new (14, 22.5));
    shape_add_point (tmp->shape, vector2D_new (14, 5));
    shape_add_point (tmp->shape, vector2D_new (50, -27.5));
    shape_add_point (tmp->shape, vector2D_new (50, -35));
    shape_add_point (tmp->shape, vector2D_new (0, -50));
    tmp->img = image_create ("img/F6.png");
    image_zoom (tmp->img, 50); 
    tmp->info.ship->shot_gum1 = fire;
    body_ang_spe2d (tmp->body, 0.2);
    control_set_ship1(tmp->info.ship);


    tmp = obj_get(obj_new (SHIP));
    tmp->body = body2d_new (0, -500, 0, 0, -100, INI_INERCIA);
    tmp->shape = shape_new ();
    shape_add_point (tmp->shape, vector2D_new (-27.5, -40));
    shape_add_point (tmp->shape, vector2D_new (-27.5, -20));
    shape_add_point (tmp->shape, vector2D_new (-14, -5));
    shape_add_point (tmp->shape, vector2D_new (-14, 26.5));
    shape_add_point (tmp->shape, vector2D_new (0, 49));
    shape_add_point (tmp->shape, vector2D_new (14, 26.5));
    shape_add_point (tmp->shape, vector2D_new (14, -5));
    shape_add_point (tmp->shape, vector2D_new (27.5, -20));
    shape_add_point (tmp->shape, vector2D_new (27.5, -40));
    tmp->img = image_create ("img/F5.png");
    image_zoom (tmp->img, 50);
    tmp->info.ship->shot_gum1 = fire;
    body_ang_spe2d (tmp->body, 0.2);
    body_pos2d_degree (tmp->body, 180);
    control_set_ship2(tmp->info.ship);

    tmp = obj_get(obj_new (PLANET));
    tmp->body = body2d_new (PLANET_MASS, 0, 0, 0, 0, 100);
    tmp->shape = shape2d_circle (100, 10);
    tmp->img = image_create ("img/DeathStar.png");
    image_zoom (tmp->img, 100);

    /*int i;
    for (i = 0 ; i < 10; i++) {
        tmp = obj_get(obj_new ());
        tmp->body = body2d_new (0, 10*i, 0, 100, 0);
        tmp->shape = shape2d_circle (1, 2);
    }*/

}

void show_info (float width, float height) {
    float ratio = width / (float) height;
    if (obj_get (0) != NULL) {
        printText2D (
            basic, 
            "Player 1", 
            -OPENGL_SCALE*ratio+30, -OPENGL_SCALE+270,
            0.8);
        draw_bar (
            -OPENGL_SCALE*ratio+30, -OPENGL_SCALE+150,
            1000, 50,
            0, 0, 1,
            obj_get(0)->info.ship->life/INI_LIFE);
        draw_bar (
            -OPENGL_SCALE*ratio+30, -OPENGL_SCALE+70,
            1000, 50,
            .8, .5, .2,
            (obj_get (0)->body->bbody.mass-INI_MASS*MIN_MASS)
            /(INI_MASS-INI_MASS*MIN_MASS));
    } else {
        printText2D (
            basic, 
            "Player 1 is a loser.", 
            -OPENGL_SCALE*ratio+30, -OPENGL_SCALE+270,
            0.8);
    }

    if (obj_get (1) != NULL) {
        printText2D (
            basic, 
            "Player 2", 
            30, -OPENGL_SCALE+270,
            0.8);
        draw_bar (
            30, -OPENGL_SCALE+150,
            1000, 50,
            0, 0, 1,
            obj_get(1)->info.ship->life/INI_LIFE);
        draw_bar (
            30, -OPENGL_SCALE+70,
            1000, 50,
            .8, .5, .2,
            (obj_get (1)->body->bbody.mass-INI_MASS*MIN_MASS)
            /(INI_MASS-INI_MASS*MIN_MASS));
    } else {
        printText2D (
            basic, 
            "Player 2 is a loser.", 
            30, -OPENGL_SCALE+270,
            0.8);
    }
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
            moviments_update ();


            if (stime < MIN_INTERVAL) 
                moviments_act(stime);
            else 
                moviments_act (MIN_INTERVAL);
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
            
            if (!control_stade ()) {
                BSP (&obj_impact);   /* Verifica colisoes */
                obj_validate ();
            }


            draw_back ();       /* Desenha fundo */
            draw_objects ();    /* Desenha objetos */
            printText2D (font2, "POGWar", -OPENGL_SCALE*ratio+20, OPENGL_SCALE-20, 1);
            sprintf(buffer, "%3.2f fps", 1.0/deltafps);
            printText2D (basic, buffer, -OPENGL_SCALE*ratio+20, OPENGL_SCALE-150, 0.5);
            show_info (width, height);

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


