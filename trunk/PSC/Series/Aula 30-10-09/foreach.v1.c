#include <stdio.h>

typedef unsigned int uint;

void foreach(void * data, uint dim, uint num, void (*action)(void * elem)) {
  char * p = (char *)data;
  uint i;
  for (i = 0; i != num; ++i) {
    (*action)(p);
    p += dim;
  }
}

int    idata[] = { 12, 15, -55, -3, 0, 6, -9, 1 };
float  fdata[] = { -1.23, 22.55, -15.91, 0.033, 5.234 };
char * sdata[] = { "PSC", "AED", "SI1", "Com" };

void iaction(void * elem) { printf("%d ", *(int*)elem); }
void faction(void * elem) { printf("%f ", *(float*)elem); }
void saction(void * elem) { printf("%s ", *(char**)elem); }

int main() {

  foreach(idata, sizeof(idata[0]), sizeof(idata)/sizeof(idata[0]), iaction); putchar('\n');
  foreach(fdata, sizeof(fdata[0]), sizeof(fdata)/sizeof(fdata[0]), faction); putchar('\n'); 
  foreach(sdata, sizeof(sdata[0]), sizeof(sdata)/sizeof(sdata[0]), saction); putchar('\n');

  return 0;
}
