#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
typedef int (*cmp_f)(void * val1, void * val2);

void * findmin(void * pdata, uint dim, uint num, cmp_f cmp);

int    idata[] = { 12, 15, -55, -3, 0, 6, -9, 1 };
float  fdata[] = { -1.23, 22.55, -15.91, 0.033, 5.234 };
char * sdata[] = { "PSC", "AED", "SI1", "Com" };

int icmp(void * v1, void * v2) { return (*(int*)v1) - (*(int*)v2); }

int fcmp(void * v1, void * v2) {
  float * f1 = (float*)v1;
  float * f2 = (float*)v2;
  return (fabsf(*f1 - *f2) < 0.001) ? 0 : (((*f1 - *f2) > 0) ? 1 : -1);
}

int scmp(void * v1, void * v2) { return strcmp(*(char**)v1, *(char**)v2); }

int main() {

  void * pmin;

  int imin;
  float fmin;
  char * smin;

  pmin = findmin(idata, sizeof(int), 8, &icmp);
  imin = *(int*)pmin;

  pmin = findmin(fdata, sizeof(float), 5, &fcmp);
  fmin = *(float*)pmin;

  pmin = findmin(sdata, sizeof(char*), 4, &scmp);
  smin = *(char**)pmin;

  printf("imin = %d\n", imin);
  printf("fmin = %f\n", fmin);
  printf("smin = %s\n", smin);

  return 0;
};
