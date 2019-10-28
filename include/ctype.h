#ifndef _CTYPE_H
#define _CTYPE_H

/* ctype.h - character types */

int isalnum(int);
int isalpha(int);
int isblank(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);

#if defined(_POSIX_EXTENSION_OB) || defined(_POSIX_EXTENSION_XSI)
int isascii(int);
int toascii(int);

#define _toupper(c)
#define _tolower(c)
#endif

#ifdef _POSIX_EXTENSION_CX
/* As in <locale.h> */
#include <_definitions/locale_t.h>

int isalnum_l(int, locale_t);
int isalpha_l(int, locale_t);
int isblank_l(int, locale_t);
int iscntrl_l(int, locale_t);
int isdigit_l(int, locale_t);
int isgraph_l(int, locale_t);
int islower_l(int, locale_t);
int isprint_l(int, locale_t);
int ispunct_l(int, locale_t);
int isspace_l(int, locale_t);
int isupper_l(int, locale_t);
int isxdigit_l(int, locale_t);
int tolower_l(int, locale_t);
int toupper_l(int, locale_t);

#endif

/* _CTYPE_H */
#endif
