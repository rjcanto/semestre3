#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

void * foreach(void * data, uint dim, uint num,
               void * (*action)(void * elem, void * ctx),
               void * ctx) {
  char * p = (char *)data;
  uint i;
  for (i = 0; i != num; ++i) {
    ctx = (*action)(p, ctx);
    p += dim;
  }
  return ctx;
}

int    idata[] = { 12, 15, -55, -3, 0, 6, -9, 1 };
float  fdata[] = { -1.23, 22.55, -15.91, 0.033, 5.234 };
char * sdata[] = { "PSC", "AED", "SI1", "Com" };

void * iaction(void * elem, void * ctx) { 
  if (!ctx) return elem;
  return *(int*)elem < *(int*)ctx ? elem : ctx;
}

void * faction(void * elem, void * ctx) { 
  if (!ctx) return elem;
  return *(float*)elem < *(float*)ctx ? elem : ctx;
}

void * saction(void * elem, void * ctx) { 
  if (!ctx) return elem;
  return strcmp(*(char**)elem, *(char**)ctx) < 0 ? elem : ctx;
}

int main() {

  void * pmin;

  int imin;
  float fmin;
  char * smin;
  
  pmin = foreach(idata, sizeof(idata[0]), sizeof(idata)/sizeof(idata[0]), iaction, NULL);
  imin = *(int*)pmin;
  
  pmin = foreach(fdata, sizeof(fdata[0]), sizeof(fdata)/sizeof(fdata[0]), faction, NULL);
  fmin = *(float*)pmin;
  
  pmin = foreach(sdata, sizeof(sdata[0]), sizeof(sdata)/sizeof(sdata[0]), saction, NULL);
  smin = *(char**)pmin;

  printf("imin = %d\n", imin);
  printf("fmin = %f\n", fmin);
  printf("smin = %s\n", smin);
  
  return 0;
}
