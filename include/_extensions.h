#ifndef __EXTENSIONS_H
#define __EXTENSIONS_H

#if !defined(__has_attribute)
#define __has_attribute(attribute) 0
#endif

#if !defined(__has_builtin)
#define __has_builtin(builtin) 0
#endif

/* Attributes */

#if __has_attribute(noreturn)
#define _NORETURN __attribute__((noreturn))
#else
#define _NORETURN
#endif

#if __has_attribute(_Nonnull)
#define _NONNULL _Nonnull
#else
#define _NONNULL
#endif

#if __has_attribute(_Nullable)
#define _NULLABLE _Nullable
#else
#define _NULLABLE
#endif

/*
 * The use of always_inline is mainly used for inline full-assembly functions.
 * Its use is discouraged in plain C code, and the use of static inline
 * is encouraged as it nearly always ends inline when optimized.
 */
#if __has_attribute(always_inline)
#define _INLINE_ALWAYS __attribute__((always_inline))
#else
#define _INLINE_ALWAYS static inline
#endif

/* __EXTENSIONS_H */
#endif
