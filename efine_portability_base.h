/*
	Helpers to make C more dependable

	An excerpt from
	https://dependablec.org/#Requirements
	2026-04-11

	Bytes/char are 8 bits.

	Types are aligned to their size.

	Source code is ASCII. (C Source files can be Unicode, but this is not dependable, and creates all manner of
	debugging, usability and security issues, like invisible characters, identically looking characters,
	characters people cant type, backwards text and so on.)

	Function pointer have the same size as data pointers. (Not guaranteed by the standard.)

	int is at least 32 bits.
*/

#if !defined(EFINE_PORTABILITY_BASE_H_SENTRY)
#define EFINE_PORTABILITY_BASE_H_SENTRY

#if defined(EFINE_NO_UNNECESSARY_DEPENDING_ON_UNISTD)
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define F_OK 0
#define W_OK 2
#define R_OK 4
#endif

#if !defined(EFINE_NOT_SUPPORTED_UNLOCKED_IO)
#endif

#if !defined(EFINE_REPLACED_UNISTD)
#endif

#if defined(_WIN32) && !defined(EFINE_REPLACED_UNISTD)
#error "Please provide a replacement for unistd.h"
#endif

#if !defined(EFINE_ASSUME_ORDERED_ASCII)
#endif

#if defined(EFINE_NOT_SUPPORTED_BUILTIN)
#define __builtin_unreachable()                                                                                        \
	do {                                                                                                           \
	} while (0 == 1)
#define __builtin_expect(a, b) ((a) == (b))
#define __builtin_expect_with_probability(a, b, c) ((a) == (b))
#define __builtin_assume_aligned(a, b, c) (a)
#define __builtin_prefetch(addr, rw, locality) (addr)
#endif

#if defined(EFINE_NOT_SUPPORTED_CONST)
#define const
#endif

#if defined(EFINE_NOT_SUPPORTED_RESTRICT)
#define restrict
#endif

#if defined(EFINE_NOT_SUPPORTED_RESTRICT_WITH_TWO_UNDERSCORES_BEFORE)
#define __restrict
#endif

#if defined(NDEBUG)
#define EFINE_NDEBUG (1 == 1)
#else
#define EFINE_NDEBUG (0 == 1)
#endif

#if defined(EFINE_NOT_SUPPORTED_UNLOCKED_IO)

#define clearerr_unlocked(stream) clearerr(stream)
#define fileno_unlocked(stream) fileno(stream)
#define feof_unlocked(stream) feof(stream)
#define ferror_unlocked(stream) ferror(stream)
#define fflush_unlocked(stream) fflush(stream)
#define fgetc_unlocked(stream) fgetc(stream)
#define fputc_unlocked(c, stream) fputc(c, stream)
#define fread_unlocked(ptr, size, n, stream) fread(ptr, size, n, stream)
#define fwrite_unlocked(ptr, size, n, stream) fwrite(ptr, size, n, stream)
#define getc_unlocked(stream) getc(stream)
#define getchar_unlocked() getchar()
#define putc_unlocked(c, stream) putc(c, stream)
#define putchar_unlocked(c) putchar(c)

#define flockfile(filehandle)                                                                                          \
	do {                                                                                                           \
	} while (0 == 1)
#define ftrylockfile(filehandle) 0
#define funlockfile(filehandle)                                                                                        \
	do {                                                                                                           \
	} while (0 == 1)

#endif /* EFINE_NOT_SUPPORTED_UNLOCKED_IO */

/*
	https://dependablec.org

	typedef struct MyStringType_ {
		int string_length;
		char string[DEPENDABLE_C_FLEXIBLE_ARRAY_MEMBER];
	} MyStringType;

	s = malloc((sizeof *s) + sizeof(char) * (i - DEPENDABLE_C_FLEXIBLE_ARRAY_MEMBER_SUBTRACT));
*/
#if __STDC_VERSION__ >= 199901L
#define EFINE_FLEXIBLE_ARRAY_MEMBER
#define EFINE_FLEXIBLE_ARRAY_MEMBER_SUBTRACT 0
#elif defined(__clang__) || defined(__GNUC__)
#define EFINE_FLEXIBLE_ARRAY_MEMBER 0
#define EFINE_FLEXIBLE_ARRAY_MEMBER_SUBTRACT 0
#elif
#define EFINE_FLEXIBLE_ARRAY_MEMBER 1
#define EFINE_FLEXIBLE_ARRAY_MEMBER_SUBTRACT 1
#endif

#if defined(EFINE_NOT_SUPPORTED_STDINT_LP64)

typedef long intmax_t;
typedef unsigned long uintmax_t;

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef signed char int_fast8_t;
typedef short int_fast16_t;
typedef int int_fast32_t;
typedef long int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long uint_fast64_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long uint_least64_t;

#endif /* EFINE_NOT_SUPPORTED_STDINT */

#endif /* EFINE_PORTABILITY_BASE_H_SENTRY */

/* 2026-04-13 */
