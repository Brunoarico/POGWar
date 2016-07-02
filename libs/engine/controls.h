/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface de gerenciamento de controles
 *
 ******************************************************************************/
 
#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "../engine/object.h"
#include "../../config.h"

void control_callback (GLFWwindow* window, int key, int scancode, int action, int mods);
void control_set_ship1 (Ship s);
void control_set_ship2 (Ship s);
int control_stade ();
int control_restart ();

#endif
