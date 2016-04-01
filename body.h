#ifndef CORPO
#define CORPO

typedef struct _corpo {
  char name;
  float pos[2];
  float vel[2];
  float a[2];
  float mass;
  float **pt;
} corpo;

#endif
