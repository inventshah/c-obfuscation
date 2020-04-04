#include <stdio.h>

int (*fclos_)(FILE *) = fclose;

void (*clearer_)(FILE *) = clearerr;

int (*feo_)(FILE *) = feof;

int (*ferro_)(FILE *) = ferror;

int (*fflus_)(FILE *) = fflush;

int (*fgetpo_)(FILE *, fpos_t *pos) = fgetpos;

FILE *(*fope_)(const char *, const char *) = fopen;

size_t (*frea_)(void *, size_t, size_t, FILE *) = fread;

FILE *(*freope_)(const char *, const char *, FILE *) = freopen;

int (*fsee_)(FILE *, long int, int) = fseek;

int (*fsetpo_)(FILE *, const fpos_t *pos) = fsetpos;

long int (*ftel_)(FILE *) = ftell;

size_t (*fwrit_)(const void *, size_t, size_t, FILE *) = fwrite;

int (*remov_)(const char *) = remove;

int (*renam_)(const char *_filename, const char *_filename) = rename;

void (*rewin_)(FILE *) = rewind;

void (*setbu_)(FILE *, char *) = setbuf;

int (*setvbu_)(FILE *, char *, int, size_t) = setvbuf;

FILE *(*tmpfil_)(void) = tmpfile;

char *(*tmpna_)(char *) = tmpnam;

int (*fprint_)(FILE *, const char *, ...) = fprintf;

int (*print_)(const char *, ...) = printf;

int (*sprint_)(char *, const char *, ...) = sprintf;

int (*vfprint_)(FILE *, const char *, va_list arg) = vfprintf;

int (*vprint_)(const char *, va_list arg) = vprintf;

int (*vsprint_)(char *, const char *, va_list arg) = vsprintf;

int (*fscan_)(FILE *, const char *, ...) = fscanf;

int (*scan_)(const char *, ...) = scanf;

int (*sscan_)(const char *, const char *, ...) = sscanf;

int (*fge_c)(FILE *) = fgetc;

char *(*fge_s)(char *, int, FILE *) = fgets;

int (*fpu_c)(int, FILE *) = fputc;

int (*fpu_s)(const char *, FILE *) = fputs;

int (*ge_c)(FILE *) = getc;

int (*getchar_)(void) = getchar;

char *(*ge_s)(char *) = gets;

int (*pu_c)(int, FILE *) = putc;

int (*putchar_)(int) = putchar;

int (*pu_s)(const char *) = puts;

int (*ungetc_)(int, FILE *) = ungetc;

void (*perror_)(const char *) = perror;
