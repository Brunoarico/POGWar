/******************************************************************************
 *  Nome:   Bruno Arico         8125459
 *          Gabriel Capella     8962078
 *          Nicolas Nogueira    9277541
 *
 *  Projeto da disciplina de Laboratorio de Programacao MAC0211
 *  Batalha Espacial
 *
 ******************************************************************************/
struct shape {
    Vector *pontos;
    int N; /* Numero de pontos */
};
typedef struct shape *Shape;

/* n eh a resolucao do circulo */
Shape cricle (int n);

/* h eh a altura e l o tamanho do lado */
Shape equilateral (double h, double l);

/* adiciona um ponto a v */
void add_point (Shape s, Vector v);
