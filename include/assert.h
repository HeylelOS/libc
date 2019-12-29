
/* assert.h - verify program assertion */

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(ignore)((void)0)
#else
#define assert(expression) (expression) ? ((void)0) : _assertion_failure(#expression, __FILE__, __LINE__)
#ifndef _ASSERT_H
#define _ASSERT_H

void
_assertion_failure(const char *, const char *, int);

/* _ASSERT_H */
#endif
#endif
