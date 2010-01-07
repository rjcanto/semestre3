#ifndef FILTERSPNG_H
#define FILTERSPNG_H
#include "myLib.h"
#include "imageFormat.h"

enum filter {NONE, SUB, UP, AVERAGE, PAETH, BEST};

int filter_none(byte source[], byte dest[], int size);
int unfilter_none(byte source[], byte dest[], int size);

int filter_sub(byte source[], byte dest[], int size, int bpp);
int unfilter_sub(byte source[], byte dest[], int size, int bpp);

int filter_up(byte source[], byte prev[], byte dest[], int size, int bpp);
int unfilter_up(byte source[], byte prev[], byte dest[], int size, int bpp);

int filter_average(byte source[], byte prev[], byte dest[], int size, int bpp);
int unfilter_average(byte source[], byte prev[], byte dest[], int size, int bpp);

byte paethPredictor(byte left, byte upper, byte upper_left);
int filter_paeth(byte source[], byte prev[], byte dest[], int size, int bpp);
int unfilter_paeth(byte source[], byte prev[], byte dest[], int size, int bpp);

void copyByteArray(byte source[], byte dest[], int size);
int filter_best(byte source[], byte prev[], byte dest[], int size, int bpp);

int filterPNG(byte source[], byte prev[], byte dest[], int size, int bpp, int filterType);
int unfilterPNG(byte source[], byte prev[], byte dest[], int size, int bpp);

#endif
