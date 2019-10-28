
/* assert.h - verify program assertion */

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(ignore)((void)0)
#else
/* TODO: Expand assert */
#endif
