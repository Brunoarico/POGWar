/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 *  Interface que define algumas constantes a serem aplicadas no jogo.
 *
 ******************************************************************************/
#define OPENGL_SCALE 1000.0                 /* Escala de zoom da camera do jogo */
#define SHOW_GL_LINE_LOOP 0                 /* Mostra os vertices dos shapes */
#define DEBUG 0

#define GRAV_CONST 1             /* Constante gravitacional */

#define BACKGROUD_IMAGE "img/galaxy.png"    /* Localizacao da imagem de background */
#define LEFT_PANEL_IMAGE "img/left.png"    /* Localizacao da imagem de background */
#define RIGHT_PANEL_IMAGE "img/right.png"    /* Localizacao da imagem de background */
#define LOGO_IMAGE "img/logo.png"    
#define LOST1_IMAGE "img/over1.png"    
#define LOST2_IMAGE "img/over2.png"    
#define BOTH_LOST_IMAGE "img/both.png"    
#define PAUSE_IMAGE "img/resume.png"    
#define FUEL_BAR_IMAGE "img/load_red.png"    
#define LIFE_BAR_IMAGE "img/load_green.png"    
#define SPEED_BAR_IMAGE "img/load_orange.png"
#define CENTRAL_PLANET_IMAGE "img/earth.png"    

#define FPS 120                             /* Quantidade de frames (atualizacao de 
                                               imagem) por segundo */

/* Intervalo mínimo entre passos do modelo gravitacional */
#define MIN_INTERVAL 0.001                  /* 0.0001 */

#define INI_FUEL 100 /* combustível inicial */
#define INI_LIFE 100 /* vida inicial */
#define SHOT_DEMAGE 10 /* quanto tira de vida um tiro */
#define SHOT_DURATION 1 /* duraçao do tiro*/
#define SHOT_INTERVAL 0.1 /* intervalo minimo entre os tiros */
#define SHOT_SPEED 800 /* velocidade do tiro */
#define SHOT_MASS 50
#define INI_MASS 5000
#define INI_INERCIA 250*3 /* momento de inercia */
#define MIN_MASS 0.1 /* porcentagem mínima da massa */

#define PLANET_MASS 4995000

#define PROPELLANT_SPEED 4 /* velocidade de saída do combustível. */
#define PROPELLANT_MASSRATE 200 /* qunato de massa vai perder por segundo. */

#define SHIP_SPEED_REFERENCE 1000 /* valor máximo a ser mostrado no velocímetro */

/* Sobre os controles */
#define SHIP1_JET1 GLFW_KEY_A
#define SHIP1_JET2 GLFW_KEY_D
#define SHIP1_JET3 GLFW_KEY_W
#define SHIP1_GUM1 GLFW_KEY_S

#define SHIP2_JET1 GLFW_KEY_J
#define SHIP2_JET2 GLFW_KEY_L
#define SHIP2_JET3 GLFW_KEY_I
#define SHIP2_GUM1 GLFW_KEY_K

#define PAUSE GLFW_KEY_P
#define RESTART GLFW_KEY_R



