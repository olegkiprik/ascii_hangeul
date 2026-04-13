/*
	Reversible Han-geul romanization scanner

	Disclaimer: Custom rules of romanization!

	Written in Dependable C documented by Eskil Steenberg:
	https://dependablec.org
*/

#define EFINE_HELPERS_IMPLEMENTATION
#include "efine_helpers.h"

#define EFINE_FSYNC_IMPLEMENTATION
#include "efine_fsync.h"

#include <stdlib.h>

/* ------------------------------------------------------------------------------------------------------------------ */

#if defined(RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS)
#define RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS_INT (1 == 1)
#else
#define RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS_INT (0 == 1)
#endif

#if defined(RHR_FINAL_CONSONANTS_PRECEDENCE)
#endif

#define RHR_MSG_FAILED_PRINT_CHAR "Failed to print a character"
#define RHR_MSG_FAILED_READ_CHAR "Failed to read a character"
#define RHR_MSG_FAILED_FLUSH "Failed to flush"
#define RHR_MSG_FAILED_SYNC "Failed to sync"

EFINE_DEF int rhr_char_is_separator(char c)
{
#if 0 == 1
	switch (c) {
	case '\r':
	case '\n':
	case '\t':
	case ' ':
	case '!':
	case '"':
	case '#':
	case '$':
	case '%':
	case '&':
	case '\'':
	case '(':
	case ')':
	case '*':
	case '+':
	case ',':
	case '-':
	case '.':
	case '/':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case ':':
	case ';':
	case '<':
	case '=':
	case '>':
	case '?':
	case '@':
	case '[':
	case '\\':
	case ']':
	case '^':
	case '_':
	case '`':
	case '|':
	case '~':
		return 1;
	default:
		break;
	}

	return 0;

#else
	int f1;

	f1 = 0;
	f1 |= (c == '\r' ? 1 : 0);
	f1 |= (c == '\n' ? 1 : 0);
	f1 |= (c == '\t' ? 1 : 0);
	f1 |= (c == ' ' ? 1 : 0);
	f1 |= (c == '!' ? 1 : 0);
	f1 |= (c == '"' ? 1 : 0);
	f1 |= (c == '#' ? 1 : 0);
	f1 |= (c == '$' ? 1 : 0);
	f1 |= (c == '%' ? 1 : 0);
	f1 |= (c == '&' ? 1 : 0);
	f1 |= (c == '\'' ? 1 : 0);
	f1 |= (c == '(' ? 1 : 0);
	f1 |= (c == ')' ? 1 : 0);
	f1 |= (c == '*' ? 1 : 0);
	f1 |= (c == '+' ? 1 : 0);
	f1 |= (c == ',' ? 1 : 0);
	f1 |= (c == '-' ? 1 : 0);
	f1 |= (c == '.' ? 1 : 0);
	f1 |= (c == '/' ? 1 : 0);
	f1 |= (c == '0' ? 1 : 0);
	f1 |= (c == '1' ? 1 : 0);
	f1 |= (c == '2' ? 1 : 0);
	f1 |= (c == '3' ? 1 : 0);
	f1 |= (c == '4' ? 1 : 0);
	f1 |= (c == '5' ? 1 : 0);
	f1 |= (c == '6' ? 1 : 0);
	f1 |= (c == '7' ? 1 : 0);
	f1 |= (c == '8' ? 1 : 0);
	f1 |= (c == '9' ? 1 : 0);
	f1 |= (c == ':' ? 1 : 0);
	f1 |= (c == ';' ? 1 : 0);
	f1 |= (c == '<' ? 1 : 0);
	f1 |= (c == '=' ? 1 : 0);
	f1 |= (c == '>' ? 1 : 0);
	f1 |= (c == '?' ? 1 : 0);
	f1 |= (c == '@' ? 1 : 0);
	f1 |= (c == '[' ? 1 : 0);
	f1 |= (c == '\\' ? 1 : 0);
	f1 |= (c == ']' ? 1 : 0);
	f1 |= (c == '^' ? 1 : 0);
	f1 |= (c == '_' ? 1 : 0);
	f1 |= (c == '`' ? 1 : 0);
	f1 |= (c == '|' ? 1 : 0);
	f1 |= (c == '~' ? 1 : 0);
	return f1;
#endif
}

/* c is a lowercase letter */
EFINE_DEF int rhr_portable_char_is_consonant(char c)
{
	switch (c) {
	case 'b':
	case 'c':
	case 'd':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'p':
	case 'r':
	case 's':
	case 't':
		return 1;
	case 'i':
	case 'e':
	case 'a':
	case 'o':
	case 'u':
	case 'y':
	case 'w':
		return 0;
	default:
		break;
	}

	return EFINE_DO_NOT_CARE_0_OR_1();
}

/*
	...abcdefghijklmnopqrstuvwxyz...
	---01110-1101111101-1110-0-0----
	00001110111011111011111000000000
*/
EFINE_DEF int rhr_std_optim_char_is_consonant(char c)
{
#if 1 == 1
	return (c < 'b' || c > 't' || c == 'o' || c == 'i' || c == 'e') ? 0 : 1;
#else
	int f1;

	f1 = 1;
	f1 &= (c < 'b' ? 0 : 1);
	f1 &= (c > 't' ? 0 : 1);
	f1 &= (c == 'o' ? 0 : 1);
	f1 &= (c == 'i' ? 0 : 1);
	f1 &= (c == 'e' ? 0 : 1);
	return f1;
#endif
}

EFINE_DEF int rhr_char_is_consonant(char c)
{
#if defined(EFINE_ASSUME_ORDERED_ASCII)
	return rhr_std_optim_char_is_consonant(c);
#else
	return rhr_portable_char_is_consonant(c);
#endif
}

EFINE_DEF int rhr_non_consonant_pair_possible(char b0, char c)
{
	/* a vowel is expected after 'w' and after 'y' */

#if 1 == 1
	if (b0 == 'y' || b0 == 'w')
		return 1;

	if (b0 == 'e' && c == 'u' || b0 == 'e' && c == 'o')
		return 1;

	if (b0 == 'a' && c == 'e' || b0 == 'e' && c == 'e')
		return 1;

	if (b0 == 'o' && c == 'o' || b0 == 'o' && c == 'e')
		return 1;

	return 0;
#else
	int f1;
	int f2;

	f1 = 0;

	f2 = (b0 == 'w' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'y' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'e' ? 1 : 0);
	f2 &= (c == 'u' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'e' ? 1 : 0);
	f2 &= (c == 'o' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'a' ? 1 : 0);
	f2 &= (c == 'e' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'e' ? 1 : 0);
	f2 &= (c == 'e' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'o' ? 1 : 0);
	f2 &= (c == 'o' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'o' ? 1 : 0);
	f2 &= (c == 'e' ? 1 : 0);
	f1 |= f2;

	return f1;
#endif
}

EFINE_DEF int rhr_non_consonant_triple_possible(char b0, char b1, char b2)
{
#if 1 == 1
	if (b0 == 'y' && b1 == 'e' && b2 == 'o')
		return 1;

	if (b0 == 'y' && b1 == 'a' && b2 == 'e')
		return 1;

	if (b0 == 'w' && b1 == 'a' && b2 == 'e')
		return 1;

	if (b0 == 'w' && b1 == 'o' && b2 == 'e')
		return 1;

	if (b0 == 'w' && b1 == 'e' && b2 == 'o')
		return 1;

	if (b0 == 'e' && b1 == 'u' && b2 == 'i')
		return 1;

	return 0;
#else
	int f1;
	int f2;

	f1 = 0;

	f2 = (b0 == 'y' ? 1 : 0);
	f2 &= (b1 == 'e' ? 1 : 0);
	f2 &= (b2 == 'o' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'y' ? 1 : 0);
	f2 &= (b1 == 'a' ? 1 : 0);
	f2 &= (b2 == 'e' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'w' ? 1 : 0);
	f2 &= (b1 == 'a' ? 1 : 0);
	f2 &= (b2 == 'e' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'w' ? 1 : 0);
	f2 &= (b1 == 'o' ? 1 : 0);
	f2 &= (b2 == 'e' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'w' ? 1 : 0);
	f2 &= (b1 == 'e' ? 1 : 0);
	f2 &= (b2 == 'o' ? 1 : 0);
	f1 |= f2;

	f2 = (b0 == 'e' ? 1 : 0);
	f2 &= (b1 == 'u' ? 1 : 0);
	f2 &= (b2 == 'i' ? 1 : 0);
	f1 |= f2;

	return f1;
#endif
}

EFINE_DEF int rhr_consonant_initial_possible(char c0, char c1)
{
	/* "cs" is not expected */

#if 1 == 1
	if (c0 == 'p' && c1 == 'p' || c0 == 'j' && c1 == 'j')
		return 1;

	if (c0 == 't' && c1 == 't' || c0 == 'k' && c1 == 'k')
		return 1;

	if (c0 == 's' && c1 == 's' || c0 == 'c' && c1 == 'h')
		return 1;

	if (c0 == 's' && c1 == 'h' || c0 == 'c' && c1 == 's')
		return 1;

	return 0;
#else
	int f1;
	int f2;

	f1 = 0;

	f2 = (c0 == 'p' ? 1 : 0);
	f2 &= (c1 == 'p' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'j' ? 1 : 0);
	f2 &= (c1 == 'j' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'k' ? 1 : 0);
	f2 &= (c1 == 'k' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 't' ? 1 : 0);
	f2 &= (c1 == 't' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 's' ? 1 : 0);
	f2 &= (c1 == 's' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'c' ? 1 : 0);
	f2 &= (c1 == 'h' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 's' ? 1 : 0);
	f2 &= (c1 == 'h' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'c' ? 1 : 0);
	f2 &= (c1 == 's' ? 1 : 0);
	f1 |= f2;

	return f1;
#endif
}

EFINE_DEF int rhr_consonant_final_possible(char c0, char c1)
{
	/* "cg", "cm", "cp", "cs", "ct", "cj", "cb" are not expected */
#if 1 == 1
	if (c0 == 'n' && c1 == 'g' || c0 == 'k' && c1 == 'k')
		return 1;

	if (c0 == 's' && c1 == 's' || c0 == 'n' && c1 == 'h')
		return 1;

	if (c0 == 'b' && c1 == 's' || c0 == 'g' && c1 == 's')
		return 1;

	if (c0 == 'n' && c1 == 'j')
		return 1;

	if ((c0 == 'l' || c0 == 'c') &&
	    (c1 == 'm' || c1 == 'g' || c1 == 'h' || c1 == 'b' || c1 == 'p' || c1 == 't' || c1 == 's'))
		return 1;

	return 0;
#else
	int f1;
	int f2;
	int f3;

	f1 = 0;

	f2 = (c0 == 'n' ? 1 : 0);
	f2 &= (c1 == 'g' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'k' ? 1 : 0);
	f2 &= (c1 == 'k' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 's' ? 1 : 0);
	f2 &= (c1 == 's' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'n' ? 1 : 0);
	f2 &= (c1 == 'h' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'b' ? 1 : 0);
	f2 &= (c1 == 's' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'g' ? 1 : 0);
	f2 &= (c1 == 's' ? 1 : 0);
	f1 |= f2;

	f2 = (c0 == 'n' ? 1 : 0);
	f2 &= (c1 == 'j' ? 1 : 0);
	f1 |= f2;

	f2 = (c1 == 'm' ? 1 : 0);
	f2 |= (c1 == 'g' ? 1 : 0);
	f2 |= (c1 == 'h' ? 1 : 0);
	f2 |= (c1 == 'b' ? 1 : 0);
	f2 |= (c1 == 'p' ? 1 : 0);
	f2 |= (c1 == 't' ? 1 : 0);
	f2 |= (c1 == 's' ? 1 : 0);

	f3 = (c0 == 'c' ? 1 : 0);
	f3 |= (c0 == 'l' ? 1 : 0);
	f2 &= f3;
	f1 |= f2;

	return f1;
#endif
}

EFINE_DEF int rhr_geulja_print_ascii(char *restrict a0, char a1, char *restrict b0, char b1, char b2, char *restrict c0,
				     char c1, char separator, char *restrict buff)
{
	if (EOF == efine_fputc_unlocked_no_eintr(*buff, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}
	if (*a0 == '\0')
		goto l_start_b;

	if (EOF == efine_fputc_unlocked_no_eintr(*a0, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}

	*a0 = '\0';

	if (a1 == '\0')
		goto l_start_b;

	if (EOF == efine_fputc_unlocked_no_eintr(a1, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}
l_start_b:
	if (*b0 == '\0')
		goto l_finish_printing;

	if (EOF == efine_fputc_unlocked_no_eintr(*b0, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}

	*b0 = '\0';

	if (b1 == '\0')
		goto l_start_c;

	if (EOF == efine_fputc_unlocked_no_eintr(b1, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}
	if (b2 == '\0')
		goto l_start_c;

	if (EOF == efine_fputc_unlocked_no_eintr(b2, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}
l_start_c:
	if (*c0 == '\0')
		goto l_finish_printing;

	if (EOF == efine_fputc_unlocked_no_eintr(*c0, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}

	*c0 = '\0';

	if (c1 == '\0')
		goto l_finish_printing;

	if (EOF == efine_fputc_unlocked_no_eintr(c1, stdout)) {
		perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
		return 1;
	}
l_finish_printing:
	*buff = separator;
	return 0;
}

EFINE_DEF int rhr_scan(void)
{
	int c_int;
	char c;
	char a0;
	char a1;
	char b0;
	char b1;
	char b2;
	char c0;
	char c1;
	char dummy;
	char buff;
	int ignoring;
	int backslash;
	int tmp;

	c = '\0';
	a0 = '\0';
	a1 = '\0';
	b0 = '\0';
	b1 = '\0';
	b2 = '\0';
	c0 = '\0';
	c1 = '\0';
	dummy = '\0';

	ignoring = 0;
	buff = '\n';

	c_int = efine_fgetc_unlocked_no_eintr(stdin);
	while (c_int != EOF) {
		c = (char)c_int;
		if (ignoring == 1) {
			tmp = 1;
			if (backslash == 1) {
				backslash = 0;
			} else if (c == '\\') {
				backslash = 1;
				if (RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS_INT) {
					tmp = 0;
				}
			} else if (c == '}') {
				ignoring = 0;
				if (RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS_INT) {
					tmp = 0;
				}
			}
			if (tmp == 1) {
				if (EOF == efine_fputc_unlocked_no_eintr(c, stdout)) {
					perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
					return 1;
				}
			}
		} else if (1 == rhr_char_is_separator(c)) {
			if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, c, &buff))
				return 1;
			c0 = '\0';
		} else if (1 == rhr_char_is_consonant(c)) {
			if (b0 == '\0') {
				if (a0 == '\0') {
					a0 = c;
					a1 = '\0';
				} else {
					a1 = c;
				}
			} else if (c0 == '\0') {
				c0 = c;
				c1 = '\0';
			} else if (c1 == '\0') {
				c1 = c;
			} else if (0 == rhr_consonant_initial_possible(c1, c) ||
				   (c1 == 's' && c == 'h' && 1 == rhr_consonant_final_possible(c0, c1))) {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
					return 1;
				a0 = c;
				a1 = '\0';
			} else {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, '\0', '-', &buff))
					return 1;
				a0 = c1;
				a1 = c;
			}
		} else if (c == '{') {
			if (RHR_OMIT_BRACES_AND_ESCAPE_SYMBOLS_INT) {

			} else if (EOF == efine_fputc_unlocked_no_eintr(c, stdout)) {
				perror("\n" RHR_MSG_FAILED_PRINT_CHAR);
				return 1;
			}
			ignoring = 1;
			backslash = 0;
		} else if (b0 == '\0') {
			b0 = c;
			b1 = '\0';
		} else if (c0 == '\0') {
			if (b1 == '\0') {
				if (1 == rhr_non_consonant_pair_possible(b0, c)) {
					b1 = c;
					b2 = '\0';
				} else {
					if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
						return 1;
					b0 = c;
					b1 = '\0';
				}
			} else if (b2 != '\0' || 0 == rhr_non_consonant_triple_possible(b0, b1, c)) {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
					return 1;
				b0 = c;
				b1 = '\0';
			} else {
				b2 = c;
			}
		} else if (c0 == 'l' && c == 'w') {
			if (c1 == '\0' || 1 == rhr_consonant_final_possible(c0, c1)) {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
					return 1;
				b0 = c;
				b1 = '\0';
			} else {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, '\0', '-', &buff))
					return 1;
				a0 = c1;
				a1 = '\0';
				b0 = c;
				b1 = '\0';
			}
		} else if (c1 == '\0') {
			if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &dummy, '\0', '-', &buff))
				return 1;
			a0 = c0;
			a1 = '\0';
			b0 = c;
			b1 = '\0';
			c0 = '\0';
		} else if (1 == rhr_consonant_initial_possible(c0, c1)) {
			if (c != 'i' && c0 == 's' && c1 == 'h') {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, '\0', '-', &buff))
					return 1;
				a0 = c1;
				b0 = c;
				b1 = '\0';
			} else {
				if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &dummy, '\0', '-', &buff))
					return 1;
				a0 = c0;
				a1 = c1;
				b0 = c;
				b1 = '\0';
				c0 = '\0';
			}
		} else if (1 == rhr_consonant_final_possible(c0, c1)) {
#if defined(RHR_FINAL_CONSONANTS_PRECEDENCE)
			/* hangeul -> hang-eul */
			if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
				return 1;
			b0 = c;
			b1 = '\0';
#else
			/* hangeul -> han-geul */
			if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, '\0', '-', &buff))
				return 1;
			a0 = c1;
			a1 = '\0';
			b0 = c;
			b1 = '\0';
#endif
		} else {
			if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, '\0', '-', &buff))
				return 1;
			a0 = c1;
			a1 = '\0';
			b0 = c;
			b1 = '\0';
		}

		c_int = efine_fgetc_unlocked_no_eintr(stdin);
	}

	if (0 != ferror(stdin)) {
		perror("\n" RHR_MSG_FAILED_READ_CHAR);
		return 1;
	}

	if (a0 != '\0' || b0 != '\0') {
		if (0 != rhr_geulja_print_ascii(&a0, a1, &b0, b1, b2, &c0, c1, '-', &buff))
			return 1;
	}

	if (0 != fflush_unlocked(stdout)) {
		perror("\n" RHR_MSG_FAILED_FLUSH);
		return 1;
	}

	if (0 != efine_fsync(STDOUT_FILENO)) {
		perror("\n" RHR_MSG_FAILED_SYNC);
		return 1;
	}

	return 0;
}

int main(void)
{
	int result;

	if (1 != (0 | 1) || 0 != (0 & 1) || 1 != (0 ^ 1) || 0 != (42 ^ 42)) {
		fputs("Unsupported platform\n", stderr);
		return EXIT_FAILURE;
	}

	flockfile(stdin);
	flockfile(stdout);
	result = rhr_scan();
	funlockfile(stdout);
	funlockfile(stdin);

	return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

#if 1 != (0 | 1) || 0 != (0 & 1) || 1 != (0 ^ 1) || 0 != (42 ^ 42)
#error "Unsupported platform"
#endif
