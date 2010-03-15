#ifndef FILTERSPNG_H
#define FILTERSPNG_H
#include "myLib.h"
#include "imageFormat.h"

enum filter {NONE, SUB, UP, AVERAGE, PAETH, BEST};

int filterPNG(byte source[], byte prev[], byte dest[], int size, int bpp, int filterType);
int unfilterPNG(byte source[], byte prev[], byte dest[], int size, int bpp);

#endif
