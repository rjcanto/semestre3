#include <stdio.h>
#include <string.h>

typedef int (*cmp_f)(int val1, int val2);

int findmin4(void * pdata, unsigned int num, cmp_f cmp);

int    idata[] = { 12, 15, -55, -3, 0, 6, -9, 1 };
float  fdata[] = { -1.23, 22.55, -15.91, 0.033, 5.234 };
char * sdata[] = { "PSC", "AED", "SI1", "Com" };

int icmp(int v1, int v2) { return v1 - v2; }
int fcmp(float v1, float v2) { return (fabsf(v1 - v2) < 0.001) ? 0 : (((v1 - v2) > 0) ? 1 : -1); }

int main() {

  int min;

  int imin;
  float fmin;
  char * smin;

  min = findmin4(idata, 8, &icmp);
  imin = min;

  min = findmin4(fdata, 5, (cmp_f)&fcmp);
  fmin = *(float*)&min;

  min = findmin4(sdata, 4, (cmp_f)&strcmp);
  smin = (char *)min;

  printf("imin = %d\n", imin);
  printf("fmin = %f\n", fmin);
  printf("smin = %s\n", smin);

  return 0;
};
