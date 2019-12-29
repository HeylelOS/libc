#ifndef _FENV_H
#define _FENV_H

/* fenvh.h - floating-point environment */

typedef unsigned int fenv_t;
typedef unsigned int fexcept_t;

#ifdef _POSIX_EXTENSION_MX
#define FE_DIVBYZERO (1 << 0)
#define FE_INEXACT   (1 << 1)
#define FE_INVALID   (1 << 2)
#define FE_OVERFLOW  (1 << 3)
#define FE_UNDERFLOW (1 << 4)
#define FE_ALL_EXCEPT (FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

#define FE_DOWNWARD   1
#define FE_TONEAREST  2
#define FE_TOWARDZERO 3
#define FE_UPWARD     4
#else
#define FE_ALL_EXCEPT 0
#endif

#define FE_DFL_ENV ((const fenv_t *)-1)

int feclearexcept(int);
int fegetenv(fenv_t *);
int fegetexceptflag(fexcept_t *, int);
int fegetround(void);
int feholdexcept(fenv_t *);
int feraiseexcept(int);
int fesetenv(const fenv_t *);
int fesetexceptflag(const fexcept_t *, int);
int fesetround(int);
int fetestexcept(int);
int feupdateenv(const fenv_t *);

/* _FENV_H */
#endif
