/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef _UTILS_H
#define _UTILS_H

#include "../util/parser/parser.h"

// used to check if a warning / an error exist
#define l_check(condition, description, name, type, signal, ret) \
	do { \
		if (condition) { \
			fprintf(stderr, "In %s(...) ", __func__); \
			if (type) {/* function - 1 */ \
				fprintf(stderr, "the function %s gave the following %s: %s.\n", name, signal, description); \
			} else { \
				/* variable - 0 */ \
				fprintf(stderr, "the variable %s gave the following %s: %s.\n", name, signal, description); \
			} \
			if (ret != -8) \
				return ret; /* if I don't want to return anything */ \
		} \
	} while (0)

// test if condition to see if there is an error in OP
#define l_try(condition) \
	do { \
		if (condition) { \
			fprintf(stderr, "%s error", __func__); \
			return -1; \
		} \
	} while (0)

/* Useful macro for handling error codes. */
#define DIE(assertion, call_description)			\
	do {							\
		if (assertion) {				\
			fprintf(stderr, "(%s, %s, %d): ",	\
				__FILE__, __func__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);			\
		}						\
	} while (0)

/**
 * Concatenate parts of the word to obtain the command.
 */
char *get_word(word_t *s);

/**
 * Concatenate command arguments in a NULL terminated list in order to pass
 * them directly to execv.
 */
char **get_argv(simple_command_t *command, int *size);

#endif /* _UTILS_H */
