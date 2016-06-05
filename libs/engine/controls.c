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

#include "controls.h"

static Ship ship1, ship2;
static int pause = 0, restart = 0, gameover = 0;

void control_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == SHIP1_JET1 && action == GLFW_PRESS)
        ship1->jet1 = 1;
    else if (key == SHIP1_JET1 && action == GLFW_RELEASE)
        ship1->jet1 = 0;
    else if (key == SHIP1_JET2 && action == GLFW_PRESS)
        ship1->jet2 = 1;
    else if (key == SHIP1_JET2 && action == GLFW_RELEASE)
        ship1->jet2 = 0;
    else if (key == SHIP1_JET3 && action == GLFW_PRESS)
        ship1->jet3 = 1;
    else if (key == SHIP1_JET3 && action == GLFW_RELEASE)
        ship1->jet3 = 0;
    else if (key == SHIP1_GUM1 && action == GLFW_PRESS)
        ship1->gum1 = 1;
    else if (key == SHIP1_GUM1 && action == GLFW_RELEASE)
        ship1->gum1 = 0;

    else if (key == SHIP2_JET1 && action == GLFW_PRESS)
        ship2->jet1 = 1;
    else if (key == SHIP2_JET1 && action == GLFW_RELEASE)
        ship2->jet1 = 0;
    else if (key == SHIP2_JET2 && action == GLFW_PRESS)
        ship2->jet2 = 1;
    else if (key == SHIP2_JET2 && action == GLFW_RELEASE)
        ship2->jet2 = 0;
    else if (key == SHIP2_JET3 && action == GLFW_PRESS)
        ship2->jet3 = 1;
    else if (key == SHIP2_JET3 && action == GLFW_RELEASE)
        ship2->jet3 = 0;
    else if (key == SHIP2_GUM1 && action == GLFW_PRESS)
        ship2->gum1 = 1;
    else if (key == SHIP2_GUM1 && action == GLFW_RELEASE)
        ship2->gum1 = 0;

    else if (key == PAUSE && action == GLFW_PRESS)
        pause = !pause;
    else if (key == RESTART && action == GLFW_PRESS)
        restart = 1;

    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void control_set_ship1 (Ship s) {
    ship1 = s;
}

void control_set_ship2 (Ship s) {
    ship2 = s;
}

int control_stade () {
    if (pause) {
        ship2->jet1 = 0;
        ship2->jet2 = 0;
        ship2->jet3 = 0;
        ship2->gum1 = 0;
        ship1->jet1 = 0;
        ship1->jet2 = 0;
        ship1->jet3 = 0;
        ship1->gum1 = 0;
    }
    return pause;
}

int control_restart () {
    if (restart) {
        restart = 0;
        ship2->jet1 = 0;
        ship2->jet2 = 0;
        ship2->jet3 = 0;
        ship2->gum1 = 0;
        ship1->jet1 = 0;
        ship1->jet2 = 0;
        ship1->jet3 = 0;
        ship1->gum1 = 0;
        pause = 1;
        return 1;
    } 
    return 0;
}

