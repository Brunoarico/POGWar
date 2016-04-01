#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Função responsavel pela alocação segura de memoria, se a memoria não puder ser alocada, o programa é encerrado (função retirada da webpage do Prof. Paulo Feofillof*/
void *mallocc (size_t nbytes) {
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      printf ("Socorro! malloc devolveu NULL!\n");
      exit (EXIT_FAILURE);
   }
   return ptr;
}

float** allocM (int m, int n) {
  float **M;
  int i;
  M = mallocc (m * sizeof(float*));
  for (i = 0; i < m; i++) M[i] = mallocc (sizeof(float));
  return M;
}

void FreeM (float **M, int m, int n) {
  int i; 
  for (i = 0; i < n; i++) free(M[i]);
  free(M);
}
  

/*Recebe um vetor x de tamanho igual a 2 e devolve o seu modulo*/
float modulo (float x[]) {
    return sqrt( pow (x[0], 2) + pow (x[1], 2));
}

/*Recebe dois vetores posA  e posB de tamanhos iguais a 2 e devolve a distancia euclidiana entre eles*/
float distEucl (float posA[2], float posB[2]) {
    return sqrt (pow (posA[0] - posB[0], 2) + pow (posA[1] - posB[1], 2));
}

/*Converte graus para radianos*/
float to_rad(float  deg) {
    return deg * (M_PI / 180.0);
}

/*Converte radianos para graus*/
float to_deg(float rad) {
    return rad * (180.0 / M_PI);
}
