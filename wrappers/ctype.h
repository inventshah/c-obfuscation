#include <ctype.h>

int (*isalnu_)(int) = isalnum;

int (*isalph_)(int) = isalpha;

int (*iscntr_)(int) = iscntrl;

int (*isdigi_)(int) = isdigit;

int (*isgrap_)(int) = isgraph;

int (*islowe_)(int) = islower;

int (*isprin_)(int) = isprint;

int (*ispunc_)(int) = ispunct;

int (*isspac_)(int) = isspace;

int (*isuppe_)(int) = isupper;

int (*isxdigi_)(int) = isxdigit;

int (*tolowe_)(int) = tolower;
int (*touppe_)(int) = toupper;