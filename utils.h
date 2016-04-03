#ifndef UTILS
#define UTILS

#include <stdlib.h>

void *mallocc (size_t nbytes);

float** allocM(int m, int n);

float modulo (float x[]);

float distEucl (float posA[2], float posB[2]);

void FreeM (float **M, int m, int n);

float to_rad(float  deg);

float to_deg(float rad);

#endif
