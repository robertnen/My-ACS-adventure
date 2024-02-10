// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source) {
	int i;
	for (i = 0; source[i]; i++) destination[i] = source[i];
	destination[i] = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len) {
	for (size_t i = 0; i < len; i++) destination[i] = source[i];
	return destination;
}

char *strcat(char *destination, const char *source) {
	size_t i;
	int len = strlen(destination);

	for (i = strlen(destination); source[i - len]; i++) destination[i] = source[i - len];
	destination[i] = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len) {
	size_t i;
	int lenDest = strlen(destination);
	for (i = lenDest; i < len + lenDest; i++) destination[i] = source[i - lenDest];
	destination[i] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2) {
	int i = 0;
	while (str1[i] && str2[i]) {
		if (str1[i] < str2[i]) return -1;
		if (str1[i] > str2[i]) return 1;
		i++;
	}

	if (str1[i] && !str2[i]) return 1;  // strlen(str1) > strlen(str2)
	if (str2[i] && !str1[i]) return -1; // strlen(str1) < strlen(str2)

	return 0;
}

int strncmp(const char *str1, const char *str2, size_t len) {
	size_t i = 0;
	while (str1[i] && str2[i] && i < len) {
		if (str1[i] < str2[i]) return -1;
		if (str1[i] > str2[i]) return 1;
		i++;
	}

	return 0;
}

size_t strlen(const char *str) {
	size_t i = 0;

	for (; *str != '\0'; str++, i++) continue;

	return i;
}

char *strchr(const char *str, int c) {
	int pos = 0, len = strlen(str);
	while (pos < len) {
		if (str[pos] == c) return (char *)(str + pos);
		pos++;
	}

	return NULL;
}

char *strrchr(const char *str, int c) {
	int pos = strlen(str);
	while (pos >= 0) {
		if (str[pos] == c) return (char *)(str + pos);
		pos--;
	}

	return NULL;
}

char *strstr(const char *haystack, const char *needle) {
	if (strlen(needle) > strlen(haystack)) return NULL; // a substring can't be longer than the string

	size_t i, j;

	for (size_t k = 0; k < strlen(haystack); k++)
		if (haystack[k] == needle[0]) { // first character found
			i = k; j = 0;
			while (haystack[i] && haystack[i++] == needle[j] && j++ < strlen(needle)) continue; // while both equal
			if (j == strlen(needle)) return (char *)(haystack + k); // found
		}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
	if (strlen(needle) > strlen(haystack)) return NULL; // a substring can't be longer than the string

	size_t i, j;

	for (int k = strlen(haystack) - 1; k >= 0; k--)
		if (haystack[k] == needle[0]) { // first character found
			i = k; j = 0;
			while (haystack[i] && haystack[i++] == needle[j] && j++ < strlen(needle)) continue; // while both equal
			if (j == strlen(needle)) return (char *)(haystack + k); // found
		}

	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num) {
	char *dest = (char *) destination, *src = (char *) source;

	if (!dest || !src) return destination; // if uninitialized stop

	while (num--) *dest++ = *src++; // copy

	return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
    char *dest = (char *)destination, *src = (char *)source;

    if (src < dest) { // if smaller, go from the end
        dest += num - 1;
        src += num - 1;
        while (num--) *dest-- = *src--;
    } else {
		 while (num--) *dest++ = *src++; // else from the start
	}
    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    const unsigned char *p1 = (const unsigned char *)ptr1; // casting
	const unsigned char *p2 = (const unsigned char *)ptr2;

    for (size_t i = 0; i < num; i++) {
        if (p1[i] > p2[i]) return 1;
        if (p1[i] < p2[i]) return -1;
    }

    return 0;
}

void *memset(void *source, int value, size_t num) {
	unsigned char *src = (unsigned char *)source;

    for (size_t i = 0; i < num; i++) src[i] = value;

	return source;
}
