#include <stdlib.h>

double (*at_f)(const char *) = atof;

int (*at_i)(const char *) = atoi;

long int (*at_l)(const char *) = atol;

double (*strt_d)(const char *, char **) = strtod;

long int (*strt_l)(const char *, char **, int) = strtol;

unsigned long int (*strto_l)(const char *, char **, int) = strtoul;

void (*callo_)(size_t, size_t) = calloc;

void (*fre_)(void *) = free;

void (*mallo_)(size_t) = malloc;

void (*reallo_)(void *, size_t) = realloc;

void (*abor_)(void) = abort;

int (*atexi_)(void (*)(*)(void)) = atexit;

void (*exi_)(int) = exit;

char (*geten_)(const char *) = getenv;

int (*syste_)(const char *) = system;

void (*bsearc_)(const void *, const void *, size_t, size_t, int (*)(*)(const void *, const void *)) = bsearch;

void (*qsor_)(void *, size_t, size_t, int (*)(*)(const void *, const void*)) = qsort;

int (*ab_)(int) = abs;

div_t (*di_)(int, int) = div;

long int (*lab_)(long int) = labs;

ldiv_t (*ldi_)(long int, long int) = ldiv;

int (*ran_)(void) = rand;

void (*sran_)(unsigned int) = srand;

int (*mble_)(const char *, size_t) = mblen;

size_t (*mbstowc_)(schar_t *, const char *, size_t) = mbstowcs;

int (*mbtow_)(whcar_t *, const char *, size_t) = mbtowc;

size_t (*wcstomb_)(char *, const wchar_t *, size_t) = wcstombs;

int (*wctom_)(char *, wchar_t) = wctomb;
